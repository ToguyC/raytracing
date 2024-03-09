#pragma once

#include "vec3.hpp"
#include <iostream>

using color = vec3;

void write_color(std::ostream &out, color pixel) {
    // write the translated [0,255] value of each color component
    out << static_cast<int>(255.999 * pixel.x()) << ' '
        << static_cast<int>(255.999 * pixel.y()) << ' '
        << static_cast<int>(255.999 * pixel.z()) << '\n';
}