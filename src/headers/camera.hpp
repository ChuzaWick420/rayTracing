#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "main_header.hpp"
#include "hittable.hpp"

class camera {
    public:

        double aspect_ratio      = 1.0;     // default aspect ratio is a square
        int    img_width         = 100;     // default image width is 100 pixels
        int    samples_per_pixel = 10;      // count for random samples per pixel
        int    max_depth         = 10;      // max depth for recursion

        void render(const hittable& world) {
            initialize();
        
            //writer loop
            for (int i = 0; i < img_height; i++) {
                for (int j = 0; j < img_width; j++) {
                    color pixel_color(0, 0, 0);

                    for (int sample = 0; sample < samples_per_pixel; sample++) {
                        ray r = get_ray(j, i);
                        pixel_color += ray_color(r, max_depth, world);
                    }

                    write_color(file_ptr, pixel_color * pixel_samples_scale);
                }
            }
        }

        //close the file before camera destroys
        ~camera() {
            file_ptr.close();
        }

    private:

        std::ofstream file_ptr;                 // image to be rendered
        int           img_height;               // Rendered image height
        point3        center;                   // Camera center
        point3        pixel00_loc;              // Location of pixel 0, 0
        vec3          pixel_delta_u;            // Offset to pixel to the right
        vec3          pixel_delta_v;            // Offset to pixel below
        double        pixel_samples_scale;      // Color scale factor for a sum of pixel samples

        void initialize() {
            file_ptr.open("image.ppm");

            img_height = int(img_width / aspect_ratio);
            img_height = (img_height < 1) ? 1 : img_height;

            pixel_samples_scale = 1.0 / samples_per_pixel;

            //write image headers
            file_ptr << 
                "P3\n" << 
                int(img_width) << " " << int(img_height) << "\n" <<
                255 << "\n";

            center = point3(0, 0, 0);

            // Determine viewport dimensions.
            auto focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (double(img_width)/img_height);

            // Calculate the vectors across the horizontal and down the vertical viewport edges.
            auto viewport_u = vec3(viewport_width, 0, 0);
            auto viewport_v = vec3(0, -viewport_height, 0);

            // Calculate the horizontal and vertical delta vectors from pixel to pixel.
            pixel_delta_u = viewport_u / img_width;
            pixel_delta_v = viewport_v / img_height;

            // Calculate the location of the upper left pixel.
            auto viewport_upper_left =
                center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
                pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        }

        color ray_color(const ray& r, int depth, const hittable& world) const {
            if (depth <= 0)
                return color(0, 0, 0);

            hit_record rec;

            if (world.hit(r, interval(0.001, infinity), rec)) {
                vec3 direction = random_on_hemisphere(rec.normal);
                return 0.5 * ray_color(ray(rec.p, direction), depth - 1, world);
            }

            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
        }

        ray get_ray(int u, int v) const {

            // Construct a camera ray originating from the origin and directed at randomly sampled
            // point around the pixel location i, j.

            auto offset = sample_square();
            auto pixel_sample = pixel00_loc
                          + ((u + offset.x()) * pixel_delta_u)
                          + ((v + offset.y()) * pixel_delta_v);

            auto ray_origin = center;
            auto ray_direction = pixel_sample - ray_origin;

            return ray(ray_origin, ray_direction);
        }

        vec3 sample_square() const {
            // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
            return vec3(random_double() - 0.5, random_double() - 0.5, 0);
        }

};

#endif
