#ifndef _RayTracer_H_
#define _RayTracer_H_

#include "Scene.h"
#include "Image.h"
#include "Ray.h"
#include "Sphere.h"
#include "Plan.h"

class RayTracer {
private: 
	Scene * scene;
	Image * image;
    Vec3f bgColor;

    std::vector<Light> lights;
    std::vector<Object*> objects;

public:
    RayTracer(const int w, const int h) {
        this->scene = new Scene();
        this->image = new Image(w, h);

        // Backgrounds color for the image 
        this->bgColor = Vec3f(0.8f, 0.8f, 0.8f);
    }
    ~RayTracer() {
        delete scene;
        delete image;
    }
    void searchClosestHit(const Ray & ray, HitRec & hitRec);
	Vec3f getEyeRayDirection(int x, int y);
    void fireRays();
    void toPPM(const char* path) {
        this->image->toPPM(path);
    };
    void toBMP(const char* path) {
        this->image->toBMP(path);
    };
    void addSphere(const Vec3f& c, const float r, const Material& mat) {
        this->scene->addSphere(c, r, mat);
    };

    //So you can add a plane
    void addPlane(const Vec3f& point, const Vec3f& normal, const Material& mat) {
        this->scene->addPlane(point, normal, mat);
    }

    //So you can add a triangel
    void addTriangle(const Vec3f& v0, const Vec3f& v1, const Vec3f& v2, const Material& mat) {
        this->scene->addTriangle(v0, v1, v2, mat);
    }


    // Fuction for Randomly Perturb Normals
    Vec3f getRandomPerturbNorml() const;

    //So you can add lights sours 
    void RayTracer::addLight(const Light& light) {
        this->scene->addLight(light);
    }

      //Pixel in the Shadow  
    bool isInShadow(const Vec3f& point, const Light& light);

    //For softshadow 
    float softShadow(const Vec3f& hitPoint, const Light& light);    

    // Caluate the light 
    Vec3f calculateLighting(const Vec3f& hitPoint, const Vec3f& normal, const Vec3f& viewDir, const HitRec& hitRec, int depth);

    //For calulacte the reflections
    Vec3f caluateReflections(const Ray& ray, int depth);


    //For multi threat 
    void processRows(int startRow, int endRow, int width);


};

#endif