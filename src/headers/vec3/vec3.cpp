#include "./vec3.hpp"

Vec3::Vec3() {
    axes[Axes::x] = 0;
    axes[Axes::y] = 0;
    axes[Axes::z] = 0;
}

Vec3::Vec3(double u_x, double u_y, double u_z) {
    axes[Axes::x] = u_x;
    axes[Axes::y] = u_y;
    axes[Axes::z] = u_z;
}

double Vec3::x() const {
    return axes[Axes::x];
}

double Vec3::y() const {
    return axes[Axes::y];
}

double Vec3::z() const {
    return axes[Axes::z];
}

Vec3 Vec3::operator - () const {
    return Vec3(
        - axes[Axes::x],
        - axes[Axes::y],
        - axes[Axes::z]
    ); 
}

double Vec3::operator[](int i) const {
    return axes[i]; 
}

double& Vec3::operator[](int i) { 
    return axes[i]; 
}

Vec3& Vec3::operator += (const Vec3& v) {
    axes[Axes::x] += v.axes[Axes::x];
    axes[Axes::y] += v.axes[Axes::y];
    axes[Axes::z] += v.axes[Axes::z];

    return *this;
}

Vec3& Vec3::operator *= (double t) {
    axes[Axes::x] *= t;
    axes[Axes::y] *= t;
    axes[Axes::z] *= t;
    return *this;
}

Vec3& Vec3::operator /= (double t) {
    return *this *= 1 / t;
}

double Vec3::length() const {
    return std::sqrt(length_squared());
}

double Vec3::length_squared() const {
    return (
        axes[Axes::x] * axes[Axes::x] +
        axes[Axes::y] * axes[Axes::y] +
        axes[Axes::z] * axes[Axes::z]
    );
}

bool Vec3::near_zero() const {
    auto threshold = 1e-8;
    return
        (std::fabs(axes[Axes::x]) < threshold) &&
        (std::fabs(axes[Axes::y]) < threshold) &&
        (std::fabs(axes[Axes::z]) < threshold);
}
