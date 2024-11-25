#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>    // NOTE: for std::fmin(), std::fabs(), std::sqrt()
#include <limits>   // NOTE: for std::numeric_limits<>
#include <cstdlib>  // NOTE: for std::rand(), RAND_MAX

#include <SFML/Graphics.hpp>

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    // Returns a random real in [0,1).
    return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

#endif
