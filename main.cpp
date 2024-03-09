#include "src/color.hpp"
#include "src/vec3.hpp"
#include <iostream>

int main() {
    // image
    int image_width = 256;
    int image_height = 256;

    // render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remainging: " << (image_height - j) << ' '
                  << std::flush;

        for (int i = 0; i < image_width; i++) {
            color pixel = color(double(i) / (image_width - 1),
                                double(j) / (image_height - 1), 0);
            write_color(std::cout, pixel);
        }
    }

    std::clog << "\rDone.                  \n";
}