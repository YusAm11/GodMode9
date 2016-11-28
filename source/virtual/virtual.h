#pragma once

#include "common.h"
#include "dir.h"
#include "nand.h"

#define VRT_SYSNAND NAND_SYSNAND
#define VRT_EMUNAND NAND_EMUNAND
#define VRT_IMGNAND NAND_IMGNAND
#define VRT_MEMORY  (1<<10)
#define VRT_GAME    (1<<11)

#define VRT_SOURCE  (VRT_SYSNAND|VRT_EMUNAND|VRT_IMGNAND|VRT_MEMORY|VRT_GAME)

#define VFLAG_A9LH_AREA (1<<20)
#define VFLAG_DIR       (1<<21)
#define VFLAG_ROOT      (1<<22)

// virtual file flag (subject to change):
// bits 0...9  : reserved for NAND virtual sources and info
// bits 10...15: reserved for other virtual sources
// bits 16...19: reserved for external flags
// bits 20...31: reserved for internal flags (different per source)
typedef struct {
    char name[32];
    u64 offset; // must be a multiple of 0x200 (for NAND access)
    u64 size;
    u32 keyslot;
    u32 flags;
} __attribute__((packed)) VirtualFile;

// virtual dirs are only relevant for virtual game drives
typedef struct {
    int index;
    u64 offset;
    u64 size;
    u32 flags;
    u32 virtual_src;
} __attribute__((packed)) VirtualDir;

u32 GetVirtualSource(const char* path);
bool CheckVirtualDrive(const char* path);
bool GetVirtualFile(VirtualFile* vfile, const char* path);
bool FindVirtualFileBySize(VirtualFile* vfile, const char* path, u32 size);
bool GetVirtualDirContents(DirStruct* contents, const char* path, const char* pattern);
int ReadVirtualFile(const VirtualFile* vfile, u8* buffer, u32 offset, u32 count, u32* bytes_read);
int WriteVirtualFile(const VirtualFile* vfile, const u8* buffer, u32 offset, u32 count, u32* bytes_written);