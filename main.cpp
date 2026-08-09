#include "vec3.h"
#include "color.h"
#include "ray.h"


#include <iostream>

color ray_color(const ray& r){
    return color(0,0,0);
}

int main() {

    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate image height, ensure at least 1
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    // Calculated aspect ratio can differ from ideal aspect ratio 
    double calc_aspect_ratio = image_width / image_height;

    // Camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * calc_aspect_ratio;
    auto camera_center = point3(0,0,0);

    // Calculate vectors across horzontal and down vertical of viewport edges
    auto viewport_u = vec3(viewport_width, 0, 0);
    // Camera convention is +Y = up, so viewport Y direction is negative
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate horizontal and vertical delta vectors b/t pixels
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate location of upper left (0,0)
    auto viewport_upper_left = camera_center 
                                - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v /2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++){
        // progress bar
        std::clog << "\rScanlines remianing: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++){
            auto pixel_color = color(double(i)/(image_width-1), double(j) / (image_height-1), 0.0);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                   \n";
}