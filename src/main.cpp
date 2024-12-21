#include "./headers/hittable_list/hittable_list.hpp"
#include "./headers/camera/camera.hpp"
#include "./headers/vec3/vec3.hpp"

#include "./headers/lambertian/lambertian.hpp"
#include "./headers/sphere/sphere.hpp"
#include "./headers/dielectric/dielectric.hpp"
#include "./headers/metal/metal.hpp"

#include <memory>

int main () {

    Hittable_list HL_world;

    auto Lam_ground_material = std::make_shared<Lambertian> (Color(0.5, 0.5, 0.5));
    auto Di_bubble          = std::make_shared<Dielectric> (1.00 / 1.50);
    auto Di_material1       = std::make_shared<Dielectric> (1.5);
    auto Lam_material2       = std::make_shared<Lambertian> (Color(0.4, 0.2, 0.1));
    auto Met_material3       = std::make_shared<Metal>      (Color(0.7, 0.6, 0.5), 0.0);

    HL_world.add(std::make_shared<Sphere>(Point3( 0  ,  1   ,  0), 1.0 , Di_material1));
    HL_world.add(std::make_shared<Sphere>(Point3( 0  , -1000,  0), 1000, Lam_ground_material));
    HL_world.add(std::make_shared<Sphere>(Point3( 0  ,  1   ,  0), 0.85, Di_bubble));
    HL_world.add(std::make_shared<Sphere>(Point3( 1.5,  1.2 , -2), 1.0 , Lam_material2));
    HL_world.add(std::make_shared<Sphere>(Point3(-1.7,  1.8 , -2), 1.0 , Met_material3));

    Camera Cam_camera;

    // Image specifications
    Cam_camera.aspect_ratio      = 16.0 / 9.0;
    Cam_camera.img_width         = 200;
    Cam_camera.samples_per_pixel = 1;
    Cam_camera.max_depth         = 50;

    // I/O utilities
    Cam_camera.threads = 4;
    Cam_camera.img_gen = true;

    // Camera Orientation
    Cam_camera.vfov     = 25;
    Cam_camera.lookfrom = Point3(0,3,10);
    Cam_camera.lookat   = Point3(0,1,0);
    Cam_camera.vup      = Vec3(0,3,0);

    // Camera Lens
    Cam_camera.defocus_angle = 0.6;
    Cam_camera.focus_dist    = 10.0;

    Cam_camera.render(HL_world);

    return 0;
}
