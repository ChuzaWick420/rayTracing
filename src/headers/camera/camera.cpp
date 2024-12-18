#include "../camera/camera.hpp"
#include "../interval/interval.hpp"
#include "../hit_record/hit_record.hpp"
#include "../material/material.hpp"

void Camera::show_img() {

    int window_height = window_width / aspect_ratio;

    // Window to render image on
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Ray Tracing", sf::Style::Default);

    float scalar = float(window_width) / img_width;

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

void Camera::render(const Hittable& world) {
    initialize();

    int total_pixels = img_height * img_width;

    pixel_grid.resize(total_pixels);

    int thread_load = total_pixels / threads;

    for (int j = 1; j <= threads; j++) {
        worker_threads.push_back(std::thread([&, j] {

            int thread_id = j;

            for (int i = 0; i < thread_load; i++) {

                int offset = (thread_id - 1) * thread_load;

                Color pixel_color(0, 0, 0);

                int x = i % img_width;
                int y = (i + offset) / img_width;

                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    Ray r = get_ray(x, y);
                    pixel_color += ray_color(r, max_depth, world);
                }

                write_color(&pixel_grid[y * img_width + x], pixel_color * pixel_samples_scale);

                this->i_image.setPixel(x, y, pixel_grid[y * img_width + x]);

                //debug
                /*printf(*/
                /*    "Thread_id: %d,\nThread_load: %d,\nOffset: %d,\nPosition: (%d, %d),\nColor: (%d, %d, %d),\n",*/
                /*    thread_id,*/
                /*    thread_load,*/
                /*    offset,*/
                /*    x, y,*/
                /*    pixel_grid[i + offset].r, pixel_grid[i + offset].g, pixel_grid[i + offset].b*/
                /*);*/
            }

        }));
    }

    //waiting for threads
    std::for_each(
        worker_threads.begin(),
        worker_threads.end(),
        [](std::thread &t) {
            t.join();
        }
    );

    // optionally save the image
    if (this->img_gen == true)
        i_image.saveToFile("rendered_img.png");

    this->show_img();
}

void Camera::initialize() {
    img_height = int(img_width / aspect_ratio);
    img_height = (img_height < 1) ? 1 : img_height;

    pixel_samples_scale = 1.0 / samples_per_pixel;

    center = lookfrom;

    i_image.create(img_width, img_height);

    // Determine viewport dimensions.
    auto theta = degrees_to_radians(vfov);
    auto h = std::tan(theta / 2);
    auto viewport_height = 2 * h * focus_dist;
    auto viewport_width = viewport_height * (double(img_width)/img_height);

    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = viewport_width * u;
    auto viewport_v = viewport_height * -v;

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / img_width;
    pixel_delta_v = viewport_v / img_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Calculate the camera defocus disk basis vectors
    auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
}


Vec3 Camera::sample_square() const {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
    return Vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

Ray Camera::get_ray(int u, int v) const {

    // Construct a camera ray originating from the defocus disk and directed at a randomly
    // sampled point around the pixel location u, v.

    auto offset = sample_square();
    auto pixel_sample = pixel00_loc
                        + ((u + offset.x()) * pixel_delta_u)
                        + ((v + offset.y()) * pixel_delta_v);

    auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;

    return Ray(ray_origin, ray_direction);
}

Point3 Camera::defocus_disk_sample() const {
    auto p = random_in_unit_disk();
    return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}

Color Camera::ray_color(const Ray& r, int depth, const Hittable& world) const {
    if (depth <= 0)
        return Color(0, 0, 0);

    Hit_record rec;

    if (world.hit(r, Interval(0.001, infinity), rec)) {
        Ray scattered;
        Color attenuation;

        if (rec.mat->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, depth-1, world);

        return Color(0,0,0);
    }

    Vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);

    return (1.0-a)*Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
}

Camera::~Camera() {}
