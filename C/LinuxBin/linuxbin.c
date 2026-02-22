#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct Elf64Header
{
    char elfMagicNumber[4]; // "\x7fELF"
    uint8_t bitAmount;      // 1: 32-bit, 2: 64-bit
    uint8_t endian;         // 1: little endian, 2: big endian
    uint8_t elfVersion1;    // must be 1
    uint8_t osAbi;          // 0: Unspecified, 1: HP-UX, 2: NetBSD, 3: Linux, etc.
    uint8_t abiVersion;     // in statically linked executables has no effect. In dynamically linked executables, if OS_ABI==3, defines dynamic linker features
    uint8_t unused[7];
    uint16_t objFileType;      // 0: ET_NONE No file type, 1: ET_REL Relocatable file, 2: ET_EXEC Executable file, 3: ET_DYN Shared object file, 4: ET_CORE Core file, etc.
    uint16_t arch;             // 0x3E: AMD64
    uint32_t elfVersion2;      // the elf version again, must be 1
    uint64_t entryPointOffset; // entry point from where the process should start executing
    uint64_t phtOffset;        // start of the program header table
    uint64_t shtOffset;        // start of the section header table
    uint32_t processorFlags;   // processor-specific flags
    uint16_t headerSize;       // the size of this header
    uint16_t phtEntrySize;     // the size of one PHT entry
    uint16_t numPhtEntries;    // num entries in the PHT
    uint16_t shtEntrySize;     // the size of one SHT entry
    uint16_t numShtEntries;    // num entries in the SHT
    uint16_t namesSht;         // the index of the SHT entry that contains the section names
} Elf64Header;

typedef struct Elf64_PhtEntry
{
    uint32_t segmentType; // 1: loadable segment, 2: dynamic linking info
    uint32_t flags;       // segment-dependent flags (position for 64-bit structure)
    uint64_t offset;      // offset of the segment in the file image
    uint64_t vaddr;       // virtual address of the segment in memory
    uint64_t paddr;       // on systems where the physical address is relevant, reserved for the physical address of the segment
    uint64_t sizeInFile;  // size of the segment in the file image
    uint64_t sizeInMem;   // size of the segment in memory
    uint64_t align;       // 0 and 1 specify no alignment. Otherwise should be a positive, integral power of 2, with 'vaddr' equating 'offset' modulus 'p_align'
} Elf64_PhtEntry;

int main()
{
    const char msgStr[] = "Holi Canoli XD\n";

    uint32_t msgSize = sizeof(msgStr) + 1; 
    uint8_t *byte0 = (uint8_t *)&msgSize;
    uint8_t *byte1 = byte0 + 1;
    uint8_t *byte2 = byte1 + 1;
    uint8_t *byte3 = byte2 + 1;

    const unsigned char asmCode[] = {
        0xb8, 0x01, 0x00, 0x00, 0x00,                           // mov rax, 1 (syscall: write)
        0xbf, 0x01, 0x00, 0x00, 0x00,                           // mov rdi, 1 (stdout)
        0x48, 0x8d, 0x35, 0x10, 0x0, 0x0, 0x0,                  // lea rsi, [rel msgStr]
        0xba, *byte0, *(byte0 + 1), *(byte0 + 2), *(byte0 + 3), // mov rex, sizeof(msgStr)
        0x0f, 0x05,                                             // syscall
        0xb8, 0x3c, 0x00, 0x00, 0x00,                           // mov eax, 3c
        0x48, 0x31, 0xff,                                       // xor rdi, rdi
        0x0f, 0x05                                              // syscall
    };

    const int headersSize = sizeof(Elf64Header) + sizeof(Elf64_PhtEntry);
    const int codeSize = sizeof(asmCode);
    const int fileSize = headersSize + codeSize + sizeof(msgStr);

    Elf64Header header = {
        .elfMagicNumber = {0x7F, 'E', 'L', 'F'},
        .bitAmount = 2, // 64-bit
        .endian = 1,    // little endian
        .elfVersion1 = 1,
        .osAbi = 3, // linux
        .abiVersion = 0,
        .unused = {0, 0, 0, 0, 0, 0, 0},
        .objFileType = 2, // Executable
        .arch = 0x3E,     // 62: AMD x86-64 architecture
        .elfVersion2 = 1,
        .entryPointOffset = 0x400000 + headersSize,
        .phtOffset = sizeof(Elf64Header),
        .shtOffset = 0,
        .processorFlags = 0,
        .headerSize = 64,
        .phtEntrySize = sizeof(Elf64_PhtEntry),
        .numPhtEntries = 1,
        .shtEntrySize = 0,
        .numShtEntries = 0, // 1,
        .namesSht = 0};

    Elf64_PhtEntry phtEntry = {
        .segmentType = 1, // 1: PT_LOAD
        .flags = 0x7,     // 1: execute, 2: write, 4: read, 1+2+4: xrw
        .offset = headersSize,
        .vaddr = 0x400000 + headersSize, // linux
        .paddr = 0x400000 + headersSize,
        .sizeInFile = codeSize,
        .sizeInMem = codeSize,
        .align = 0x1000};

    FILE *file = fopen("raw_exe", "w");

    fwrite(&header, 1, sizeof(header), file);
    fwrite(&phtEntry, 1, sizeof(phtEntry), file);
    fwrite(asmCode, 1, sizeof(asmCode), file);
    fwrite(msgStr, 1, sizeof(msgStr), file);

    fclose(file);
}