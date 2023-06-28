#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable {
public:
  hittable_list();
  hittable_list(shared_ptr<hittable> object);

  void clear();
  void add(shared_ptr<hittable> object);

  virtual bool hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const override;

  virtual bool bounding_box(double time0, double time1,
                            aabb &output_box) const override;

  virtual ~hittable_list();

public:
  std::vector<shared_ptr<hittable>> objects;
};

#endif
