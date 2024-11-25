#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include "../utils.hpp"

class Interval {
  public:
    double min, max;

    Interval() : min(+infinity), max(-infinity) {} // Default interval is empty

    Interval(double min, double max) : min(min), max(max) {}

    double size() const;

    bool contains(double) const;

    bool surrounds(double) const;

    double clamp(double x) const;

    static const Interval empty, universe;
};


#endif
