#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../hittable/hittable.hpp"
#include "../color3/color3.hpp"

#include "SFML/Graphics.hpp"

#include "../main_header.hpp"

#include <vector>
#include <thread>
#include <algorithm>

class Camera {
    public:

        double aspect_ratio      = 1.0;     // default aspect ratio is a square
        int    img_width         = 100;     // default image width is 100 pixels
        int    samples_per_pixel = 10;      // count for random samples per pixel
        int    max_depth         = 10;      // max depth for recursion
        bool   img_gen           = false;   // saves a png when true
        double vfov              = 90;      // vertical viewing angle
        Point3 lookfrom          = Point3(0, 0, 0);
        Point3 lookat            = Point3(0, 0, -1);
        Vec3   vup               = Vec3(0, 1, 0);

        int threads = 1;

        double defocus_angle = 0;
        double focus_dist = 10;

        void render(const Hittable&);

        ~Camera();

    private:

        std::vector<sf::Color> pixel_grid;
        std::vector<std::thread> worker_threads;
        int window_width = 1024;
        int img_height;               // Rendered image height
        Point3 center;                   // Camera center
        Point3 pixel00_loc;              // Location of pixel 0, 0
        Vec3 pixel_delta_u;            // Offset to pixel to the right
        Vec3 pixel_delta_v;            // Offset to pixel below
        double pixel_samples_scale;      // Color scale factor for a sum of pixel samples
        Vec3 u, v, w;
        sf::Image i_image;

        Vec3 defocus_disk_u;
        Vec3 defocus_disk_v;

        void show_img();

        void initialize();

        Point3 defocus_disk_sample() const;

        Vec3 sample_square();
        Ray get_ray(int, int) const;

        Color ray_color(const Ray&, int, const Hittable&) const;
        Vec3 sample_square() const;
};

#endif
