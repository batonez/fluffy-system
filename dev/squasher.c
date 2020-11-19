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
        iout += jxinttostr(counter, buf + iout);
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
  int file = jxopen(argv[1], 0, 0);
  unsigned long fsize = jxgetfilesize(file);
  unsigned long allocsize = fsize;
  char* in = jxalloc(&allocsize);

  unsigned size = jxread(file, in, fsize);
  jxclose(file);

  if (size != fsize)
    jxwritestr(JX_STDOUT, "Warning: number of bytes read is not the same as file size as reported by stat.\n");
    
  unsigned result_size = squash(in, size);

  file = jxopen(argv[2], 0x0001 | 0x0200 | 0x0400, 0644);
  jxwrite(file, in, result_size);
  jxclose(file);

  jxdealloc(in, allocsize);
  return 0;
}

