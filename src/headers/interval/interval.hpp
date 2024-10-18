#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include "../main_header.hpp"

class interval {
  public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {} // Default interval is empty

    interval(double min, double max) : min(min), max(max) {}

    double size() const;

    bool contains(double) const;

    bool surrounds(double) const;

    double clamp(double x) const;

    static const interval empty, universe;
};


#endif
