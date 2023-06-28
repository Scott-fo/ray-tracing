#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "utils.h"
#include "vec3.h"
class camera {
public:
  camera(point3 lookfrom, point3 lookat, vec3 vup, double vfov,
         double aspect_ratio, double aperture, double focus_dist,
         double _time0 = 1, double _time1 = 0);

  ray get_ray(double s, double t) const;

private:
  point3 origin;
  point3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
  vec3 u, v, w;
  double lens_radius;
  double time0, time1;
};

#endif
