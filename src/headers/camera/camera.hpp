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
        int get_max_light_bounce() const;
        double get_vfov() const;
        Point3 get_origin() const;
        Point3 get_capture_target_pos() const;
        Vec3 get_y_unit() const;
        int get_threads_count() const;
        double get_defocus_angle() const;
        double get_focal_length() const;

        // setters
        void set_aspect_ratio(double);
        void set_img_width(int);
        void set_samples_per_pixel(int);
        void set_max_light_bounce(int);
        void set_vfov(double);
        void set_origin(Point3);
        void set_capture_target_pos(Point3);
        void set_y_unit(Vec3);
        void set_threads_count(int);
        void set_defocus_angle(double);
        void set_focal_length(double);

        ~Camera();

    private:
        std::vector<sf::Color> pixel_grid;
        double d_aspect_ratio      = 1.0;     // default aspect ratio is a square
        unsigned int    u_img_width         = 100;     // default image width is 100 pixels
        unsigned int    u_samples_per_pixel = 10;      // count for random samples per pixel
        unsigned int u_max_light_bounce = 10;      // max depth for recursion
        double vfov              = 90;      // vertical viewing angle
        Point3 P3_origin = Point3(0, 0, 0);
        Point3 P3_capture_target_pos = Point3(0, 0, -1);
        Vec3   V3_y_unit               = Vec3(0, 1, 0);
        unsigned int u_threads_count = 1;
        double d_defocus_angle = 0;
        double d_focal_length = 10;
        std::vector<std::thread> threads;
        unsigned int u_img_height;               // Rendered image height
        Point3 P3_center;                   // Camera center
        Point3 P3_pixel00_loc;              // Location of pixel 0, 0
        Vec3 V3_pixel_delta_u;            // Offset to pixel to the right
        Vec3 V3_pixel_delta_v;            // Offset to pixel below
        double d_pixel_samples_scale;      // Color scale factor for a sum of pixel samples
        Vec3 u, v, w;
        sf::Image i_image;
        Vec3 defocus_disk_u;        // Horizontal radius
        Vec3 defocus_disk_v;        // Vertical radius
        void initialize();
        Point3 defocus_disk_sample() const;
        Vec3 sample_square();
        Ray get_ray(int, int) const;
        Color ray_color(const Ray&, int, const Hittable&) const;
        Vec3 sample_square() const;
};

#endif
