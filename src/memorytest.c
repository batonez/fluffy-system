#include "sys.h"
#include "base.h"

int main()
{
  unsigned long size = 1000;
  char* ptr = (char*) jxalloc(&size);
  if (!ptr) {
    jxwritestr(JX_STDOUT, "Failed to allocate memory\n");
  }

  for (unsigned long i = 0; i < size; i++)
    ptr[i] = 1;

  jxdealloc(ptr, size);
  return 0;
}
