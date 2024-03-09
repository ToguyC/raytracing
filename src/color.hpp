#pragma once

#include "vec3.hpp"
#include <iostream>
#include <vector>

using color = vec3;

inline double linear_to_gamma(double linear_component) { return sqrt(linear_component); }

inline void write_color_stream(std::ostream &out, color pixel, int samples_per_pixel) {
    double r = pixel.x();
    double g = pixel.y();
    double b = pixel.z();

    // divide the color by the number of samples
    double scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    // apply the linear to gamma transform
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // write the translated [0,255] value of each color component
    static const interval intensity(0.000, 0.999);

    // clang-format off
    out << static_cast<int>(256 * intensity.clamp(r)) << ' '
        << static_cast<int>(256 * intensity.clamp(g)) << ' '
        << static_cast<int>(256 * intensity.clamp(b)) << '\n';
    // clang-format on
}

inline void write_color(std::vector<unsigned char> &image, color pixel, int samples_per_pixel) {
    double r = pixel.x();
    double g = pixel.y();
    double b = pixel.z();

    // divide the color by the number of samples
    double scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    // apply the linear to gamma transform
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // write the translated [0,255] value of each color component
    static const interval intensity(0.000, 0.999);

    image.push_back(256 * intensity.clamp(r));
    image.push_back(256 * intensity.clamp(g));
    image.push_back(256 * intensity.clamp(b));
    image.push_back(255);
}