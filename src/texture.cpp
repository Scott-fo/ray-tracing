#include "texture.h"
#include "external_stb_image.h"
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

image_texture::image_texture()
    : data(nullptr), width(0), height(0), bytes_per_scanline(0) {}

image_texture::image_texture(const char *filename) {
  auto components_per_pixel = bytes_per_pixel;

  data = stbi_load(filename, &width, &height, &components_per_pixel,
                   components_per_pixel);

  if (!data) {
    std::cerr << "ERROR: Could not load texture image file '" << filename
              << "'.\n";
    width = height = 0;
  }

  bytes_per_scanline = bytes_per_pixel * width;
}

image_texture::~image_texture() { delete data; }

colour image_texture::value(double u, double v, const vec3 &p) const {
  if (data == nullptr) {
    return colour(0, 1, 1);
  }

  u = clamp(u, 0.0, 1.0);
  v = 1.0 - clamp(v, 0.0, 1.0);

  auto i = static_cast<int>(u * width);
  auto j = static_cast<int>(v * height);

  if (i >= width) {
    i = width - 1;
  }

  if (j >= height) {
    j = height - 1;
  }

  const auto colour_scale = 1.0 / 255.0;
  auto pixel = data + j * bytes_per_scanline + i * bytes_per_pixel;

  return colour(colour_scale * pixel[0], colour_scale * pixel[1],
                colour_scale * pixel[2]);
}
