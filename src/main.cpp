#include "rtweekend.h"

#include "bvh.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "quad.h"
#include "sphere.h"
#include "material.h"
#include "texture.h"

#include <chrono>
 

void three_sphere()
{
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5,0.5,0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    //CENTER
    //
    //world.add(make_shared<sphere>(point3(0,1,0),1,make_shared<lambertian>(checker)));

    // //LEFT 
    // auto diffused_mat_red = make_shared<metal>(color(2,0,0), 0.6);
    // world.add(make_shared<sphere>(point3(0,1,2),1,diffused_mat_red));

    // //RIGHT
    // auto diffused_mat_green = make_shared<lambertian>(color(0,2,0));
    // world.add(make_shared<sphere>(point3(0,1,-2),1,diffused_mat_green));

    world = hittable_list(make_shared<bvh_node>(world));

    camera cam;

    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 400; 
    cam.sample_per_pixel = 50;
    cam.max_depth = 50;
    cam.background = color(0.7, 0.8, 1.0);

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,1,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0;

    cam.render(world);

}

void checkered_spheres()
{
    hittable_list world;

    auto checker = make_shared<checker_texture>(0.32,color(.2, .3, .1), color(.9, .9, .9));

    world.add(make_shared<sphere>(point3(0,-10,0), 10, make_shared<lambertian>(checker)));
    world.add(make_shared<sphere>(point3(0,10,0), 10, make_shared<lambertian>(checker)));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.sample_per_pixel = 100;
    cam.max_depth = 50;
    cam.background = color(0.7, 0.8, 1.0);

    cam.vfov = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat = point3(0,0,0);
    cam.vup = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}

void earth()
{
    auto earth_texture = make_shared<image_texture>("earthmap.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);
    auto globe = make_shared<sphere>(point3(0,0,0), 2, earth_surface);

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.sample_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background = color(0.7, 0.8, 1.0);

    cam.vfov     = 20;
    cam.lookfrom = point3(0,0,12);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(hittable_list(globe));
}

void perlin_spheres()
{
    hittable_list world;

    auto pretext = make_shared<noise_texture>(4);
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(pretext)));
    world.add(make_shared<sphere>(point3(0,2,0), 2, make_shared<lambertian>(pretext)));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.sample_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background = color(0.7, 0.8, 1.0);

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);

}

void quads()
{
    hittable_list world;

    //Materials
    auto left_red     = make_shared<lambertian>(color(1.0,0.2,0.2));
    auto back_green   = make_shared<lambertian>(color(0.2, 1.0, 0.2));
    auto right_blue   = make_shared<lambertian>(color(0.2, 0.2, 1.0));
    auto upper_orange = make_shared<lambertian>(color(1.0, 0.5, 0.0));
    auto lower_teal   = make_shared<lambertian>(color(0.2, 0.8, 0.8));


    //Quads
    world.add(make_shared<quad>(point3(-3,-2,5), vec3(0,0,-4), vec3(0,4,0), left_red));
    world.add(make_shared<quad>(point3(-2,-2, 0), vec3(4, 0, 0), vec3(0, 4, 0), back_green));
    world.add(make_shared<quad>(point3( 3,-2, 1), vec3(0, 0, 4), vec3(0, 4, 0), right_blue));
    world.add(make_shared<quad>(point3(-2, 3, 1), vec3(4, 0, 0), vec3(0, 0, 4), upper_orange));
    world.add(make_shared<quad>(point3(-2,-3, 5), vec3(4, 0, 0), vec3(0, 0,-4), lower_teal));

    camera cam;

    cam.aspect_ratio      = 1.0;
    cam.image_width       = 400;
    cam.sample_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background = color(0.7, 0.8, 1.0);

    cam.vfov     = 80;
    cam.lookfrom = point3(0,0,9);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}

void simple_light()
{
    hittable_list world;

    auto myMat = make_shared<solid_color>(color(0,0,1));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(myMat)));
    world.add(make_shared<sphere>(point3(0,2,0), 2, make_shared<lambertian>(myMat)));

    auto diffLight = make_shared<diffuse_light>(color(5,5,5));
    world.add(make_shared<sphere>(point3(0,8,0), 2, diffLight));
    world.add(make_shared<quad>(point3(3,1,-2), vec3(2,0,0), vec3(0,2,0), diffLight));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.sample_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background        = color(0,0,0);

    cam.vfov     = 20;
    cam.lookfrom = point3(26,3,6);
    cam.lookat   = point3(0,2,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}

void cornell_box()
{
    hittable_list world;

    //Materials
    auto red = make_shared<lambertian>(color(.65,.05,.05));
    auto white = make_shared<lambertian>(color(.73,.73,.73));
    auto green = make_shared<lambertian>(color(.12,.45,.15));
    auto light = make_shared<diffuse_light>(color(15,15,15));

    //Objects
    world.add(make_shared<quad>(point3(555,0,0), vec3(0,555,0), vec3(0,0,555), green));
    world.add(make_shared<quad>(point3(0,0,0), vec3(0,555,0), vec3(0,0,555), red));
    world.add(make_shared<quad>(point3(343, 554, 332), vec3(-130,0,0), vec3(0,0,-105), light));
    world.add(make_shared<quad>(point3(0,0,0), vec3(555,0,0), vec3(0,0,555), white));
    world.add(make_shared<quad>(point3(555,555,555), vec3(-555,0,0), vec3(0,0,-555), white));
    world.add(make_shared<quad>(point3(0,0,555), vec3(555,0,0), vec3(0,555,0), white));

    shared_ptr<hittable> box1 = box(point3(0,0,0), point3(165,330,165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265,0,295));
    world.add(box1);

    shared_ptr<hittable> box2 = box(point3(0,0,0), point3(165,165,165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, vec3(130,0,65));
    world.add(box2);

    //Scene properties
    camera cam;

    cam.aspect_ratio      = 1.0;
    cam.image_width       = 600;
    cam.sample_per_pixel  = 500;
    cam.max_depth         = 50;
    cam.background        = color(0,0,0);

    cam.vfov     = 40;
    cam.lookfrom = point3(278, 278, -800);
    cam.lookat   = point3(278, 278, 0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);

}

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();

    //RUN program
    earth();

    
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    std::clog << "time taken: "<< duration.count()<< " seconds\n" << std::flush;

    return 0;
};