#pragma once

#include "vec3.hpp"
#include <iostream>

using color = vec3;

inline void write_color(std::ostream &out, color pixel) {
    // write the translated [0,255] value of each color component
    // clang-format off
    out << static_cast<int>(255.999 * pixel.x()) << ' '
        << static_cast<int>(255.999 * pixel.y()) << ' '
        << static_cast<int>(255.999 * pixel.z()) << '\n';
    // clang-format on
}