#include "sys.h"
#include "base.h"

unsigned squash(char* buf, unsigned size)
{
  unsigned iin = 0, iout = 0, counter = 0;
  char symbol = buf[0];

  while (iin < size) {
    if (symbol == buf[iin])
      counter++;
    else {
      buf[iout++] = symbol;
      if (counter > 1) {
        iout += inttostr(counter, buf + iout);
        counter = 1;
      }
    }

    symbol = buf[iin];
    iin++;
  }

  return iout;
}

int main(int argc, char** argv)
{
  int file = jopen(argv[1], 0, 0);
  char in[1000];
  unsigned size = jread(file, in, 1000);
  jclose(file);

  unsigned result_size = squash(in, size);

  file = jopen(argv[2], 0x0001 | 0x0200 | 0x0400, 0644);
  jwrite(file, in, result_size);
  jclose(file);
  return 0;
}
