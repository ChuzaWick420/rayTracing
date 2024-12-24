#ifndef VEC3_HPP
#define VEC3_HPP

#include "../utils.hpp"
#include "SFML/Graphics.hpp"

enum Axes {
    x, y, z
};

class Vec3 {
  public:
    double axes[3];

    Vec3();
    Vec3(double, double, double);

    double x() const;
    double y() const;
    double z() const;

    Vec3 operator-() const;
    double operator[](int) const;
    double& operator[](int);

    Vec3& operator+=(const Vec3&);

    Vec3& operator*=(double);

    Vec3& operator/=(double);

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

// Point3 is just an alias for Vec3, but useful for geometric clarity in the code.
using Point3 = Vec3;

inline void operator<<(sf::Color& pixel, const Vec3& vec) {
    pixel.r = vec.axes[Axes::x];
    pixel.g = vec.axes[Axes::y];
    pixel.b = vec.axes[Axes::z];
}

inline Vec3 operator + (const Vec3& u, const Vec3& v) {
    return Vec3(
        u.axes[Axes::x] + v.axes[Axes::x],
        u.axes[Axes::y] + v.axes[Axes::y],
        u.axes[Axes::z] + v.axes[Axes::z]
    );
}

inline Vec3 operator - (const Vec3& u, const Vec3& v) {
    return Vec3(
        u.axes[Axes::x] - v.axes[Axes::x],
        u.axes[Axes::y] - v.axes[Axes::y],
        u.axes[Axes::z] - v.axes[Axes::z]
    );
}

inline Vec3 operator * (const Vec3& u, const Vec3& v) {
    return Vec3(
        u.axes[Axes::x] * v.axes[Axes::x],
        u.axes[Axes::y] * v.axes[Axes::y],
        u.axes[Axes::z] * v.axes[Axes::z]
    );
}

inline Vec3 operator * (double t, const Vec3& v) {
    return Vec3(
        t * v.axes[Axes::x],
        t * v.axes[Axes::y],
        t * v.axes[Axes::z]
    );
}

inline Vec3 operator * (const Vec3& v, double t) {
    return t * v;
}

inline Vec3 operator / (const Vec3& v, double t) {
    return (1 / t) * v;
}

inline double dot(const Vec3& u, const Vec3& v) {
    return u.axes[Axes::x] * v.axes[Axes::x]
         + u.axes[Axes::y] * v.axes[Axes::y]
         + u.axes[Axes::z] * v.axes[Axes::z];
}

inline Vec3 cross(const Vec3& u, const Vec3& v) {
    return Vec3(
        u.axes[Axes::y] * v.axes[Axes::z] - u.axes[Axes::z] * v.axes[Axes::y],
        u.axes[Axes::z] * v.axes[Axes::x] - u.axes[Axes::x] * v.axes[Axes::z],
        u.axes[Axes::x] * v.axes[Axes::y] - u.axes[Axes::y] * v.axes[Axes::x]
    );
}

inline Vec3 unit_vector(const Vec3& v) {
    return v / v.length();
}

inline Vec3 random_in_unit_sphere() {
    while (true) {
        auto V3_p = Vec3::random(-1,1);
        if (V3_p.length_squared() < 1)
            return V3_p;
    }
}

inline Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

inline Vec3 random_on_hemisphere(const Vec3& normal) {
    Vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return - on_unit_sphere;
}

inline Vec3 reflect(const Vec3& v, const Vec3& n) {
    double d_mag = dot(v, unit_vector(n));
    Vec3 d = unit_vector(n) * d_mag;
    Vec3 b = -d;
    return v + 2 * b;
}

inline Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
    auto cos_theta = std::fmin(dot(-uv, n), 1.0);
    Vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    Vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

inline Vec3 random_in_unit_disk() {
    while(true) {
        auto V3_p = Vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (V3_p.length_squared() < 1)
            return V3_p;
    }
}

#endif
