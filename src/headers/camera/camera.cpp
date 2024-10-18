#include "./camera.hpp"
#include <cstdint>

void camera::show() {

    int window_width = aspect_ratio * window_height;

    // Window to render image on
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Ray Tracing", sf::Style::Default);

    float scalar = float(window_width) / img_width;

    //creates an image
    sf::Image i_image;
    i_image.create(img_width, img_height);

    for(int i = 0; i < img_height; i++) {
        for (int j = 0; j < img_width; j++) {
            i_image.setPixel(j, i, pixel_grid[i][j]);
        }
    }
    
    sf::Texture t_image;
    t_image.loadFromImage(i_image);

    sf::Sprite s_image(t_image);
    s_image.setScale(sf::Vector2f(scalar, scalar));

    while (window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Green);

        window.draw(s_image);

        window.display();
    }
}

void camera::render(const hittable& world) {
    initialize();
        
    //writer loop
    for (int i = 0; i < img_height; i++) {
        for (int j = 0; j < img_width; j++) {
            color pixel_color(0, 0, 0);

            for (int sample = 0; sample < samples_per_pixel; sample++) {
                ray r = get_ray(j, i);
                pixel_color += ray_color(r, max_depth, world);
            }

            write_color(&pixel_grid[i][j], pixel_color * pixel_samples_scale);
        }
    }

   this->show();
}

void camera::initialize() {
    //file_ptr.open("image.ppm");

    img_height = int(img_width / aspect_ratio);
    img_height = (img_height < 1) ? 1 : img_height;

    pixel_samples_scale = 1.0 / samples_per_pixel;

    pixel_grid = new sf::Color*[img_height];
 
    for (int i = 0; i < img_width; i++) {
        pixel_grid[i] = new sf::Color[img_width];
    }

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


vec3 camera::sample_square() const {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

ray camera::get_ray(int u, int v) const {

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


color camera::ray_color(const ray& r, int depth, const hittable& world) const {
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


//close delete img data before camera destroys
camera::~camera() {
    int img_height = img_width / aspect_ratio;
    for (int j = 0; j < img_height; j++) {
        delete [] pixel_grid[j];
    }
}
