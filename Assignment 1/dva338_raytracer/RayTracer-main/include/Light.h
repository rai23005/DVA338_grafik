#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Vec3.h"  // Inkludera Vec3f.h för att använda Vec3f för position och färg

class Light {
public:

    // Light position
    Vec3f position;  

    // The color of the light (red, green, and blue light) / the intersivt of the light 
    Vec3f color;     

    // Default constructor
    Light() : position(Vec3f(0.0f, 0.0f, 0.0f)), 
        color(Vec3f(0.0f, 0.0f, 0.0f)) {}  

    // Constructor with parameters
    Light(const Vec3f& pos, const Vec3f& col)
        : position(pos), color(col) {}
};

#endif