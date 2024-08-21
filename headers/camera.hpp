#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "main_header.hpp"
#include "hittable.hpp"

class camera {
    public:

        double aspect_ratio = 1.0;  //default aspect ratio is a square
        int img_width = 100;        //default image width is 100 pixels

        void render(const hittable& world) {
            initialize();
        
            //writer loop
            for (int i = 0; i < img_height; i++) {
                for (int j = 0; j < img_width; j++) {
                    auto pixel_center = pixel00_loc + (j * pixel_delta_u) + (i * pixel_delta_v);
                    auto ray_direction = pixel_center - center;

                    ray r(center, ray_direction);
                    color pixel_color = ray_color(r, world);
                    write_color(file_ptr, pixel_color);
                }
            }
        }

        //close the file before camera destroys
        ~camera() {
            file_ptr.close();
        }

    private:

        std::ofstream file_ptr;                 //image to be rendered
        int           img_height;               // Rendered image height
        point3        center;                   // Camera center
        point3        pixel00_loc;              // Location of pixel 0, 0
        vec3          pixel_delta_u;            // Offset to pixel to the right
        vec3          pixel_delta_v;            // Offset to pixel below

    void initialize() {

        file_ptr.open("image.ppm");

        img_height = int(img_width / aspect_ratio);
        img_height = (img_height < 1) ? 1 : img_height;

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

    color ray_color(const ray& r, const hittable& world) const {
        hit_record rec;

        if (world.hit(r, interval(0, infinity), rec)) {
            return 0.5 * (rec.normal + color(1,1,1));
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }

};

#endif
