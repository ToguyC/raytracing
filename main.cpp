#include "src/rtweekend.hpp"

#include "src/color.hpp"
#include "src/interfaces/hittable.hpp"
#include "src/interfaces/hittable_list.hpp"
#include "src/objects/sphere/sphere.hpp"
#include <iostream>

color ray_color(const ray &r, const hittable &world) {
    hit_record rec;

    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    double a = 0.5 * (unit_direction.y() + 1.0);

    // lerp function
    // blendedValue = (1 - a) * startValue + a * endValue
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
    // image
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // calculate the image height, and ensure that it's at least 1
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // world
    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // camera
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
    point3 camera_center = point3(0, 0, 0);

    // calculate the vectors across the horizontal and down the vertical
    // viewport edges
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // calculate the horizontal and vertical delta vectors from pixel to pixel
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // calculate the location of the upper left pixel
    vec3 viewport_upper_left =
        camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remainging: " << (image_height - j) << ' ' << std::flush;

        for (int i = 0; i < image_width; i++) {
            vec3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            vec3 ray_direction = pixel_center - camera_center;

            ray r(camera_center, ray_direction);

            color pixel = ray_color(r, world);
            write_color(std::cout, pixel);
        }
    }

    std::clog << "\rDone.                  \n";
}