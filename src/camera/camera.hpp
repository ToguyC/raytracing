#pragma once

#include "../utilities.hpp"

#include "../color.hpp"
#include "../interfaces/hittable.hpp"
#include "../material.hpp"

#include <iostream>

class camera {
  public:
    void render(const hittable &world);

  private:
    void initialize();
    color ray_color(const ray &r, int depth, const hittable &world) const;
    ray get_ray(int i, int j) const;
    vec3 pixel_sample_square() const;

  public:
    double aspect_ratio            = 16.0 / 9.0;
    int image_width                = 400;
    int samples_per_pixel          = 10;
    int max_depth                  = 10;
    bool use_lambertian_reflection = true;

  private:
    int image_height;   // Rendered image height
    point3 center;      // Camera center
    point3 pixel00_loc; // Location of pixel 0, 0
    vec3 pixel_delta_u; // Offset to pixel to the right
    vec3 pixel_delta_v; // Offset to pixel below
};