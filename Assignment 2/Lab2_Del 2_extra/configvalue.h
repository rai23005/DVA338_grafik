//Global value to config, so easy to find them in   

#ifndef _CONFIGVALUE_H_
#define _CONFIGVALUE_H_

#include "algebra.h"
#include "mesh.h"


extern Vector cameraPositioned;
extern Vector cameraRotation;



extern float left;
extern float right;
extern float top;
extern float bottom;
extern float config_near;
extern float config_far;

extern Vector cowPositioned;
extern Vector cowRotation;
extern Vector cowScale;

extern Material cowMaterial;

extern Vector teapotPositioned;
extern Vector teapotRotation;
extern Vector teapotScale;

extern Material teapotMaterial;

extern Vector triceratopsPositioned;
extern Vector triceratopsRotation;
extern Vector triceratopsScale;

extern Material triceratopsMaterial;

extern Vector knotPositioned;
extern Vector knotRotation;
extern Vector knotScale;

extern Vector cubePositioned;
extern Vector cubeRotation;
extern Vector cubeScale;

struct Light {
    Vector position;
    Vector ambient;
    Vector diffuse;
    Vector specular;
};


extern Light sceneLight;

extern Light sceneExtraLights[];

extern int max_Light;


#endif


