#include "sys.h"
#include "base.h"
#include "pixels.h"
#include "bmp.h"

#define WIDTH 1920
#define HEIGHT 1080

typedef struct {
  int width;
  int height;
  int x0, y0, x1, y1;
  int antialiasing;
  int swapxy;
  float k;
  float b;
} jx_uniform;

void jxprecalculate(jx_uniform* u)
{
  if (jxabs(u->x1 - u->x0) < jxabs(u->y1 - u->y0)) {
    jxswap(&u->x0, &u->y0);
    jxswap(&u->x1, &u->y1);
    u->swapxy = 1;
  } else {
    u->swapxy = 0;
  }

  u->k = (float) (u->y1 - u->y0) / (u->x1 - u->x0);
  u->b = u->y0 - u->x0 * u->k;

  if (u->x0 > u->x1)
    jxswap(&u->x0, &u->x1);
}

jx_pixel24bit jxcalculate_pixel_color(int x, int y, jx_uniform* u)
{
  jx_pixel24bit result = {0, 0, 0};

  if (u->swapxy)
    jxswap(&x, &y);

  if (x >= u->x0 && x <= u->x1) {
    float ylineideal = u->k * x + u->b;
    int yline = jxround(ylineideal);

    if (y == yline) {
      result.r = 255;
    }

    if (u->antialiasing) {
      if (y == yline - 1) {
        float error = ylineideal - yline + 0.5f;
        result.r = 255.0 * (1.0f - error);
      } else if (y == yline + 1) {
        float error = ylineideal - yline + 0.5f;
        result.r = 255.0 * error;
      }
    }
  }

  return result;
}

int main()
{
  jx_pixel24bit pixels[WIDTH*HEIGHT];

  jx_uniform uniform;
  uniform.width = WIDTH;
  uniform.height = HEIGHT;
  uniform.x0 = 300;
  uniform.x1 = 1400;
  uniform.y0 = 400;
  uniform.y1 = 300;
  uniform.antialiasing = 1;

  jxprecalculate(&uniform);

  for (register int x = 0; x < WIDTH; x++)
    for (register int y = 0; y < HEIGHT; y++)
      pixels[y*WIDTH + x] = jxcalculate_pixel_color(x, y, &uniform);

  jxsavebmpfile(pixels, WIDTH, HEIGHT);

  return 0;
}

