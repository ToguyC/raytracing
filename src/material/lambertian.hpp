#pragma once

#include "material.hpp"

class lambertian : public material {
  public:
    lambertian(const color &a) : albedo(a) {}

    bool scatter(__attribute__((unused)) const ray &r_in, const hit_record &rec,
                 color &attenuation, ray &scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();

        // catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered   = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

  private:
    color albedo;
};