#ifndef COLOR_H
#define COLOR_H
#define COLORCAST 255.999

#include "vec3.hpp"
#include <iostream>

using color = vec3;

void write_color(std::ostream& out, color pixel_color) {
    out << static_cast<int>(COLORCAST * pixel_color.x()) << ' '
        << static_cast<int>(COLORCAST * pixel_color.y()) << ' '
        << static_cast<int>(COLORCAST * pixel_color.z()) << '\n';
}


#endif