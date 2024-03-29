#pragma once

#include "../utilities.hpp"

#include "../interfaces/hittable.hpp"

class hit_record;

class material {
  public:
    virtual ~material() = default;

    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation,
                         ray &scattered) const = 0;
};