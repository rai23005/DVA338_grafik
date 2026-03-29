#ifndef _PLAN_H_
#define _PLAN_H_

#include "Vec3.h"
#include "Ray.h"
#include "Object.h"


class Plan : public Object {
public:
	Vec3f point; //Point for the plane
	Vec3f normal; //The normal vector for the plan

	// Color for the plan 
	Material mat;


public:

	// Plan can have diffrent color
	Plan(const Vec3f& point, const Vec3f& normal, const Material& material)
		: point(point), normal(normal.getNormalized()), mat(material) {}

	// Check if the ray intersects with the plane
	bool hit(const Ray& r, HitRec& rec) const;

	// Compute surface fields like normal
	void computeSurfaceHitFields(const Ray& r, HitRec& rec) const;

	//metod to get color of the plan 
	Vec3f getColor() const {
		return mat.color; 
	}

	//Get the plane normal
	Vec3f getNormal(const Vec3f& hitPoint) const override {
		return normal; 
	}

	//Metod for get properties value in Plan
	Vec3f getAmbient() const { return mat.ambient;}

	Vec3f getDiffuse() const {return mat.diffuse;}

	Vec3f getSpecular() const {	return mat.specular;}

	float getShininess() const {return mat.shininess;}
	

};

#endif


