#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "./vec3/vec3.hpp"

#include <string>

#include <SFML/Graphics.hpp>

enum Material_id_map {
    LAMBERTIAN, 
    DIELECTRIC,
    METAL,
    MATT
};

struct Objects {
    Vec3 v3_pos;
    float f_radius;
    int u_material_id;
};

struct Configuration {
    float aspect_ratio = 16.0f / 9.0f;
    unsigned int u_img_width = 1024;
    unsigned int u_win_width= 1024;
    sf::Color clr_win_bg = sf::Color(255, 0, 0);
    bool b_img_gen_permission = true;
    unsigned int u_max_threads = 4;
    int i_vfov = 25;
    unsigned int u_samples_per_pixel = 1;
    Color sky = Color(0.5, 0.7, 1.0);
    Point3 p3_cam_origin = Point3(0, 3, 10);
    Point3 p3_target_capture_pos = Point3(0, 1, 0);
    Vec3 v3_cam_height = Vec3(0, 3, 0);
    float f_cam_defocus_angle = 0.6;
    float f_local_length = 10.0;
    std::string title = "Ray Tracing";

    Objects[] = {
        {Vec3(0, 0, 0), 0.5, Material_id_map::MATT},
        {Vec3(0, 1, 0), 0.7, Material_id_map::METAL}
    };
};

#endif
