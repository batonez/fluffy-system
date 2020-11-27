#pragma once

#define JX_RAND_MAX 4242
#define JX_EOF -1

unsigned jxstrlength(const char* str);
int jxwritestr(int fd, const char* buf);
char jxreadchar(int fd);
unsigned jxreadline(int fd, char* buf, unsigned size);
unsigned jxinttostr(int integer, char* out);
unsigned jxstrtoint(const char* in, int* result);
void* jxalloc(unsigned long* size);
void jxdealloc(void* ptr, unsigned long size);
unsigned long jxgetfilesize(int fd);
int jxpow(int base, unsigned exp);
int jxrand(void);
void jxsrand(unsigned int seed);

static inline void jxswap(int* a, int* b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

static inline int jxround(float a)
{
  a += a - (int) a;
  return (int) a;
}

static inline int jxabs(int a)
{
  if (a < 0)
    return -a;
  return a;
}

