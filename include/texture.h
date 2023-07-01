#ifndef TEXTURE_H
#define TEXTURE_H

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

#endif
