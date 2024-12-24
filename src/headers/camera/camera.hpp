#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../hittable/hittable.hpp"
#include "../vec3/vec3.hpp"
#include "../color/color.hpp"

#include <vector>
#include <thread>

#include <SFML/Graphics.hpp>

class Camera {
    public:
        sf::Image* render(const Hittable&);

        // getters
        double get_aspect_ratio() const;
        int get_img_width() const;
        int get_samples_per_pixel() const;
        int get_max_depth() const;
        double get_vfov() const;
        Point3 get_lookfrom() const;
        Point3 get_lookat() const;
        Vec3 get_vup() const;
        int get_threads() const;
        double get_defocus_angle() const;
        double get_focus_dist() const;

        // setters
        void set_aspect_ratio(double);
        void set_img_width(int);
        void set_samples_per_pixel(int);
        void set_max_depth(int);
        void set_vfov(double);
        void set_lookfrom(Point3);
        void set_lookat(Point3);
        void set_vup(Vec3);
        void set_threads(int);
        void set_defocus_angle(double);
        void set_focus_dist(double);

        ~Camera();

    private:
        std::vector<sf::Color> pixel_grid;
        double aspect_ratio      = 1.0;     // default aspect ratio is a square
        int    img_width         = 100;     // default image width is 100 pixels
        int    samples_per_pixel = 10;      // count for random samples per pixel
        int    max_depth         = 10;      // max depth for recursion
        double vfov              = 90;      // vertical viewing angle
        Point3 lookfrom          = Point3(0, 0, 0);
        Point3 lookat            = Point3(0, 0, -1);
        Vec3   vup               = Vec3(0, 1, 0);
        int threads = 1;
        double defocus_angle = 0;
        double focus_dist = 10;
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
        void initialize();
        Point3 defocus_disk_sample() const;
        Vec3 sample_square();
        Ray get_ray(int, int) const;
        Color ray_color(const Ray&, int, const Hittable&) const;
        Vec3 sample_square() const;
};

#endif
