#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Ray.h"
#include "Material.h"

class Object {
    private:
public:
    virtual ~Object() {};
    virtual bool hit(const Ray & r, HitRec & rec) const = 0;


     
    Material mat;


    const Object* hitObject = nullptr;


    //Metod for get properties value in object
    virtual Vec3f getColor() const = 0;
    virtual Vec3f getAmbient() const = 0;
    virtual Vec3f getDiffuse() const = 0;
    virtual Vec3f getSpecular() const = 0;
    virtual float getShininess() const = 0;
 
    //Get the normal for a point 
    virtual Vec3f getNormal(const Vec3f& hitPoint) const = 0;

    //Metod for get properties of the material 
    Material getMaterial() const { return mat; }






};

#endif