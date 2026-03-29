#include "RayTracer.h"
#include <iostream>

void RayTracer::searchClosestHit(const Ray& ray, HitRec& hitRec) {
	hitRec.anyHit = false;
	hitRec.tHit = Ray::tMax;

	//Look through all the object 
	for (int i = 0; i < this->scene->objects.size(); i++) {
		HitRec tempRec;
		tempRec.tHit = Ray::tMax;

		//Check if the ray hits the current object 
		if (this->scene->objects[i]->hit(ray, tempRec)) {


			//If the ray hits objeckt closer than the previous closet hit 
			if (tempRec.tHit < hitRec.tHit) {
				
				//Uppdate the closet hit 
				hitRec = tempRec;
				hitRec.anyHit = true;
				hitRec.hitObject = this->scene->objects[i];
			}
		}
	}
}

Vec3f RayTracer::getEyeRayDirection(int x, int y) {
	//Uses a fix camera looking along the negative z-axis
	//Bigger negativ = more in zoom 
	static float z = -5.0f;
	static float sizeX = 4.0f;
	static float sizeY = 3.0f;

	//Move camera to left/ right 
	static float left = -sizeX * 0.5f;
	static float top = sizeY * 0.5f;


	static float dx = sizeX / float(this->image->getWidth());
	static float dy = sizeY / float(this->image->getHeight());


	float px = left + x * dx;
	float py = top - y * dy;

	// No rotation
	float rotatedX = px;
	float rotatedY = py;

	// 180-degree rotation around Z axis:
	//float rotatedX = -px;
	//float rotatedY = -py;

	// 90-degree roation counter-clockwise 
	//float rotatedX = -py;
	//float rotatedY = px;

	// 90-degree roation clockwise 
	//float rotatedX = py;
	//float rotatedY = -px;

	return Vec3f(rotatedX, rotatedY, z).normalize();
}


// Is the pixel in the shadow 
bool RayTracer::isInShadow(const Vec3f& point, const Light& light) {
	// Move the start point for the ray for prevent shadow acne
	Vec3f offset = (light.position - point).getNormalized() * 0.001f;
	Vec3f shadowOrigin = point + offset;

	//Direction from point to the light 
	Vec3f dirToLight = (light.position - point).getNormalized();

	//Create a shadowray pointing to the light
	Ray shadowRay(shadowOrigin, dirToLight);

	//Hit record 
	HitRec shadowHit;
	shadowHit.tHit = Ray::tMax;

	//check for all objects if any blocks the lights
	for (Object* obj : this->scene->objects) {
		if (obj->hit(shadowRay, shadowHit)) {
				
				return true; 
			
		}
	}
	return false;
}


//Function that calculate Lighting/color for the pixel 
Vec3f RayTracer::calculateLighting(const Vec3f& hitPoint, const Vec3f& normal, const Vec3f& viewDir, const HitRec& hitRec) {
	
	//A defult color (black) 
	Vec3f color = Vec3f(0.0f, 0.0f, 0.0f);

	//for each light 
	for (const Light& light : this->scene->lights) {

		//Our L, where is lightsource direction from the hitpoint, 
		Vec3f lightDir = (light.position - hitPoint).getNormalized();

		// Ambient lighting (𝐼𝑎𝑚𝑏𝑖𝑒𝑛𝑡 = 𝐼𝑎𝑘𝑎) • 𝑘𝑎 = (𝑘𝑎𝑟 , 𝑘𝑎𝑔, 𝑘𝑎𝑏) • 𝐼𝑎 = (𝐼𝑎𝑟 , 𝐼𝑎𝑔, 𝐼𝑎𝑏 )
		Vec3f I_ambient = hitRec.hitObject->getAmbient().multCoordwise(light.color);


		// Always add I_ambient, to the color 
		color = I_ambient;

		//If the hit point is in a shadow compare to the light 
		if (!isInShadow(hitPoint, light)) {

			// Diffuse lighting (𝐼𝑑𝑖𝑓𝑓𝑢𝑠𝑒 = 𝐼𝑑𝑘𝑑 cos 𝜃 = 𝐼𝑑𝑘𝑑 (𝑁. 𝐿) ) 
			//Calucate N.L
			float NdotL = normal.dot(lightDir);

			// Only consider light coming from the front
			if (NdotL < 0.0f) NdotL = 0.0f;

			Vec3f I_diffuse = hitRec.hitObject->getDiffuse().multCoordwise(light.color) * NdotL;

			// Specular lighting 𝐼𝑠𝑝𝑒𝑐𝑢𝑙𝑎𝑟 = 𝐼𝑠𝑘𝑠 cos 𝜑 = 𝐼𝑠𝑘𝑠(𝑅. 𝑉)^𝛼 
			//Reflections direction on the surface, vector R. R=2(N.L)N-L
			Vec3f reflectDir = (normal * (2 * NdotL) - lightDir).getNormalized();

			// Get shinnes of the object 
			float shininess = hitRec.hitObject->getShininess();

			//Caluate (𝑅. 𝑉)^shininess

			float RV = std::pow(std::max(reflectDir.dot(viewDir), 0.0f), shininess);
			//float RV = std::pow(reflectDir.dot(viewDir), shininess);
			if (RV < 0.0f) RV = 0.0f; // Only consider light coming from the front

			Vec3f I_specular = hitRec.hitObject->getSpecular().multCoordwise(light.color) * RV;


			//Phong Reflection Model
			// Add diffuse and specular contributions to the final color
			//color += I_diffuse + I_specular;
			color += I_specular;
		}


		//color value between 0-1  		
		color.x = std::min(1.0f, std::max(0.0f, color.x));
		color.y = std::min(1.0f, std::max(0.0f, color.y));
		color.z = std::min(1.0f, std::max(0.0f, color.z));

	}

	return color;
}



void RayTracer::fireRays() {

	Ray ray;

	//Loop through ever pixel in the image
	for (int x = 0; x < this->image->getWidth(); x++) {
		for (int y = 0; y < this->image->getHeight(); y++) {

			//Get the ray direction to the eye
			ray.d = RayTracer::getEyeRayDirection(x, y);

			//Search for the closet object
			RayTracer::searchClosestHit(ray, ray.hitRec);

			// Add so it check if it hit anything 
			if (ray.hitRec.anyHit && ray.hitRec.hitObject != nullptr) {


				//Where is the hitpoint p
				Vec3f hitPoint = ray.o + ray.d * ray.hitRec.tHit;

				//Calculate a normal at the hitpoint of p our N
				Vec3f normal = ray.hitRec.hitObject->getNormal(hitPoint).getNormalized();

				//Direction from the eya, normaliz 
				Vec3f viewDir = (ray.o - hitPoint).getNormalized();
 
				Vec3f finalcolor = calculateLighting(hitPoint, normal, viewDir, ray.hitRec);

				//Set the final pixel color 
				this->image->setPixel(x, y, finalcolor);
			}
			else {
				//No hit for the raytracer, set bgColor
				this->image->setPixel(x, y, this->bgColor);
			}
		}
	}


}