#pragma once

#include "../../interfaces/hittable.hpp"
#include "../../vec3.hpp"

class sphere : public hittable {
  public:
    sphere(point3 _center, double _radius) : center(_center), radius(_radius) {}

    bool hit(const ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const override;

  private:
    point3 center;
    double radius;
};