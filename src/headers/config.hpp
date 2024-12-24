#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "./vec3/vec3.hpp"
#include "./color/color.hpp"
#include "./hittable/hittable.hpp"

#include "./sphere/sphere.hpp"
#include "./lambertian/lambertian.hpp"
#include "./metal/metal.hpp"
#include "./dielectric/dielectric.hpp"

#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

struct Configuration {
    float        f_aspect_ratio        = 16.0f / 9.0f;
    unsigned int u_img_width           = 1024;
    unsigned int u_win_width           = 1024;
    bool         b_img_gen_permission  = true;
    unsigned int u_max_light_bounce    = 50;
    unsigned int u_max_threads         = 2;
    int          i_vfov                = 25;
    unsigned int u_samples_per_pixel   = 500;
    float        f_cam_defocus_angle   = 0.6;
    float        f_local_length        = 10.0;
    std::string  str_title             = "Ray Tracing";
    sf::Color    clr_win_bg            = sf::Color(255, 0, 0);
    Color        clr_sky               = Color(0.5, 0.7, 1.0);
    Point3       P3_cam_origin         = Point3(0, 3, 10);
    Point3       P3_target_capture_pos = Point3(0, 1, 0);
    Vec3         V3_cam_y_unit         = Vec3(0, 1, 0);

    std::vector<std::shared_ptr<Hittable>> v_sptr_HL_objects = {
        std::make_shared<Sphere>(
            Point3(-1.7, 1.8, -2),          // Position
            1.0,                            // radius
            std::make_shared<Metal>(        // type
                Color(0.7, 0.6, 0.5),       // color
                0.05                        // fuzz
            )
        ),
        std::make_shared<Sphere>(
            Point3(1.5, 1.2, -2),           // Position
            1.0,                            // radius
            std::make_shared<Lambertian>(   // type
                Color(0.4, 0.2, 0.1)        // color
            )
        ),
        std::make_shared<Sphere>(
            Point3(0, 1, 0),                // Position
            1,                              // radius
            std::make_shared<Dielectric>(   // type
                1.5                         // refractive index
            )
        ),
        std::make_shared<Sphere>(
            Point3(0, 1, 0),                // Position
            0.85,                           // radius
            std::make_shared<Dielectric>(   // type
                1.00 / 1.50                 // refractive index
            )
        ),
        std::make_shared<Sphere>(
            Point3(0, -1000, 0),            // Position
            1000,                           // radius
            std::make_shared<Lambertian>(   // type
                Color(0.5, 0.5, 0.5)        // color
            )
        ),
    };
};

#endif
