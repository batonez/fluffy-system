#include "sys.h"

unsigned strlength(const char* str)
{
  int num = 0;
  while (*str != '\0') {
    num++;
    str++;
  }
  return num;
}

int writestr(int fd, const char* buf)
{
  unsigned len = strlength(buf);
  return jwrite(fd, buf, len);
}

unsigned inttostr(int integer, char* out)
{
  unsigned num_digits = 0;

  if (integer < 0) {
    integer = -integer;
    num_digits++;
    out[0] = '-';
  }

  int copy = integer;

  do {
    copy /= 10;
    num_digits++;
  } while (copy != 0);
 
  int i = 1;

  do {
    int digit = integer % 10;
    out[num_digits - i++] = digit + 48;
    integer /= 10;
  } while (integer != 0);

  return num_digits;
}
