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
            perror("open(mem,rd) failed\n");
            exit(1);
        }
    }
    if(lseek64(mem_fd, addr, SEEK_SET) == (off64_t)-1)
    {
        perror("lseek64(mem,rd) failed");
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

int main(int argc, char **argv)
{
    int log_fd;
    bool intercept_read = false;
    bool intercept_write = false;
    int dev_random_fd = -1;
    /* the first syscall is exec, which exists at the end, so from out point of view,
     * the first syscall is an exit because the next syscall is an actual entry */
    bool syscall_entry = false;

    if(argc < 4)
    {
        printf("usage: %s <opt> <file> <program> [<args>]\n", argv[0]);
        printf("options:\n");
        printf("\t-r\tRead random data from file\n");
        printf("\t-w\tWrite random data to file\n");
        return 1;
    }

    if(strcmp(argv[1], "-r") == 0)
        intercept_read = true;
    else if(strcmp(argv[1], "-w") == 0)
        intercept_write = true;
    else
    {
        printf("Unknown option '%s'\n", argv[1]);
        return 1;
    }

    struct utsname uts;
    if(uname(&uts) < 0)
    {
        perror("uname failed\n");
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
        printf("Program compiled for %s but running machine is %s\n",
        #if __WORDSIZE == 64
            "x86_64",
        #else
            "i386/i686",
        #endif
            uts.machine);
        return 1;
    }

    int flags = 0;
    if(intercept_read)
        flags |= O_RDONLY;
    if(intercept_write)
        flags |= O_CREAT|O_WRONLY|O_TRUNC;
    log_fd = open(argv[2], flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(log_fd < 0)
    {
        perror("Cannot open random data file");
        return 1;
    }

    child_pid = fork();
    if(child_pid < 0)
    {
        perror("fork failed");
        close(log_fd);
        return 1;
    }

    if(child_pid == 0)
    {
        if(ptrace(PTRACE_TRACEME, 0, NULL, NULL) < 0)
        {
            perror("ptrace(traceme) failed\n");
            return 1;
        }
        /* make sure the other process is ready */
        raise(SIGSTOP);
        execve(argv[3], &argv[4], NULL);
        return 1;
    }

    while(true)
    {
        struct rusage rus;
        int stat;
        pid_t p = wait4(child_pid, &stat, WUNTRACED, &rus);
        if(p < 0 || p != child_pid)
        {
            perror("wait4 failed or bugged");
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
            perror("ptrace(getregs) failed\n");
            break;
        }

        #if __WORDSIZE == 64
        arg_t syscall = regs.orig_rax;
        arg_t arg1 = regs.rdi;
        arg_t arg2 = regs.rsi;
        arg_t arg3 = regs.rdx;
        arg_t result = regs.rax;
        #elif __WORDSIZE == 32
        arg_t syscall = regs.orig_eax;
        arg_t arg1 = regs.ebx;
        arg_t arg2 = regs.ecx;
        arg_t arg3 = regs.edx;
        arg_t result = regs.eax;
        #endif
        if(syscall == __NR_open)
        {
            if(syscall_entry && intercept_read)
            {
                char buf[128];
                if(read_user_mem(arg1, buf, 128) == 128 && strcmp(buf, "/dev/random") == 0)
                {
                    put_user_mem(arg1, "/dev/zero", strlen("/dev/zero") + 1);
                    syscall_entry = false;
                    ptrace(PTRACE_SYSCALL, child_pid, NULL, NULL);
                    wait4(child_pid, &stat, WUNTRACED, &rus);
                    put_user_mem(arg1, "/dev/random", strlen("/dev/random"));
                    goto Lanalyze;
                }
            }
            if(!syscall_entry)
            {
                char buf[128];
                if(read_user_mem(arg1, buf, 128) == 128 && strcmp(buf, "/dev/random") == 0)
                {
                    if(dev_random_fd != -1)
                        printf("[devrandomizer] /dev/random opened several times !\n");
                    dev_random_fd = result;
                }
            }
        }
        else if(syscall == __NR_read)
        {
            if(arg1 == (arg_t)dev_random_fd && intercept_read && !syscall_entry)
            {
                char *data = malloc(arg3);
                if(data && read(log_fd, data, arg3) == (ssize_t)arg3 &&
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
                    perror("ptrace(setregs) failed\n");
                    break;
                }
            }
            if(arg1 == (arg_t)dev_random_fd && intercept_write && !syscall_entry)
            {
                char *data = malloc(arg3);
                if(data && read_user_mem(arg2, data, arg3) == (ssize_t)arg3)
                    if(write(log_fd, data, arg3) != (ssize_t)arg3)
                        printf("[devrandomizer] log write failure\n");
                free(data);
            }
        }
        else if(syscall == __NR_close)
        {
            if(arg1 == (arg_t)dev_random_fd)
                dev_random_fd = -1;
        }

        syscall_entry = !syscall_entry;
        ptrace(PTRACE_SYSCALL, child_pid, NULL, NULL);
    }

    close(log_fd);
    return 0;
}
