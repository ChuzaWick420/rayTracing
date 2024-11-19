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

    // World
    hittable_list world;

    auto material_ground  = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center  = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left    = make_shared<metal>(color(0.8, 0.8, 0.8), 0.08);
    auto material_right   = make_shared<dielectric>(1.50);
    auto material_bubble  = make_shared<dielectric>(1.00 / 1.50);

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.35, material_bubble));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.img_width = 1024;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;
    cam.img_gen = false;
    cam.vfov = 90;

    cam.render(world);

    return 0;
}
