#include "sys.h"
#include "base.h"

int main()
{
  int file = jxopen("readline.txt", JX_O_RDONLY, 0);
  char buf[100];

  while (jxreadline(file, buf, 99)) {
    jxwritestr(JX_STDOUT, buf);
    jxwrite(JX_STDOUT, "\n", 1);
  }

  jxclose(file);
  jxwrite(JX_STDOUT, "END\n", 4);
  return 0;
}

