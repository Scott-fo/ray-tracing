#include "sphere.h"
#include "math.h"
#include "utils.h"
#include "vec3.h"

sphere::sphere() {}

sphere::sphere(point3 cen, double r, shared_ptr<material> m)
    : center(cen), radius(r), mat_ptr(m){};

sphere::~sphere() {}

bool sphere::hit(const ray &r, double t_min, double t_max,
                 hit_record &rec) const {
  vec3 oc = r.origin() - center;
  auto a = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius * radius;

  auto discriminant = half_b * half_b - a * c;
  if (discriminant < 0) {
    return false;
  }

  auto sqrtd = sqrt(discriminant);

  auto root = (-half_b - sqrtd) / a;
  if (root < t_min || t_max < root) {
    root = (-half_b + sqrtd) / a;
    if (root < t_min || t_max < root) {
      return false;
    }
  }

  rec.t = root;
  rec.p = r.at(rec.t);
  vec3 outward_normal = (rec.p - center) / radius;
  rec.set_face_normal(r, outward_normal);
  get_sphere_uv(outward_normal, rec.u, rec.v);
  rec.mat_ptr = mat_ptr;

  return true;
}

bool sphere::bounding_box(double time0, double time1, aabb &output_box) const {
  output_box = aabb(center - vec3(radius, radius, radius),
                    center + vec3(radius, radius, radius));

  return true;
}

void sphere::get_sphere_uv(const point3 &p, double &u, double &v) {
  // p is a given point on the sphere of radius 1 and centered at origin
  // u is the returned value bounded 0, 1 of the angle around the Y axis from
  // x = -1 (2pi)
  // v is the return value bounded 0, 1 of the angle from y=-1 to y=1 (pi)

  auto theta = acos(-p.y());
  auto phi = atan2(-p.z(), p.x()) + pi;

  u = phi / (2 * pi);
  v = theta / pi;
}
