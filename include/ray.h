#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
  ray();
  ray(const point3 &origin, const vec3 &direction, double time = 0.0);

  point3 origin() const;
  point3 at(double t) const;

  vec3 direction() const;

  double time() const;

public:
  point3 orig;
  vec3 dir;
  double tm;
};

#endif
