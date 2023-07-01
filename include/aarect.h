#ifndef AARECT_H
#define AARECT_H

#include "hittable.h"
#include "utils.h"
#include <memory>

class xy_rect : public hittable {
public:
  xy_rect();

  xy_rect(double _x0, double _x1, double _y0, double _y1, double _k,
          shared_ptr<material> mat);

  virtual bool hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const override;

  virtual bool bounding_box(double time0, double time1,
                            aabb &output_box) const override;

public:
  shared_ptr<material> mp;
  double x0, x1, y0, y1, k;
};

class xz_rect : public hittable {
public:
  xz_rect();

  xz_rect(double _x0, double _x1, double _z0, double _z1, double _k,
          shared_ptr<material> mat);

  virtual bool hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const override;

  virtual bool bounding_box(double time0, double time1,
                            aabb &output_box) const override;

public:
  shared_ptr<material> mp;
  double x0, x1, z0, z1, k;
};

class yz_rect : public hittable {
public:
  yz_rect();
  yz_rect(double _y0, double _y1, double _z0, double _z1, double _k,
          shared_ptr<material> mat);

  virtual bool hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const override;

  virtual bool bounding_box(double time0, double time1,
                            aabb &output_box) const override;

public:
  shared_ptr<material> mp;
  double z0, z1, y0, y1, k;
};

#endif
