#include "sphere.hpp"

bool sphere::hit(const ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const {
    vec3 oc = r.origin() - center;
    double a = r.direction().length_squared();
    double half_b = dot(oc, r.direction());
    double c = oc.length_squared() - radius * radius;

    double discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
        return false;

    double sqrtd = sqrt(discriminant);

    // find the nearest root that lies in the acceptable range
    double root = (-half_b - sqrtd) / a;

    if (root <= ray_tmin || root > ray_tmax) {
        root = (-half_b + sqrtd) / a;

        if (root <= ray_tmin || root > ray_tmax)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}