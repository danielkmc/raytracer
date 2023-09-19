# Ray Tracing Rendering

![ray tracing](images/raytracing.png)
This is a basic ray tracing project written in C++. It simulates the concept of tracing light rays to objects to illuminate and project shadows. Currently, this project features:

1. Light diffusion for metallic (reflective) and lambertian (matte) surfaces
2. Reflectance and refraction of dielectric materials (water, glass)
3. Camera positioning and Field-of-View (FOV)
4. Anti-aliasing

## Components

### Camera Class `camera.hpp`

This class controls all aspects regarding camera positioning and rendering of the image, including field-of-view (FOV), depth-of-field effects, and pixel-sampling to create an anti-aliasing effect.

#### Field of view

Field of view determines how much can be seen in the image at once and is set by the `camera.vfov` parameter, defining the vertical field of view of the camera. Here are three images displaying varying levels of field of view
| vfov=20 | vfov=50 | vfov=90 |
| - | - | - |
| ![20 vfov](images/three_spheres4.png) | ![20 vfov](images/three_spheres4_50vfov.png) | ![20 vfov](images/three_spheres4_90vfov.png) |

As the vertical field of view increases, the horizontal increases to maintain the ratio between the viewport's height and width parameters.

#### Depth of field

Depth of field, or defocus blur, is simulated by randomizing ray generation from a disk centered at our camera center, with the radius of this disk determined by the focus distance of the camera and the range of ray angles the viewport's center pixel color is calculated from.

This provides the effect of having varying sizes of aperture lenses in photography where blurring is used to give a sense of depth to an image.

Here are three images, from left to right, where the first has no defocus angle and a focus distance of 10, the second has a focus distance of 10 and defocus angle of 5, and the third has a focus distance of 10 and defocus angle of 10:
| No defocus blur| Defocus angle = 5| Defocus angle = 10|
| - | - | - |
| ![no defocus blur](images/three_spheres3.png) | ![defocus blur 5](images/three_spheres_5angle.png) | ![defocus blur 10](images/three_spheres_10angle.png) |

The red sphere stays in focus since it is within the focus plane determined by the focus distance, while the dielectric and metal spheres become blurrier as the "lens" increases in size (defocus angle increasing).

<!-- <p float="left">
   <img src="images/three_spheres3.png" width="33%" /> 
   <img src="images/three_spheres_5angle.png" width="33%" /> 
   <img src="images/three_spheres_10angle.png" width="33%" /> 
</p> -->

#### Antialiasing

Antialiasing is the process that removes the jagged-ness of pixel boundaries between two different objects, typically done by taking a sample of the surroundings and blending the pixels that define the boundary and the surrounding areas. By blending the pixel boundaries, the image produces a softer boundary.

Pixel sampling from a circle or a square are used in this project to provide antialiasing. Here are three images showing circle vs. square vsx no antialiasing:

| No antialiasing | Circle sampling | Square sampling |
| - | - | - |
| ![no antialiasing](images/three_spheres4_noantialiasing.png) | ![circle sampling](images/three_spheres4_circle.png) | ![square sampling](images/three_spheres4_square.png) |

Zooming in, we can see that the boundary between the red sphere and the background shows that the circle sampling makes a smoother edge opposed to square, and no antialiasing make the boundary appear rough:

| No antialiasing | Circle sampling | Square sampling |
| - | - | - |
| ![no antialiasing](images/antialiasing_none.png) | ![circle sampling](images/antialiasing_circle.png) | ![square sampling](images/antialiasing_square.png) |

#### Pixel Sampling

The `camera.samples_per_pixel` parameter controls how many samples we take when averaging a pixel's rendered color. Having this parameter too low introduces more noise in the final rendered image as seen in the following image rendered with the parameter set to 25:

Increasing this parameter to 100 produces a significant improving in the rendered image:


---

### Material Class `material.hpp`

This class provides the structure for all classes that inherit from it, and only provides the scatter function that computes the scattering of rays that hit objects. There are three kinds of materials defined:

1. Lambertian
2. Metallic
3. Dielectric

---

### Hittable Class `hittable.hpp`

To determine if an object was hit by a ray and what to do after, the hittable class provides the details of the reaction the light will have after hitting: the material to determine what kind of light diffusion and the surface normal vector from the point where the ray hit the object.

Whether we see the point is also determine by calculating whether the ray hit the surface on the side that we see. If the normal vector, pointing outwards from the surface, is in the opposite direction as the ray that we projected to produce it, then we know the surface is facing the camera.

#### Hittable list (world) `hittable_list.hpp`

This class is a list of hittable objects that are being rendered in the current image and provides a way to track all the hittable objects that rays can encounter.

---

## Future changes

1. Different anti-aliasing methods
   1. gaussian blur
2. Add different shapes
   1. rectangle
3. Add models with triangle meshes
4. Parallelizing the rendering process with threads or cuda

