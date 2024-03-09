#pragma once

// may result in circular dependencies, but until this, ff
#include "utilities.hpp"

class interval {
  public:
    interval() : min(+infinity), max(-infinity) {}

    interval(double _min, double _max) : min(_min), max(_max) {}

    bool contains(double x) const { return min <= x && x <= max; }

    bool surrounds(double x) const { return min < x && x < max; }

  public:
    double min, max;
    static const interval empty, universe;
};

const static interval empty(+infinity, -infinity);
const static interval universe(-infinity, +infinity);