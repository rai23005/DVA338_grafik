
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Vec3.h"
#include "Ray.h"
#include "Object.h"

class Triangle : public Object {

public: 

	//The three corner
	Vec3f vertexA, vertexB, vertexC;


	Vec3f edge1, edge2, edge3;

	Vec3f normal;

	// Material for the trainagel 
	Material mat;
	



		//construktor for the trinagel 
	
	Triangle(const Vec3f& vertexA, const Vec3f& vertexB, const Vec3f& vertexC, const Material& material)
		: vertexA(vertexA), vertexB(vertexB), vertexC(vertexC), mat(material) {
	
		edge1 = vertexB - vertexA;
		edge2 = vertexC - vertexA; 
		edge3 = vertexC - vertexB;
		normal = edge1.cross(edge2).getNormalized();
	}




public:

	// Compute surface fields like normal
	void computeSurfaceHitFields(const Ray& r, HitRec& rec) const;

	// Check if the ray intersects with the triangel
	bool hit(const Ray& r, HitRec& rec) const;

	//Get the triangel normal
	Vec3f getNormal(const Vec3f& ) const override {
		return normal;
	}

	//metod to get color of the plan 
	Vec3f getColor() const {
		return mat.color;
	}


	//Metod for get properties value in Plan
	Vec3f getAmbient() const { return mat.ambient; }
	Vec3f getDiffuse() const { return mat.diffuse; }
	Vec3f getSpecular() const { return mat.specular; }
	float getShininess() const { return mat.shininess; }
	float getReflective()const { return mat.reflectiveness; }





};

#endif