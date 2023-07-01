#include "texture.h"
#include "utils.h"
#include "vec3.h"
#include <memory>

solid_colour::solid_colour() {}

solid_colour::~solid_colour() {}

solid_colour::solid_colour(colour c) : colour_value(c) {}

solid_colour::solid_colour(double red, double green, double blue)
    : solid_colour(colour(red, green, blue)) {}

colour solid_colour::value(double u, double v, const vec3 &p) const {
  return colour_value;
}

checker_texture::checker_texture() {}

checker_texture::~checker_texture() {}

checker_texture::checker_texture(shared_ptr<texture> _even,
                                 shared_ptr<texture> _odd)
    : even(_even), odd(_odd) {}

checker_texture::checker_texture(colour c1, colour c2)
    : even(make_shared<solid_colour>(c1)), odd(make_shared<solid_colour>(c2)) {}

colour checker_texture::value(double u, double v, const vec3 &p) const {
  auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
  if (sines < 0) {
    return odd->value(u, v, p);
  } else {
    return even->value(u, v, p);
  }
}
