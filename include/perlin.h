#ifndef PERLIN_H
#define PERLIN_H

#include "vec3.h"
class perlin {
public:
  perlin();
  ~perlin();
  double noise(const point3 &p) const;

private:
  static const int point_count = 256;
  double *ranfloat;
  int *perm_x, *perm_y, *perm_z;

  static int *perlin_generate_perm();
  static void permute(int *p, int n);
};

#endif
