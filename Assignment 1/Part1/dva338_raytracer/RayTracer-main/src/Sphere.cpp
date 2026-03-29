
#include "Sphere.h"
#include <utility>


bool Sphere::hit(const Ray & r, HitRec & rec) const {	
	

	//Vector from sphere centrum to ray 
	Vec3f oc = r.o - c;

	// a = dot product of the ray direction with itself
	float a = r.d.dot(r.d);

	// Can not divide with 0 
	if (a == 0) {
		return false;
	}

	// b = 2 * dot product of oc and ray direction
	float b = 2.0f * oc.dot(r.d);

	// c = oc.oc - r^2
	float c_ = oc.dot(oc) - this->r * this->r;

	//used to check if the ray hit the sphere
	float rayhitSphere = b * b - 4 * a * c_;

	//If rayhitSpeher is less then 0 do it not hit the spehere
		if (rayhitSphere < 0) {
			return false;
		}

		// Calculate the two intersection points
		float squarOfrayhitSphere = sqrt(rayhitSphere);
		float t1 = (-b - squarOfrayhitSphere) / (2.0f * a);
		float t2 = (-b + squarOfrayhitSphere) / (2.0f * a);

		//start value of t
		float t = -1.0f;

		//Get that valu that is lowest poestiv value
		if (t1 > 0 && t2 > 0) {
			t = std::min(t1, t2);}
		else if (t1 > 0) { t = t1; }
		else if (t2 > 0) { t = t2; }

		// Both intersections are behind the camera
		else { return false; }

	//if t is closer then last hit point, change hitpoint 
		if (t < rec.tHit) {
			rec.tHit = t;
			rec.p = r.o + r.d * t; //hit point
			rec.n = (rec.p - c).normalize(); //Normal
			rec.hitObject = this;
			rec.anyHit = true;
			return true;
		}
		return false;
	}


void Sphere::computeSurfaceHitFields(const Ray & r, HitRec & rec) const {
	rec.p = r.o + r.d * rec.tHit;
	rec.n = (rec.p - c).normalize();
}
