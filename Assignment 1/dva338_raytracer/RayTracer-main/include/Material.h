#ifndef _MATERIAL_H_
#define _MATERIAL_H_


//To use vector 
#include "Vec3.h" 
#include <iostream>

class Material {
public:

	//Color of the material
	Vec3f color;


	Vec3f ambient;    // Ambient component
	Vec3f diffuse;    // Diffuse component
	Vec3f specular;   // Specular component
	float shininess;   // Shininess exponent  
	float reflectiveness;  //How Reflective a material is

	// Default constructor
	Material()
		: color(Vec3f(0.0f, 0.0f, 0.0f)),
		ambient(Vec3f(0.0f, 0.0f, 0.0f)),
		diffuse(Vec3f(0.0f, 0.0f, 0.0f)),
		specular(Vec3f(0.0f, 0.0f, 0.0f)),
		shininess(0.0f),
		reflectiveness(0.0f) {}

	// Constructor with full material properties
	Material(const Vec3f& ambient,
		const Vec3f& diffuse,
		const Vec3f& specular,
		float shininess,
		float reflectiveness)
		: ambient(ambient), 
		diffuse(diffuse), 
		specular(specular),
		shininess(shininess),
		reflectiveness(reflectiveness),
		color(diffuse) {
	}

	Material(const Vec3f& amb, const Vec3f& diff, const Vec3f& spec, float shininessVal)
		: ambient(amb), diffuse(diff), specular(spec),
		shininess(shininessVal)
	{
		reflectiveness = std::min(shininess / 10000.0f, 1.0f);
	}




	//Metod to get the diffrent value 
	Vec3f getAmbient() const { return ambient; }
	Vec3f getDiffuse() const { return diffuse; }
	Vec3f getSpecular() const { return specular; }
	float getShininess() const { return shininess; }


};

#endif