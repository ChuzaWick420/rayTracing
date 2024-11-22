#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../hittable/hittable.hpp"
#include "../color3/color3.hpp"

#include "SFML/Graphics.hpp"

#include "../main_header.hpp"
#include <vector>

class camera {
    public:

        double aspect_ratio      = 1.0;     // default aspect ratio is a square
        int    img_width         = 100;     // default image width is 100 pixels
        int    samples_per_pixel = 10;      // count for random samples per pixel
        int    max_depth         = 10;      // max depth for recursion
        bool   img_gen           = false;   // saves a png when true
        double vfov              = 90;      // vertical viewing angle
        point3 lookfrom          = point3(0, 0, 0);
        point3 lookat            = point3(0, 0, -1);
        vec3   vup               = vec3(0, 1, 0);

        double defocus_angle = 0;
        double focus_dist = 10;

        void render(const hittable&);

        ~camera();

    private:

        std::vector<sf::Color> pixel_grid;
        int window_width = 1024;
        int img_height;               // Rendered image height
        point3 center;                   // Camera center
        point3 pixel00_loc;              // Location of pixel 0, 0
        vec3 pixel_delta_u;            // Offset to pixel to the right
        vec3 pixel_delta_v;            // Offset to pixel below
        double pixel_samples_scale;      // Color scale factor for a sum of pixel samples
        vec3 u, v, w;

        vec3 defocus_disk_u;
        vec3 defocus_disk_v;

        void show_img();

        void initialize();

        point3 defocus_disk_sample() const;

        vec3 sample_square();
        ray get_ray(int, int) const;

        color ray_color(const ray&, int, const hittable&) const;
        vec3 sample_square() const;
};

#endif
