typedef struct {
  unsigned char b;
  unsigned char g;
  unsigned char r;
} jx_pixel24bit;

typedef struct {
  int x;
  int y;
} jx_vertex;

typedef struct {
  int swapxy;
  int x0, y0, x1, y1;
  float k;
  float b;
} jx_line_primitive;

