#include <fstream>

#include "./headers/main_header.hpp"
#include "./headers/hittable.hpp"
#include "./headers/hittable_list.hpp"
#include "./headers/sphere.hpp"

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;

    if (world.hit(r, interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.0, 0.0, 0.0);
}

int main () {
    
    //defining image dimensions
    float img_width, img_height;
    float aspect_ratio = 16.0/9.0;

    img_width = 400.0;
    img_height = img_width / aspect_ratio;

    //height correction
    img_height = (img_height < 1) ? 1 : img_height;

    //image creation
    std::ofstream file_ptr("image.ppm");

    //image headers
    file_ptr << 
        "P3\n" << 
        int(img_width) << " " << int(img_height) << "\n" <<
        255 << "\n";

    // World
    hittable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    //camera stuff
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(img_width) / img_height);
    auto focal_length = 1.0;
    auto camera_center = point3(0, 0, 0);

    //viewport vectors
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    //pixel space
    auto pixel_delta_u = viewport_u / img_width;
    auto pixel_delta_v = viewport_v / img_height;

    //edge
    auto viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    //writer loop
    for (int i = 0; i < img_height; i++) {
        for (int j = 0; j < img_width; j++) {
            auto pixel_center = pixel00_loc + (j * pixel_delta_u) + (i * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;

            ray r(camera_center, ray_direction);
            color pixel_color = ray_color(r, world);
            write_color(file_ptr, pixel_color);
        }
    }

    //image saving
    file_ptr.close();
    
    return 0;
}
