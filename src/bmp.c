#include "sys.h"
#include "base.h"
#include "pixels.h"

typedef struct {
  unsigned char signature[2];
  unsigned filesize;
  unsigned unused; // = 0
  unsigned dataoffset;
} __attribute__((packed)) jx_bmpheader;

typedef struct {
  unsigned infoheadersize; // = 40
  unsigned imagewidth;
  unsigned imageheight;
  unsigned short planes; // = 1
  unsigned short bitdepth;
  unsigned compression;
  unsigned imagesize; // can be 0 if no compression
  unsigned xpixelspermeter;
  unsigned ypixelspermeter;
  unsigned colorsused;
  unsigned importantcolors;
} __attribute__((packed)) jx_bmpinfoheader;

void jxsavebmpfile(void *pixels, unsigned width, unsigned height)
{
  jx_bmpheader header;
  jx_bmpinfoheader infoheader;

  header.signature[0] = 'B';
  header.signature[1] = 'M';
  header.filesize = sizeof(header) + sizeof(infoheader) + width*height*3;
  header.unused = 0;
  header.dataoffset = sizeof(header) + sizeof(infoheader);

  infoheader.infoheadersize = sizeof(infoheader);
  infoheader.imagewidth = width;
  infoheader.imageheight = height;
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
  jxwrite(file, pixels, height*width*3);
  jxclose(file);
}
