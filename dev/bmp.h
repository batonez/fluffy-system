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

typedef struct {
  unsigned char b;
  unsigned char g;
  unsigned char r;
} jx_pixel24bit;

