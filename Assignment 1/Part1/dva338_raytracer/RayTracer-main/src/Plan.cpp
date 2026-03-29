#include "Plan.h"
#include <utility>


bool Plan::hit(const Ray& r, HitRec& rec) const {


    //if dot produkt white normal and ray direction close to 0, parallel 
    float alignment = normal.dot(r.d);
    

    // absolute amount of the alignment between ray and plane
    // if the dot produkt i close to 0,  close to parallel (it is parallel) 

    if (std::fabs(alignment) > 0.001) {

       //The lenght from ray to hitpoint  
        float t = (point - r.o).dot(normal) / alignment;
    

       //If the hit i closer then prevoius hit. 
        if (t > 0 && t < rec.tHit) {

           
            rec.tHit = t;  //Lengt to hitpoint
            rec.p = r.o + r.d * t; // Where is the hitpoint
            rec.n = normal;       //normal 
            rec.hitObject = this;  //Save to this plan
            rec.anyHit = true;     

       
            return true;
        }
    }

    return false;
}

void Plan::computeSurfaceHitFields(const Ray& r, HitRec& rec) const {
    rec.n = normal;                
    rec.p = r.o + r.d * rec.tHit;  
   
}