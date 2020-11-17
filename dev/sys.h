#define STDOUT 1

//jopen
#define O_RDONLY 0x0000
#define O_WRTONLY 0x0001
#define O_RDWR 0x0002
#define O_CREAT 0x0200
#define O_TRUNCATE 0x0400

// jmmap
#define PROT_NONE 0x00  /* no permissions */
#define PROT_READ 0x01  /* pages can be read */
#define PROT_WRITE  0x02  /* pages can be written */
#define PROT_EXEC 0x04  /* pages can be executed */
#define MAP_SHARED  0x0001    /* share changes */
#define MAP_PRIVATE 0x0002    /* changes are private */
#define MAP_FILE  0x0000  /* map from file (default) */
#define MAP_ANON  0x1000  /* allocated from memory, swap space, macos only */

#define PAGE_SIZE 4096 // not necessarily true, better to define at runtime via sysctl call

unsigned jwrite(int fd, const char* buff, unsigned long size);
unsigned jread(int fd, char* buff, unsigned long size);
int jopen(const char* path, int flags, int mode);
int jclose(int fd);
void* jmmap(void* addr, unsigned long len, int prot, int flags, int fd, unsigned long pos);
int jmunmap(void* addr, unsigned long len);
