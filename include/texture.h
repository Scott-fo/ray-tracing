#ifndef TEXTURE_H
#define TEXTURE_H

#include "perlin.h"
#include "vec3.h"

class texture {
public:
  virtual colour value(double u, double v, const point3 &p) const = 0;
};

class solid_colour : public texture {
public:
  solid_colour();
  solid_colour(colour c);
  solid_colour(double red, double green, double blue);

  virtual colour value(double u, double v, const vec3 &p) const override;
  virtual ~solid_colour();

private:
  colour colour_value;
};

class checker_texture : public texture {
public:
  checker_texture();
  checker_texture(shared_ptr<texture> _even, shared_ptr<texture> _odd);
  checker_texture(colour c1, colour c2);

  virtual colour value(double u, double v, const point3 &p) const override;
  virtual ~checker_texture();

public:
  shared_ptr<texture> odd, even;
};

class noise_texture : public texture {
public:
  noise_texture() {}
  noise_texture(double sc) : scale(sc) {}

  virtual colour value(double u, double v, const point3 &p) const override {
    return colour(1, 1, 1) * 0.5 *
           (1 + sin(scale * p.z() + 10 * noise.turb(p)));
  }

public:
  perlin noise;
  double scale;
};

class image_texture : public texture {
public:
  const static int bytes_per_pixel = 3;

  image_texture();

  image_texture(const char *filename);
  ~image_texture();

  virtual colour value(double u, double v, const vec3 &p) const override;

private:
  unsigned char *data;
  int width, height;
  int bytes_per_scanline;
};

#endif
