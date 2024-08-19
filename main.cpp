#include <iostream>
#include <fstream>

#include "./headers/vec3.hpp"
#include "./headers/color3.hpp"
#include "./headers/ray.hpp"

color ray_color(const ray& r) {
    return color(0, 0, 0);
}

int main () {
    
    //defining image dimensions
    int img_width, img_height;
    float aspect_ratio = 16.0f/9.0f;

    img_width = 200;
    img_height = aspect_ratio * img_width;

    //image creation
    std::ofstream file_ptr("image.ppm");

    //image headers
    file_ptr << 
        "P3\n" << 
        img_height << " " << img_width << "\n" <<
        255 << "\n";

    //camera stuff
    auto viewport_height = 2.0f;
    auto viewport_width = viewport_height * double(img_width / img_height);
    auto focal_length = 1.0f;
    auto camera_center = point3(0, 0, 0);

    //viewport vectors
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    //pixel space
    auto pixel_delta_u = viewport_u / img_width;
    auto pixel_delta_v = viewport_v / img_height;

    //writer loop
    for (int i = 0; i < img_height; i++) {
        for (int j = 0; j < img_width; j++) {
            write_color(file_ptr, color(i, j, 0));
        }
    }

    //image saving
    file_ptr.close();
    
    return 0;
}
