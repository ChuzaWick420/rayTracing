#include "./ray.hpp"

Ray::Ray() {}

const Point3& Ray::origin() const  { 
    return orig; 
}

const Vec3& Ray::direction() const { 
    return dir; 
}


Point3 Ray::at(double t) const {
    return orig + t*dir;
}
