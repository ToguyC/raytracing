#include "camera.hpp"

void camera::initialize() {
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    center = point3(0, 0, 0);

    // Determine viewport dimensions.
    auto focal_length    = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width  = viewport_height * (static_cast<double>(image_width) / image_height);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left =
        center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

std::vector<unsigned char> camera::render(const hittable &world, OutputFileType type) {
    initialize();

    std::vector<unsigned char> image;

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remainging: " << (image_height - j) << ' ' << std::flush;

        for (int i = 0; i < image_width; i++) {
            color pixel_color(0, 0, 0);

            for (int sample = 0; sample < samples_per_pixel; sample++) {
                ray r = get_ray(i, j);
                pixel_color += ray_color(r, max_depth, world);
            }

            if (type == FILE_PPM) {
                write_color_stream(std::cout, pixel_color, samples_per_pixel);
            } else if (type == FILE_PNG) {
                write_color(image, pixel_color, samples_per_pixel);
            } else {
                std::cerr << "Unkonwn file type." << std::endl;
                exit(1);
            }
        }
    }

    std::clog << "\rDone.                  \n";

    return image;
}

color camera::ray_color(const ray &r, int depth, const hittable &world) const {
    hit_record rec;

    if (depth <= 0) {
        return color(0, 0, 0);
    }

    if (world.hit(r, interval(0.001, infinity), rec)) {
        ray scattered;
        color attenuation;

        if (rec.mat->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, depth - 1, world);
        }

        return color(0, 0, 0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    double a            = 0.5 * (unit_direction.y() + 1.0);

    // lerp function
    // blendedValue = (1 - a) * startValue + a * endValue
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

ray camera::get_ray(int i, int j) const {
    // get randomly sampled camera ray for the pixel at location i, j
    point3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
    point3 pixel_sample = pixel_center + pixel_sample_square();

    point3 ray_origin  = center;
    vec3 ray_direction = pixel_sample - ray_origin;

    return ray(ray_origin, ray_direction);
}

vec3 camera::pixel_sample_square() const {
    double px = -0.5 + random_double();
    double py = -0.5 + random_double();

    return (px * pixel_delta_u) + (py * pixel_delta_v);
}