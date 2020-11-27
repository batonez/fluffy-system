#include "bmp.h"
#include "pixels.h"

#define WIDTH 1920
#define HEIGHT 1080

int main()
{
  jx_pixel24bit pixels[WIDTH*HEIGHT];
  jxsavebmpfile(pixels, WIDTH, HEIGHT);
  return 0;
}

