#pragma once

unsigned jxstrlength(const char* str);
int jxwritestr(int fd, const char* buf);
unsigned jxinttostr(int integer, char* out);
void* jxalloc(unsigned long* size);
void jxdealloc(void* ptr, unsigned long size);
unsigned long jxgetfilesize(int fd);

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

