#include "engine.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>

Engine::Engine(Configuration C_config) :
    WM_window(
        C_config.str_title, {
            C_config.u_win_width,
            (unsigned int)(C_config.u_win_width / C_config.f_aspect_ratio)
        },
        C_config.clr_win_bg
    ),
    S_scene(C_config.v_sptr_HL_objects),
    save_img(C_config.b_img_gen_permission)
{

    Cam_camera.set_aspect_ratio(C_config.f_aspect_ratio);
    Cam_camera.set_img_width(C_config.u_img_width);
    Cam_camera.set_samples_per_pixel(C_config.u_samples_per_pixel);
    Cam_camera.set_max_light_bounce(C_config.u_max_light_bounce);
    Cam_camera.set_threads(C_config.u_max_threads);
    Cam_camera.set_vfov(C_config.i_vfov);
    Cam_camera.set_lookfrom(C_config.P3_cam_origin);
    Cam_camera.set_lookat(C_config.P3_target_capture_pos);
    Cam_camera.set_vup(C_config.V3_cam_y_unit);
    Cam_camera.set_defocus_angle(C_config.f_cam_defocus_angle);
    Cam_camera.set_focus_dist(C_config.f_local_length);

}

void Engine::run() {
    std::cout << "Running Ray Tracing Version 0.0.1" << std::endl;

    Hittable_list& HL_ref_scene = S_scene.create_scene();

    std::cout << "Scene Generated Successfully" << std::endl;

    sf::Image* I_ref_image = Cam_camera.render(HL_ref_scene);

    std::cout << "Image Generated Successfully" << std::endl;

    if (save_img)
        I_ref_image->saveToFile("./rendered_img.png");

    std::cout << "Image Saved Successfully" << std::endl;

    WM_window.display(I_ref_image);
}
