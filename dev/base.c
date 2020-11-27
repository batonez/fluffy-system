#include "sys.h"
#include "base.h"

static unsigned long int randnext = 13875920;

int jxrand(void)
{
  randnext = randnext * 11035143;
  return randnext % (JX_RAND_MAX + 1);
}

void jxsrand(unsigned int seed)
{
  randnext = seed;
}

char jxreadchar(int fd)
{
  char result;
  return jxread(fd, &result, 1) ? result : JX_EOF;
}

unsigned jxreadline(int fd, char* buf, unsigned size)
{
  unsigned sizeused = 0;
  char c = jxreadchar(fd);

  while (c != JX_EOF && c != '\n' && sizeused + 1 < size) {
    buf[sizeused++] = c;
    c = jxreadchar(fd);
  }

  if (c == JX_EOF)
    return JX_EOF;

  buf[sizeused++] = '\0';
  return sizeused;
}

unsigned jxstrlength(const char* str)
{
  int num = 0;
  while (*str != '\0') {
    num++;
    str++;
  }
  return num;
}

int jxwritestr(int fd, const char* buf)
{
  unsigned len = jxstrlength(buf);
  return jxwrite(fd, buf, len);
}

unsigned jxinttostr(int integer, char* out)
{
  unsigned num_symbols = 0;

  if (integer < 0) {
    integer = -integer;
    num_symbols++;
    out[0] = '-';
  }

  int copy = integer;

  do {
    copy /= 10;
    num_symbols++;
  } while (copy != 0);
 
  int i = 1;

  do {
    int digit = integer % 10;
    out[num_symbols - i++] = digit + 48;
    integer /= 10;
  } while (integer != 0);

  out[num_symbols++] = '\0';
  return num_symbols;
}

int jxpow(int base, unsigned exp)
{
  int result = 1;

  while (exp > 0) {
    result *= base;
    exp--;
  }

  return result;
}

unsigned jxstrtoint(const char* in, int* result)
{
  unsigned num_digits = 0;

  while (in[num_digits] != '\0')
    num_digits++;

  if (!num_digits)
    return 0;

  unsigned start = 0;
  if (in[0] == '-')
    start++;

  *result = 0;

  for (unsigned i = start; i < num_digits; i++) {
    *result += (in[i] - 48) * jxpow(10, (num_digits - 1 - i));
  }

  if (start)
    *result = - *result;

  return num_digits;
}

void* jxalloc(unsigned long* size)
{
  if (*size % JX_PAGE_SIZE)
    *size = (*size) / JX_PAGE_SIZE * JX_PAGE_SIZE + JX_PAGE_SIZE;

  void* ptr = jxmmap((void*) 1, *size, JX_PROT_WRITE | JX_PROT_READ, JX_MAP_PRIVATE | JX_MAP_ANON, -1, 0);

  if ((long) ptr < 0) {
    jxwritestr(JX_STDOUT, "Failed to allocate page\n");
    return 0;
  }

  return ptr;
}

void jxdealloc(void* ptr, unsigned long size)
{
  if (jxmunmap(ptr, size))
    jxwritestr(JX_STDOUT, "Failed to deallocate page\n");
}

unsigned long jxgetfilesize(int fd)
{
  struct stat64 filestat;
  if (jxfstat(fd, &filestat)) {
    jxwritestr(JX_STDOUT, "Failed to get file stat\n");
    return -1;
  }

  return filestat.st_size;
}

