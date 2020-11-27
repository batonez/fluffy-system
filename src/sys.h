#pragma once

#include <sys/stat.h>

#define JX_STDOUT 1

//jxopen
#define JX_O_RDONLY 0x0000
#define JX_O_WRTONLY 0x0001
#define JX_O_RDWR 0x0002
#define JX_O_CREAT 0x0200
#define JX_O_TRUNCATE 0x0400

// jxmmap
#define JX_PROT_NONE 0x00  /* no permissions */
#define JX_PROT_READ 0x01  /* pages can be read */
#define JX_PROT_WRITE  0x02  /* pages can be written */
#define JX_PROT_EXEC 0x04  /* pages can be executed */
#define JX_MAP_SHARED  0x0001    /* share changes */
#define JX_MAP_PRIVATE 0x0002    /* changes are private */
#define JX_MAP_FILE  0x0000  /* map from file (default) */
#define JX_MAP_ANON  0x1000  /* allocated from memory, swap space, macos only */

#define JX_PAGE_SIZE 4096 // not necessarily true, better to define at runtime via sysctl call

unsigned jxwrite(int fd, const void* buff, unsigned long size);
unsigned jxread(int fd, void* buff, unsigned long size);
int jxopen(const char* path, int flags, int mode);
int jxclose(int fd);
void* jxmmap(void* addr, unsigned long len, int prot, int flags, int fd, unsigned long pos);
int jxmunmap(void* addr, unsigned long len);
int jxstat(const char* path, struct stat64* filestat);
int jxfstat(int fd, struct stat64* filestat);

