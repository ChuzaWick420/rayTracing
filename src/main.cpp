#include "./headers/vec3/vec3.hpp"
#include "./headers/sphere/sphere.hpp"
#include "./headers/hittable_list/hittable_list.hpp"
#include "./headers/camera/camera.hpp"
#include "./headers/material/material.hpp"
#include "./headers/lambertian/lambertian.hpp"
#include "./headers/metal/metal.hpp"
#include "./headers/dielectric/dielectric.hpp"

#include "./headers/main_header.hpp"

int main () {

    Hittable_list world;

    auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3(0,-1000,0), 1000, ground_material));

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto bubble = make_shared<Dielectric>(1.00 / 1.50);
    world.add(make_shared<Sphere>(Point3(0, 1, 0), 0.85, bubble));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point3(1.5, 1.2, -2), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point3(-1.7, 1.8, -2), 1.0, material3));

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.img_width = 1024;
    cam.samples_per_pixel = 500;
    cam.max_depth         = 50;

    cam.threads = 4;
    cam.img_gen = true;

    cam.vfov     = 25;
    cam.lookfrom = Point3(0,3,10);
    cam.lookat   = Point3(0,1,0);
    cam.vup      = Vec3(0,3,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0;

    cam.render(world);

    return 0;
}
