#ifndef _SCENE_H_
#define _SCENE_H_
#include <vector>
using namespace std;

#include "Sphere.h"
#include "Plan.h"
#include "Light.h"

class Scene {
private:

public:
	vector<Object*> objects;
	vector<Light> lights;

	Scene(void) {}
	~Scene() {
		clear();
	}

	//Add color to the sphere 
	void addSphere(const Vec3f & c, const float r, const Material& mat) {
		//Store sphere as an Object pointer
        Sphere* s = new Sphere(c, r, mat);
		objects.push_back(s);
	}

	//Function to add a plane to the image
	void addPlane(const Vec3f& point, const Vec3f& normal, const Material& mat) {
		Plan* p = new Plan(point, normal, mat);
		objects.push_back(p);
	}

	//So It can add a light 
	void addLight(const Light& light) {
			lights.push_back(light);
	}

	void clear()
	{
		// clear objects from memory
		for(vector<Object*>::iterator it = objects.begin(); it != objects.end(); ++it)
			delete *it;
		// Then reset the container
		objects.clear();
	}
	
	int save(char * fileName) {
		// Save your scene to a file somehow ...
		return 0;
	}
	void load(char * fileName) {
		// To avoid memory leaks, we run clear, which deletes any old objects first.
		this->clear();
		// load scene from file here ...
	}

};

#endif