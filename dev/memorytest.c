#include "sys.h"
#include "base.h"

int main()
{
  char* ptr = (char*) jxmmap(0, JX_PAGE_SIZE, JX_PROT_WRITE | JX_PROT_READ, JX_MAP_PRIVATE | JX_MAP_ANON, -1, 0);
  if ((long) ptr < 0) {
    jxwritestr(JX_STDOUT, "Failed to allocate page\n");
    return 1;
  }

  jxwritestr(JX_STDOUT, "Allocated\n");

  for (int i = 0; i < JX_PAGE_SIZE; i++)
    ptr[i] = 1;

  jxwritestr(JX_STDOUT, "Done writing\n");

  if (jxmunmap(ptr, JX_PAGE_SIZE*10)) {
    jxwritestr(JX_STDOUT, "Failed to deallocate page\n");
    return 1;
  }

  jxwritestr(JX_STDOUT, "Program has finished\n");

  return 0;
}
