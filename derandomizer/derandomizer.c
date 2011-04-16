#define _LARGEFILE64_SOURCE
#define _GNU_SOURCE

#include <sys/wait.h>
#include <sys/user.h>
#include <sys/time.h>
#include <sys/ptrace.h>
#include <sys/signal.h>
#include <sys/sysinfo.h>
#include <sys/resource.h>
#include <sys/utsname.h>
#include <linux/ptrace.h>
#include <asm/unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <bits/wordsize.h>
#include <sys/syscall.h>
#include <stdint.h>

int child_pid;

#if __WORDSIZE == 64
typedef uint64_t arg_t;
#elif __WORDSIZE == 32
typedef uint32_t arg_t;
#endif

#if __WORDSIZE == 64
arg_t translate_32_to_64_syscall(arg_t a)
{
    switch(a)
    {
        case 3: return __NR_read;
        case 4: return __NR_write;
        case 5: return __NR_open;
        case 6: return __NR_close;
        case 13: return __NR_time;
        default: return a;
    }
}
#endif

ssize_t read_user_mem(arg_t addr, char *buf, int len)
{
    static int mem_fd = -1;

    if(mem_fd == -1)
    {
        char memname[64];
        sprintf(memname, "/proc/%d/mem", (int)child_pid);
        mem_fd = open(memname, O_RDONLY);
        if(mem_fd < 0)
        {
            perror("[derandomizer] open(mem,rd) failed\n");
            exit(1);
        }
    }
    if(lseek64(mem_fd, addr, SEEK_SET) == (off64_t)-1)
    {
        perror("[derandomizer] lseek64(mem,rd) failed");
        exit(1);
    }
    return read(mem_fd, buf, len);
}

ssize_t put_user_mem(arg_t addr, char *buf, int len)
{
    ssize_t cpy_len = 0;
    #define WS  4
    while(len >= WS)
    {
        if(ptrace(PTRACE_POKEDATA, child_pid, addr, *(long *)buf) < 0)
            return cpy_len;
        addr += WS;
        buf += WS;
        len -= WS;
        cpy_len += WS;
    }
    if(len != 0)
    {
        long tmp = ptrace(PTRACE_PEEKDATA, child_pid, addr, 0);
        memcpy(&tmp, buf, len);
        if(ptrace(PTRACE_POKEDATA, child_pid, addr, tmp) < 0)
            return cpy_len;
        cpy_len += len;
    }
    #undef WS
    return cpy_len;
}

#if __WORDSIZE == 64
bool is_32bit_syscall(struct user_regs_struct *regs)
{
    if(regs->cs == 0x23)
        return true; /* 32-bit CPU mode */
    if(regs->cs != 0x33)
    {
        printf("[derandomizer] unknown syscall type\n");
        return false;
    }
    uint16_t instr;
    if(read_user_mem(regs->rip - 2, (char *)&instr, 2) != 2)
        return false;
    switch(instr)
    {
        case 0x050f: return false;
        case 0x80cd: return true;
        default: return false;
    }
}
#endif

void exec_child(int argc, char **argv)
{
    (void) argc;
    execve(argv[0], argv, NULL);
}

int main(int argc, char **argv)
{
    int rand_read_fd = -1;
    bool provide_rand = false;
    int rand_write_fd = -1;
    bool log_rand = false;
    int time_read_fd = -1;
    bool provide_time = false;
    int time_write_fd = -1;
    bool log_time = false;
    int dev_random_fd = -1;
    /* the first syscall is exec, which exists at the end, so from out point of view,
     * the first syscall is an exit because the next syscall is an actual entry */
    bool syscall_entry = false;

    if(argc < 2)
    {
        printf("usage: %s <opt> <program> [<args>]\n", argv[0]);
        printf("options:\n");
        printf("\t-r <file>\tRead random data from <file>\n");
        printf("\t-w <file>\tWrite random data to <file>\n");
        printf("\t-rt <file>\tRead time data from <file>\n");
        printf("\t-wt <file>\tWrite time data to <file>\n");
        return 1;
    }

    argc--;
    argv++;

    while(argc >= 2)
    {
        if(strcmp(argv[0], "-r") == 0)
        {
            rand_read_fd = open(argv[1], O_RDONLY);
            if(rand_read_fd < 0)
            {
                perror("[derandomizer] Cannot open input random data file");
                return 1;
            }
            argc -= 2;
            argv += 2;
            provide_rand = true;
        }
        else if(strcmp(argv[0], "-w") == 0)
        {
            rand_write_fd = open(argv[1], O_CREAT|O_WRONLY|O_TRUNC,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            if(rand_write_fd < 0)
            {
                perror("[derandomizer] Cannot open output random data file");
                return 1;
            }
            argc -= 2;
            argv += 2;
            log_rand = true;
        }
        else if(strcmp(argv[0], "-rt") == 0)
        {
            time_read_fd = open(argv[1], O_RDONLY);
            if(time_read_fd < 0)
            {
                perror("[derandomizer] Cannot open input time data file");
                return 1;
            }
            argc -= 2;
            argv += 2;
            provide_time = true;
        }
        else if(strcmp(argv[0], "-wt") == 0)
        {
            time_write_fd = open(argv[1], O_CREAT|O_WRONLY|O_TRUNC,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            if(time_write_fd < 0)
            {
                perror("[derandomizer] Cannot open output time data file");
                return 1;
            }
            argc -= 2;
            argv += 2;
            log_time = true;
        }
        else
            break;
    }

    if(argc == 0)
    {
        printf("[derandomizer] Invalid command line\n");
        return 1;
    }

    struct utsname uts;
    if(uname(&uts) < 0)
    {
        perror("[derandomizer] uname failed\n");
        return 1;
    }
    #if __WORDSIZE == 64
    if(strcmp(uts.machine, "x86_64") != 0)
    #elif __WORDSIZE == 32
    if(strcmp(uts.machine, "i386") != 0 && strcmp(uts.machine, "i686") != 0)
    #else
    #error error
    #endif
    {
        printf("[derandomizer] Program compiled for %s but running machine is %s\n",
        #if __WORDSIZE == 64
            "x86_64",
        #else
            "i386/i686",
        #endif
            uts.machine);
        return 1;
    }

    child_pid = fork();
    if(child_pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if(child_pid == 0)
    {
        if(ptrace(PTRACE_TRACEME, 0, NULL, NULL) < 0)
        {
            perror("[derandomizer] ptrace(traceme) failed\n");
            return 1;
        }
        /* make sure the other process is ready */
        raise(SIGSTOP);
        exec_child(argc, argv);
        return 1;
    }

    while(true)
    {
        struct rusage rus;
        int stat;
        pid_t p = wait4(child_pid, &stat, WUNTRACED, &rus);
        if(p < 0 || p != child_pid)
        {
            perror("[derandomizer] wait4 failed or bugged");
            break;
        }
        
        Lanalyze:
        if(!WIFSTOPPED(stat))
            break;
        if(WSTOPSIG(stat) != SIGTRAP)
        {
            ptrace(PTRACE_SYSCALL, child_pid, NULL, NULL);
            continue;
        }
        
        struct user_regs_struct regs;
        if(ptrace(PTRACE_GETREGS, child_pid, NULL, &regs) < 0)
        {
            perror("[derandomizer] ptrace(getregs) failed\n");
            break;
        }
        
        arg_t syscall, arg1, arg2, arg3, result;
        #if __WORDSIZE == 64
        bool _32bit_syscall = is_32bit_syscall(&regs);
        syscall = regs.orig_rax;
        if(_32bit_syscall)
        {
            arg1 = regs.rbx;
            arg2 = regs.rcx;
            arg3 = regs.rdx;
            syscall = translate_32_to_64_syscall(syscall);
        }
        else
        {
            arg1 = regs.rdi;
            arg2 = regs.rsi;
            arg3 = regs.rdx;
        }
        result = regs.rax;
        #elif __WORDSIZE == 32
        syscall = regs.orig_eax;
        arg1 = regs.ebx;
        arg2 = regs.ecx;
        arg3 = regs.edx;
        result = regs.eax;
        #endif
        if(syscall == __NR_open)
        {
            if(syscall_entry && provide_rand)
            {
                char buf[128];
                if(read_user_mem(arg1, buf, 128) == 128 &&
                    (strcmp(buf, "/dev/random") == 0 || strcmp(buf, "/dev/urandom") == 0))
                {
                    put_user_mem(arg1, "/dev/zero", strlen("/dev/zero") + 1);
                    syscall_entry = false;
                    ptrace(PTRACE_SYSCALL, child_pid, NULL, NULL);
                    wait4(child_pid, &stat, WUNTRACED, &rus);
                    put_user_mem(arg1, buf, strlen(buf));
                    goto Lanalyze;
                }
            }
            if(!syscall_entry)
            {
                char buf[128];
                if(read_user_mem(arg1, buf, 128) == 128 &&
                    (strcmp(buf, "/dev/random") == 0 || strcmp(buf, "/dev/urandom") == 0))
                {
                    if(dev_random_fd != -1)
                        printf("[derandomizer] /dev/random opened several times !\n");
                    dev_random_fd = result;
                }
            }
        }
        else if(syscall == __NR_read)
        {
            if(arg1 == (arg_t)dev_random_fd && provide_rand && !syscall_entry)
            {
                char *data = malloc(arg3);
                if(data && read(rand_read_fd, data, arg3) == (ssize_t)arg3 &&
                        put_user_mem(arg2, data, arg3) == (ssize_t)arg3)
                    result = arg3;
                else
                    result = -1;
                free(data);
                #if __WORDSIZE == 64
                regs.rax = result;
                #elif __WORDSIZE == 32
                regs.eax = result;
                #endif
                if(ptrace(PTRACE_SETREGS, child_pid, NULL, &regs) < 0)
                {
                    perror("[derandomizer] ptrace(setregs) failed\n");
                    break;
                }
            }
            if(arg1 == (arg_t)dev_random_fd && log_rand && !syscall_entry)
            {
                char *data = malloc(arg3);
                if(data && read_user_mem(arg2, data, arg3) == (ssize_t)arg3)
                    if(write(rand_write_fd, data, arg3) != (ssize_t)arg3)
                        printf("[derandomizer] Failure to log random data\n");
                free(data);
            }
        }
        else if(syscall == __NR_close)
        {
            if(arg1 == (arg_t)dev_random_fd)
                dev_random_fd = -1;
        }
        else if(syscall == __NR_time && !syscall_entry)
        {
            if(log_time)
            {
                if(write(time_write_fd, &result, sizeof result) != sizeof result)
                    printf("[derandomizer] Failure to log time data\n");
            }
            if(provide_time)
            {
                if(read(time_read_fd, &result, sizeof result) != sizeof result)
                    result = -1;
                if(arg1 != 0 && put_user_mem(arg1, (char *)&result, sizeof result) != sizeof result)
                    result = -1;
                #if __WORDSIZE == 64
                regs.rax = result;
                #elif __WORDSIZE == 32
                regs.eax = result;
                #endif
                if(ptrace(PTRACE_SETREGS, child_pid, NULL, &regs) < 0)
                {
                    perror("[derandomizer] ptrace(setregs) failed\n");
                    break;
                }
            }
        }

        syscall_entry = !syscall_entry;
        ptrace(PTRACE_SYSCALL, child_pid, NULL, NULL);
    }

    return 0;
}
