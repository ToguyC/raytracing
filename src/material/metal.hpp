#pragma once

#include "material.hpp"

class metal : public material {
  public:
    metal(const color &a) : albedo(a) {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation,
                 ray &scattered) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered      = ray(rec.p, reflected);
        attenuation    = albedo;
        return true;
    }

  private:
    color albedo;
};