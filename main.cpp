#include "utils.hpp"

#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "material.hpp"

int main() {

    // World
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    // world.add(make_shared<sphere>(point3(1, 1, 1), 1, make_shared<metal>(color(1, 1, 1), 0)));
    // world.add(make_shared<sphere>(point3(3, 0.6, 3), .6, make_shared<metal>(color(.9, 0, .1), .7)));
    // world.add(make_shared<sphere>(point3(4, .8, .2), .8, make_shared<metal>(color(.8, .8, .8), 0)));
    // world.add(make_shared<sphere>(point3(6, .4, 1.5), .4, make_shared<dielectric>(1.5)));

    for (int i = -15; i < 15; i++) {
        for (int j = -15; j < 15; j++) {
            auto choose_mat = random_double();
            point3 center(i + .5*random_double(), 0.3, j + .5*random_double());

            if ((center - point3(4, 0.3, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.3) {
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                } else if (choose_mat < 0.7) {
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                } else {
                    sphere_material = make_shared<dielectric>(1.5);
                }
                world.add(make_shared<sphere>(center, 0.3, sphere_material));
            }
        }
    }


    // Camera
    camera cam;
    cam.aspect_ratio      = 16.0/9.0;
    cam.image_width       = 1920;
    cam.samples_per_pixel = 500;
    cam.max_depth         = 100;

    cam.vfov     = 50;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0, 0, 0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = .5;
    cam.focus_dist = 10;
    
    cam.render(world);
    

}