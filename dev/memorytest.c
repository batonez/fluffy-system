#include "sys.h"
#include "base.h"

int main()
{
  char* ptr = (char*) jmmap(0, PAGE_SIZE, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANON, -1, 0);
  if ((long) ptr < 0) {
    writestr(STDOUT, "Failed to allocate page\n");
    return 1;
  }

  writestr(STDOUT, "Allocated\n");

  for (int i = 0; i < PAGE_SIZE; i++)
    ptr[i] = 1;

  ptr[8191] = 1;

  writestr(STDOUT, "Done writing\n");

  if (jmunmap(ptr, PAGE_SIZE*10)) {
    writestr(STDOUT, "Failed to deallocate page\n");
    return 1;
  }

  writestr(STDOUT, "Program has finished\n");

  return 0;
}
