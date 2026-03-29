//Global value to config, so easy to find them in   

#ifndef _CONFIGVALUE_H_
#define _CONFIGVALUE_H_



#include "glm.hpp"
#include "matrix_transform.hpp"

using glm::vec3;
using glm::mat4;
using glm::radians;
using glm::translate;
using glm::rotate;
using glm::scale;


//Extra asigment 

extern vec3 cameraStartPositioned;
extern vec3 cameraStartRotation;
extern vec3 cameraStartViewDirection;
extern vec3 cameraStartUpVector;



extern float left;
extern float right;
extern float top;
extern float bottom;
extern float config_near;
extern float config_far;

extern vec3 cowPositioned;
extern vec3 cowRotation;
extern vec3 cowScale;

extern vec3 teapotPositioned;
extern vec3 teapotRotation;
extern vec3 teapotScale;

extern vec3 triceratopsPositioned;
extern vec3 triceratopsRotation;
extern vec3 triceratopsScale;


mat4 BuildModelLocalToWorld(vec3 translation, vec3 rotationInDegrees, vec3 Vectorscale);

#endif