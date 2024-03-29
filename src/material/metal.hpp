#pragma once

#include "material.hpp"

class metal : public material {
  public:
    metal(const color &a, double f) : albedo(a), fuzz(f) {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation,
                 ray &scattered) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered      = ray(rec.p, reflected + fuzz * random_unit_vector());
        attenuation    = albedo;
        return dot(scattered.direction(), rec.normal) > 0;
    }

  private:
    color albedo;
    double fuzz;
};