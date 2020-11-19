unsigned jxstrlength(const char* str);
int jxwritestr(int fd, const char* buf);
unsigned jxinttostr(int integer, char* out);
void* jxalloc(unsigned long* size);
void jxdealloc(void* ptr, unsigned long size);
unsigned long jxgetfilesize(int fd);
