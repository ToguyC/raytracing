#include "src/utilities.hpp"

#include "src/camera/camera.hpp"
#include "src/color.hpp"
#include "src/interfaces/hittable_list.hpp"
#include "src/material/dielectric.hpp"
#include "src/material/lambertian.hpp"
#include "src/material/metal.hpp"
#include "src/objects/sphere/sphere.hpp"

#include "lib/lodepng/lodepng.hpp"

int main() {
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(1.5);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.4, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

    camera cam;

    cam.aspect_ratio              = 16.0 / 9.0;
    cam.image_width               = 400;
    cam.samples_per_pixel         = 100;
    cam.max_depth                 = 50;
    cam.use_lambertian_reflection = true;

    auto image = cam.render(world, FILE_PNG);

    std::string output_path = "image.png";
    auto status = lodepng::encode(output_path, image, static_cast<unsigned>(cam.image_width),
                                  static_cast<unsigned>(cam.image_height));
    if (status != 0) {
        std::cerr << "Error saving PNG file. " << lodepng_error_text(status) << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cerr << "Image saved in " << output_path << std::endl;
    }
}