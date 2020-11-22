#include "sys.h"
#include "base.h"
#include "bmp.h"

#define WIDTH 1920
#define HEIGHT 1080

jx_pixel24bit gradient(unsigned x, unsigned y, unsigned width, unsigned height)
{
  jx_pixel24bit result = {0, 0, 0};

  float ratio = (float) y / (float) height;
  result.r = 255 * ratio;

  ratio = (float) x / (float) width;
  result.b = 255 * ratio;

  result.g = 100;

  return result;
}

jx_pixel24bit calculate_pixel_color(unsigned x, unsigned y, unsigned width, unsigned height)
{
  jx_pixel24bit result = {0, 0, 0};

  int x0 = 300;
  int x1 = 1400;
  int y0 = 100;
  int y1 = 800;

  if (x >= x0 && x < x1) {
    if (x1 - x0 < y1 - y0) {
      int tmp = x;
      x = y;
      y = tmp;
      tmp = x0;
      x0 = y0;
      y0 = tmp;
      tmp = x1;
      x1 = y1;
      y1 = tmp;
    }

    float yline = ((float) (y1 - y0) / (x1 - x0)) * (x - x0) + y0;
    yline += (yline - (int) yline);
    if (y == (int) yline)
      result.r = 255;
  }

  return result;
}

void draw(jx_pixel24bit* pixels, unsigned width, unsigned height)
{
  for (unsigned x = 0; x < width; x++)
    for (unsigned y = 0; y < height; y++)
      pixels[y*width + x] = calculate_pixel_color(x, y, width, height);
}

int main()
{
  jx_bmpheader header;
  jx_bmpinfoheader infoheader;
  jx_pixel24bit pixels[WIDTH*HEIGHT];

  draw(pixels, WIDTH, HEIGHT);

  header.signature[0] = 'B';
  header.signature[1] = 'M';
  header.filesize = sizeof(header) + sizeof(infoheader) + WIDTH*HEIGHT*3;
  header.unused = 0;
  header.dataoffset = sizeof(header) + sizeof(infoheader);

  infoheader.infoheadersize = sizeof(infoheader);
  infoheader.imagewidth = WIDTH;
  infoheader.imageheight = HEIGHT;
  infoheader.planes = 1;
  infoheader.bitdepth = 24;
  infoheader.compression = 0;
  infoheader.imagesize = 0;
  infoheader.xpixelspermeter = 0;
  infoheader.ypixelspermeter = 0;
  infoheader.colorsused = 0;
  infoheader.importantcolors = 0;

  int file = jxopen("picture.bmp", JX_O_WRTONLY | JX_O_CREAT | JX_O_TRUNCATE, 0644);

  jxwrite(file, &header, sizeof(header));
  jxwrite(file, &infoheader, sizeof(infoheader));
  jxwrite(file, pixels, WIDTH*HEIGHT*3);
  jxclose(file);

  return 0;
}
