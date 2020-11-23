#include "sys.h"
#include "base.h"
#include "pixels.h"
#include "bmp.h"

#define WIDTH 1920
#define HEIGHT 1080

typedef struct {
  int width;
  int height;
  int antialiasing;
} jx_uniform;

typedef struct {
  int swapxy;
  int x0, y0, x1, y1;
  float k;
  float b;
} jx_line_primitive;

void jxswap(int* a, int* b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int jxround(float a)
{
  a += a - (int) a;
  return (int) a;
}

void jxprecalculate(jx_line_primitive* p)
{
  if (p->x0 > p->x1)
    jxswap(&(p->x0), &(p->x1));

  if (p->y0 > p->y1)
    jxswap(&(p->y0), &(p->y1));

  if (p->x1 - p->x0 < p->y1 - p->y0) {
    jxswap(&(p->x0), &(p->y0));
    jxswap(&(p->x1), &(p->y1));
    p->swapxy = 1;
  } else {
    p->swapxy = 0;
  }

  p->k = (float) (p->y1 - p->y0) / (p->x1 - p->x0);
  p->b = p->y0 - p->x0 * p->k;
}

void jxcalculate_pixel_color(int x, int y, const jx_uniform* u, const jx_line_primitive* p, jx_pixel24bit* result)
{
  if (p->swapxy)
    jxswap(&x, &y);

  if (x >= p->x0 && x < p->x1) {
    float ylineideal = p->k * x + p->b;
    int yline = jxround(ylineideal);

    if (y == yline) {
      result->r = 255;
    }

    if (u->antialiasing) {
      if (y == yline - 1) {
        float error = ylineideal - yline + 0.5f;
        result->r = 255.0 * (1.0f - error);
      } else if (y == yline + 1) {
        float error = ylineideal - yline + 0.5f;
        result->r = 255.0 * error;
      }
    }
  }
}

int main()
{
  jx_pixel24bit pixels[WIDTH*HEIGHT];

  // set background color
  for (register int i = 0; i < WIDTH*HEIGHT; i++) {
    pixels[i].r = 0;
    pixels[i].g = 0;
    pixels[i].b = 0;
  }

  jx_uniform uniform;
  uniform.width = WIDTH;
  uniform.height = HEIGHT;
  uniform.antialiasing = 1;

  int vertexarray[] = {1400, 250, 1910, 1070, 300, 400, 1800, 800};
  int vertexsize = 2;
  unsigned indexarray[] = {0, 1, 2, 3};

  for (int i = 0; i < 4; i += 2) {
    jx_line_primitive line;
    line.x0 = vertexarray[indexarray[i]*vertexsize];
    line.y0 = vertexarray[indexarray[i]*vertexsize + 1];
    line.x1 = vertexarray[indexarray[i + 1]*vertexsize];
    line.y1 = vertexarray[indexarray[i + 1]*vertexsize + 1];
    jxprecalculate(&line);

    for (register int x = 0; x < WIDTH; x++) {
      for (register int y = 0; y < HEIGHT; y++) {
        jxcalculate_pixel_color(x, y, &uniform, &line, &pixels[y*WIDTH + x]);
      }
    }
  }

  jxsavebmpfile(pixels, WIDTH, HEIGHT);

  return 0;
}

