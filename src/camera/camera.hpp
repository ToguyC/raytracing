#pragma once

#include "../utilities.hpp"

#include "../color.hpp"
#include "../interfaces/hittable.hpp"
#include "../material/material.hpp"

#include <iostream>
#include <vector>

enum OutputFileType { FILE_PPM, FILE_PNG };

class camera {
  public:
    std::vector<unsigned char> render(const hittable &world, OutputFileType type);

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
    int image_height;

  private:
    point3 center;      // Camera center
    point3 pixel00_loc; // Location of pixel 0, 0
    vec3 pixel_delta_u; // Offset to pixel to the right
    vec3 pixel_delta_v; // Offset to pixel below
};