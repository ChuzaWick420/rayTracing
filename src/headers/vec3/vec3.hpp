#ifndef VEC3_HPP
#define VEC3_HPP

#include "../utils.hpp"
#include "SFML/Graphics.hpp"

class Vec3 {
  public:
    double e[3];

    Vec3();
    Vec3(double e0, double e1, double e2);

    double x() const;
    double y() const;
    double z() const;

    Vec3 operator-() const;
    double operator[](int i) const;
    double& operator[](int i);

    Vec3& operator+=(const Vec3& v);

    Vec3& operator*=(double t);

    Vec3& operator/=(double t);

    double length() const;

    double length_squared() const;

    bool near_zero() const;

    static Vec3 random() {
        return Vec3(random_double(), random_double(), random_double());
    }

    static Vec3 random(double min, double max) {
        return Vec3(random_double(min,max), random_double(min,max), random_double(min,max));
    }
};

#endif
