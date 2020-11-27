#include "sys.h"
#include "base.h"
#include "pixels.h"
#include "bmp.h"

#define WIDTH 1920
#define HEIGHT 1080

typedef struct {
  int width;
  int height;
} jx_uniform;

jx_pixel24bit jxcalculate_pixel_color(int x, int y, jx_uniform* uniform)
{
  jx_pixel24bit result = {0, 0, 0};

  float ratio = (float) y / uniform->height;
  result.r = 255 * ratio;

  ratio = (float) x / uniform->width;
  result.b = 255 * ratio;

  result.g = 100;

  return result;
}

int main()
{
  jx_pixel24bit pixels[WIDTH*HEIGHT];

  jx_uniform uniform;
  uniform.width = WIDTH;
  uniform.height = HEIGHT;

  for (register int x = 0; x < WIDTH; x++)
    for (register int y = 0; y < HEIGHT; y++)
      pixels[y*WIDTH+ x] = jxcalculate_pixel_color(x, y, &uniform);

  jxsavebmpfile(pixels, WIDTH, HEIGHT);

  return 0;
}

