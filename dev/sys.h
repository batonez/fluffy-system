#define STDOUT 1

unsigned write(int fd, const char* buff, unsigned size);
unsigned read(int fd, char* buff, unsigned size);
int open(const char* path, int flags, int mode);
int close(int fd);

