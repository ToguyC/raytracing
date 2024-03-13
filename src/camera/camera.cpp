#include "camera.hpp"

void camera::initialize() {
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    center = lookfrom;

    // Determine viewport dimensions.
    double theta           = degrees_to_radians(vfov);
    double h               = tan(theta / 2);
    double viewport_height = 2 * h * focus_dist;
    double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

    // Calculate the u,v,w unit basis vectors for the camera coordinate frame
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = viewport_width * u;
    vec3 viewport_v = viewport_height * -v;

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    vec3 viewport_upper_left = center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc              = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Calculate the camera defocus disk basis vectors.
    double defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2));
    defocus_disk_u        = u * defocus_radius;
    defocus_disk_v        = v * defocus_radius;
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
    // Get a randomly-sampled camera ray for the pixel at location i,j, originating from the
    // camera defocus disk.
    point3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
    point3 pixel_sample = pixel_center + pixel_sample_square();

    point3 ray_origin  = (defocus_angle <= 0) ? center : defocus_disk_sample();
    vec3 ray_direction = pixel_sample - ray_origin;

    return ray(ray_origin, ray_direction);
}

vec3 camera::pixel_sample_square() const {
    double px = -0.5 + random_double();
    double py = -0.5 + random_double();

    return (px * pixel_delta_u) + (py * pixel_delta_v);
}

vec3 camera::defocus_disk_sample() const {
    // Returns a random point in the camera defocus disk
    point3 p = random_in_unit_disk();
    return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}