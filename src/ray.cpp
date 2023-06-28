#include "ray.h"

ray::ray() {}

ray::ray(const point3 &origin, const vec3 &direction, double time)
    : orig(origin), dir(direction), tm(time) {}

point3 ray::origin() const { return orig; }
point3 ray::at(double t) const { return orig + dir * t; }

vec3 ray::direction() const { return dir; }

double ray::time() const { return tm; }
