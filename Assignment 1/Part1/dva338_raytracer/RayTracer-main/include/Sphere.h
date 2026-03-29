#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Vec3.h"
#include "Ray.h"
#include "Object.h"



class Sphere : public Object {
public:
	Vec3f c; //Center of the sphere
	float r; //RAdius of the sphere

	// Color to the sphere 
	Material mat;


public:
	
	// Constructor
	Sphere(const Vec3f& cen, float rad, const Material& material) : c(cen), r(rad), mat(material) {}

	// Check if the ray intersects with the sphere
	bool hit(const Ray & r, HitRec & rec) const;

	// Compute surface fields
	void computeSurfaceHitFields(const Ray & r, HitRec & rec) const;

	//metod to get color of the sphere 
	Vec3f getColor() const {
		return mat.color; 

	}

	//Get metod for value of 
	Vec3f getAmbient() const { return mat.ambient;}
	Vec3f getDiffuse() const {return mat.diffuse;}
	Vec3f getSpecular() const {	return mat.specular;}
	float getShininess() const {return mat.shininess;}



	//Get normal for the Spehre
	Vec3f Sphere::getNormal(const Vec3f& hitPoint) const {
		return (hitPoint - c).getNormalized();
	}

	Material getMaterial() const { return mat; }


};

#endif