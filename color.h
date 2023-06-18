#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>
#include <ostream>

inline void write_colour(std::ostream &out, colour pixel_colour) {
  out << static_cast<int>(255.999 * pixel_colour.x()) << ' '
      << static_cast<int>(255.999 * pixel_colour.y()) << ' '
      << static_cast<int>(255.999 * pixel_colour.z()) << '\n';
}

#endif
