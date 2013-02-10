/* from ReactOS */

#define IMAGE_SIZEOF_FILE_HEADER	20
#define IMAGE_FILE_RELOCS_STRIPPED	1
#define IMAGE_FILE_EXECUTABLE_IMAGE	2
#define IMAGE_FILE_LINE_NUMS_STRIPPED	4
#define IMAGE_FILE_LOCAL_SYMS_STRIPPED	8
#define IMAGE_FILE_AGGRESIVE_WS_TRIM 	16
#define IMAGE_FILE_LARGE_ADDRESS_AWARE	32
#define IMAGE_FILE_uint8_tS_REVERSED_LO	128
#define IMAGE_FILE_32BIT_MACHINE	256
#define IMAGE_FILE_DEBUG_STRIPPED	512
#define IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP	1024
#define IMAGE_FILE_NET_RUN_FROM_SWAP	2048
#define IMAGE_FILE_SYSTEM	4096
#define IMAGE_FILE_DLL	8192
#define IMAGE_FILE_UP_SYSTEM_ONLY	16384
#define IMAGE_FILE_uint8_tS_REVERSED_HI	32768
#define IMAGE_FILE_MACHINE_UNKNOWN	0

#define IMAGE_DOS_SIGNATURE 0x5A4D
#define IMAGE_NT_SIGNATURE 0x00004550
#define IMAGE_NT_OPTIONAL_HDR32_MAGIC 0x10b
#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES 16
#define IMAGE_SIZEOF_SHORT_NAME 8

#define IMAGE_SUBSYSTEM_UNKNOWN                      0
#define IMAGE_SUBSYSTEM_NATIVE                       1
#define IMAGE_SUBSYSTEM_WINDOWS_GUI                  2
#define IMAGE_SUBSYSTEM_WINDOWS_CUI                  3
#define IMAGE_SUBSYSTEM_OS2_CUI                      5
#define IMAGE_SUBSYSTEM_POSIX_CUI                    7
#define IMAGE_SUBSYSTEM_NATIVE_WINDOWS               8
#define IMAGE_SUBSYSTEM_WINDOWS_CE_GUI               9
#define IMAGE_SUBSYSTEM_EFI_APPLICATION             10
#define IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER     11
#define IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER          12
#define IMAGE_SUBSYSTEM_EFI_ROM                     13
#define IMAGE_SUBSYSTEM_XBOX                        14

#define IMAGE_DLLCHARACTERISTICS_NO_ISOLATION 0x0200
#define IMAGE_DLLCHARACTERISTICS_NO_SEH 0x0400
#define IMAGE_DLLCHARACTERISTICS_NO_BIND 0x0800
#define IMAGE_DLLCHARACTERISTICS_WDM_DRIVER 0x2000
#define IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE 0x8000
#define IMAGE_FIRST_SECTION(h) ((PIMAGE_SECTION_HEADER) ((uint32_t_PTR)h+FIELD_OFFSET(IMAGE_NT_HEADERS,OptionalHeader)+((PIMAGE_NT_HEADERS)(h))->FileHeader.SizeOfOptionalHeader))
#define IMAGE_DIRECTORY_ENTRY_EXPORT	0
#define IMAGE_DIRECTORY_ENTRY_IMPORT	1
#define IMAGE_DIRECTORY_ENTRY_RESOURCE	2
#define IMAGE_DIRECTORY_ENTRY_EXCEPTION	3
#define IMAGE_DIRECTORY_ENTRY_SECURITY	4
#define IMAGE_DIRECTORY_ENTRY_BASERELOC	5
#define IMAGE_DIRECTORY_ENTRY_DEBUG	6
#define IMAGE_DIRECTORY_ENTRY_COPYRIGHT	7
#define IMAGE_DIRECTORY_ENTRY_GLOBALPTR	8
#define IMAGE_DIRECTORY_ENTRY_TLS	9
#define IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG	10
#define IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT	11
#define IMAGE_DIRECTORY_ENTRY_IAT	12
#define IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT	13
#define IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR	14
#define IMAGE_SCN_TYPE_REG 0
#define IMAGE_SCN_TYPE_DSECT 1
//#define IMAGE_SCN_TYPE_NOLOAD 2
#define IMAGE_SCN_TYPE_GROUP 4
#define IMAGE_SCN_TYPE_NO_PAD 8
#define IMAGE_SCN_CNT_CODE 32
#define IMAGE_SCN_CNT_INITIALIZED_DATA 64
#define IMAGE_SCN_CNT_UNINITIALIZED_DATA 128
#define IMAGE_SCN_COMPRESSED 0x00002000
#define IMAGE_SCN_LNK_OTHER 256
#define IMAGE_SCN_LNK_INFO 512
#define IMAGE_SCN_LNK_REMOVE 2048
#define IMAGE_SCN_LNK_COMDAT 4096
#define IMAGE_SCN_MEM_FARDATA 0x8000
#define IMAGE_SCN_MEM_PURGEABLE 0x20000
#define IMAGE_SCN_MEM_16BIT 0x20000
#define IMAGE_SCN_MEM_LOCKED  0x40000
#define IMAGE_SCN_MEM_PRELOAD 0x80000
#define IMAGE_SCN_ALIGN_1uint8_tS 0x100000
#define IMAGE_SCN_ALIGN_2uint8_tS 0x200000
#define IMAGE_SCN_ALIGN_4uint8_tS 0x300000
#define IMAGE_SCN_ALIGN_8uint8_tS 0x400000
#define IMAGE_SCN_ALIGN_16uint8_tS 0x500000
#define IMAGE_SCN_ALIGN_32uint8_tS 0x600000
#define IMAGE_SCN_ALIGN_64uint8_tS 0x700000
#define IMAGE_SCN_LNK_NRELOC_OVFL 0x1000000
#define IMAGE_SCN_MEM_DISCARDABLE 0x2000000
#define IMAGE_SCN_MEM_NOT_CACHED 0x4000000
#define IMAGE_SCN_MEM_NOT_PAGED 0x8000000
#define IMAGE_SCN_MEM_SHARED 0x10000000
#define IMAGE_SCN_MEM_EXECUTE 0x20000000
#define IMAGE_SCN_MEM_READ 0x40000000
#define IMAGE_SCN_MEM_WRITE 0x80000000

#define IMAGE_FILE_MACHINE_I386       0x14c
#define IMAGE_FILE_MACHINE_ARM        0x01c0  // ARM Little-Endian
#define IMAGE_FILE_MACHINE_THUMB      0x01c2
#define IMAGE_FILE_MACHINE_AMD64      0x8664

#define IS_INTRESOURCE(i) (((uint32_t *)(i) >> 16) == 0)
#define MAKEINTRESOURCEA(i) (char *)((uint32_t *)((uint16_t)(i)))
#define MAKEINTRESOURCEW(i) (wchar_t *)((uint32_t *)((uint16_t)(i)))
#define MAKEINTRESOURCE(i) MAKEINTRESOURCEA(i)

#define RT_CURSOR MAKEINTRESOURCE(1)
#define RT_FONT MAKEINTRESOURCE(8)
#define RT_BITMAP MAKEINTRESOURCE(2)
#define RT_ICON MAKEINTRESOURCE(3)
#define RT_MENU MAKEINTRESOURCE(4)
#define RT_DIALOG MAKEINTRESOURCE(5)
#define RT_STRING MAKEINTRESOURCE(6)
#define RT_FONTDIR MAKEINTRESOURCE(7)
#define RT_ACCELERATOR MAKEINTRESOURCE(9)
#define RT_RCDATA MAKEINTRESOURCE(10)
#define RT_MESSAGETABLE MAKEINTRESOURCE(11)
#define DIFFERENCE 11
#define RT_GROUP_CURSOR MAKEINTRESOURCE((uint32_t *)RT_CURSOR+DIFFERENCE)
#define RT_GROUP_ICON MAKEINTRESOURCE((uint32_t *)RT_ICON+DIFFERENCE)
#define RT_VERSION MAKEINTRESOURCE(16)
#define RT_DLGINCLUDE MAKEINTRESOURCE(17)
#define RT_PLUGPLAY MAKEINTRESOURCE(19)
#define RT_VXD MAKEINTRESOURCE(20)
#define RT_ANICURSOR MAKEINTRESOURCE(21)
#define RT_ANIICON MAKEINTRESOURCE(22)
#define RT_HTML MAKEINTRESOURCE(23)

typedef struct _IMAGE_DOS_HEADER {
    uint16_t e_magic;
    uint16_t e_cblp;
    uint16_t e_cp;
    uint16_t e_crlc;
    uint16_t e_cparhdr;
    uint16_t e_minalloc;
    uint16_t e_maxalloc;
    uint16_t e_ss;
    uint16_t e_sp;
    uint16_t e_csum;
    uint16_t e_ip;
    uint16_t e_cs;
    uint16_t e_lfarlc;
    uint16_t e_ovno;
    uint16_t e_res[4];
    uint16_t e_oemid;
    uint16_t e_oeminfo;
    uint16_t e_res2[10];
    uint32_t e_lfanew;
} __attribute__((packed)) IMAGE_DOS_HEADER,*PIMAGE_DOS_HEADER;

typedef struct _IMAGE_FILE_HEADER {
    uint16_t Machine;
    uint16_t NumberOfSections;
    uint32_t TimeDateStamp;
    uint32_t PointerToSymbolTable;
    uint32_t NumberOfSymbols;
    uint16_t SizeOfOptionalHeader;
    uint16_t Characteristics;
} __attribute__((packed)) IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

typedef struct _IMAGE_DATA_DIRECTORY  {
    uint32_t VirtualAddress;
    uint32_t Size;
} __attribute__((packed)) IMAGE_DATA_DIRECTORY,*PIMAGE_DATA_DIRECTORY;

typedef struct _IMAGE_OPTIONAL_HEADER32  {
    uint16_t Magic;
    uint8_t MajorLinkerVersion;
    uint8_t MinorLinkerVersion;
    uint32_t SizeOfCode;
    uint32_t SizeOfInitializedData;
    uint32_t SizeOfUninitializedData;
    uint32_t AddressOfEntryPoint;
    uint32_t BaseOfCode;
    uint32_t BaseOfData;
    uint32_t ImageBase;
    uint32_t SectionAlignment;
    uint32_t FileAlignment;
    uint16_t MajorOperatingSystemVersion;
    uint16_t MinorOperatingSystemVersion;
    uint16_t MajorImageVersion;
    uint16_t MinorImageVersion;
    uint16_t MajorSubsystemVersion;
    uint16_t MinorSubsystemVersion;
    uint32_t Win32VersionValue;
    uint32_t SizeOfImage;
    uint32_t SizeOfHeaders;
    uint32_t CheckSum;
    uint16_t Subsystem;
    uint16_t DllCharacteristics;
    uint32_t SizeOfStackReserve;
    uint32_t SizeOfStackCommit;
    uint32_t SizeOfHeapReserve;
    uint32_t SizeOfHeapCommit;
    uint32_t LoaderFlags;
    uint32_t NumberOfRvaAndSizes;
    IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} __attribute__((packed)) IMAGE_OPTIONAL_HEADER32,*PIMAGE_OPTIONAL_HEADER32;

typedef struct _IMAGE_NT_HEADERS32  {
    uint32_t Signature;
    IMAGE_FILE_HEADER FileHeader;
    IMAGE_OPTIONAL_HEADER32 OptionalHeader;
} __attribute__((packed)) IMAGE_NT_HEADERS32,*PIMAGE_NT_HEADERS32;

typedef struct _IMAGE_SECTION_HEADER {
    char Name[IMAGE_SIZEOF_SHORT_NAME];
    union {
        uint32_t PhysicalAddress;
        uint32_t VirtualSize;
    } Misc;
    uint32_t VirtualAddress;
    uint32_t SizeOfRawData;
    uint32_t PointerToRawData;
    uint32_t PointerToRelocations;
    uint32_t PointerToLinenumbers;
    uint16_t NumberOfRelocations;
    uint16_t NumberOfLinenumbers;
    uint32_t Characteristics;
} IMAGE_SECTION_HEADER,*PIMAGE_SECTION_HEADER;

typedef struct _IMAGE_EXPORT_DIRECTORY {
    uint32_t Characteristics;
    uint32_t TimeDateStamp;
    uint16_t MajorVersion;
    uint16_t MinorVersion;
    uint32_t Name;
    uint32_t Base;
    uint32_t NumberOfFunctions;
    uint32_t NumberOfNames;
    uint32_t AddressOfFunctions;
    uint32_t AddressOfNames;
    uint32_t AddressOfNameOrdinals;
} IMAGE_EXPORT_DIRECTORY,*PIMAGE_EXPORT_DIRECTORY;

typedef struct _IMAGE_RESOURCE_DIRECTORY {
    uint32_t Characteristics;
    uint32_t TimeDateStamp;
    uint16_t MajorVersion;
    uint16_t MinorVersion;
    uint16_t NumberOfNamedEntries;
    uint16_t NumberOfIdEntries;
} IMAGE_RESOURCE_DIRECTORY, *PIMAGE_RESOURCE_DIRECTORY;

typedef struct _IMAGE_RESOURCE_DIRECTORY_ENTRY {
    uint32_t Name;
    uint32_t OffsetToData;
} IMAGE_RESOURCE_DIRECTORY_ENTRY, *PIMAGE_RESOURCE_DIRECTORY_ENTRY;

typedef struct _IMAGE_RESOURCE_DATA_ENTRY {
    uint32_t OffsetToData;
    uint32_t Size;
    uint32_t CodePage;
    uint32_t Reserved;
} IMAGE_RESOURCE_DATA_ENTRY, *PIMAGE_RESOURCE_DATA_ENTRY;

typedef struct _IMAGE_RESOURCE_DIR_STRING_U {
    uint16_t Length;
    uint16_t NameString[ 1 ];
} IMAGE_RESOURCE_DIR_STRING_U, *PIMAGE_RESOURCE_DIR_STRING_U;

typedef struct _IMAGE_IMPORT_BY_NAME {
    uint16_t Hint;
    char Name[1];
} IMAGE_IMPORT_BY_NAME,*PIMAGE_IMPORT_BY_NAME;

typedef struct _IMAGE_RUNTIME_FUNCTION_ENTRY {
    uint32_t BeginAddress;
    uint32_t EndAddress;
    uint32_t ExceptionHandler;
    uint32_t HandlerData;
    uint32_t PrologEndAddress;
} IMAGE_RUNTIME_FUNCTION_ENTRY,*PIMAGE_RUNTIME_FUNCTION_ENTRY;

typedef struct _IMAGE_THUNK_DATA32 {
    union {
        uint32_t ForwarderString;
        uint32_t Function;
        uint32_t Ordinal;
        uint32_t AddressOfData;
    } u1;
} IMAGE_THUNK_DATA32;
typedef IMAGE_THUNK_DATA32 *PIMAGE_THUNK_DATA32;

#define IMAGE_ORDINAL_FLAG32 0x80000000
#define IMAGE_ORDINAL32(Ordinal) ((Ordinal) & 0xffff)
#define IMAGE_SNAP_BY_ORDINAL32(Ordinal) (((Ordinal) & IMAGE_ORDINAL_FLAG32)!=0)

typedef struct _IMAGE_IMPORT_DESCRIPTOR {
    union {
	uint32_t Characteristics;
	uint32_t OriginalFirstThunk;
    }u;
    uint32_t TimeDateStamp;
    uint32_t ForwarderChain;
    uint32_t Name;
    uint32_t FirstThunk;
} IMAGE_IMPORT_DESCRIPTOR,*PIMAGE_IMPORT_DESCRIPTOR;
