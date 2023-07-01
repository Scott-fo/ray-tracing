#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H

#include "hittable.h"
#include "texture.h"
#include "utils.h"
#include <memory>
class constant_medium : public hittable {
public:
  constant_medium(shared_ptr<hittable> b, double d, shared_ptr<texture> a);
  constant_medium(shared_ptr<hittable> b, double d, colour c);

  virtual bool hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const override;

  virtual bool bounding_box(double time0, double time1,
                            aabb &output_box) const override;

public:
  shared_ptr<hittable> boundary;
  shared_ptr<material> phase_function;
  double neg_inv_density;
};

#endif
