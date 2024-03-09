#pragma once

#include <cmath>
#include <limits>
#include <memory>

// usings
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// utility functions
inline double degrees_to_radians(double degrees) { return degrees * pi / 180.0; }

// common headers

#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"