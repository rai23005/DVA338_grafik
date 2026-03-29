#include "configvalue.h"


//Camera start value
vec3 cameraStartPositioned = { 0,0,20 };
vec3 cameraStartRotation = { 0.0f, 0.0f, 0.0f };
vec3 cameraStartViewDirection = { 0.0f, 0.0f, -1.0f };
vec3 cameraStartUpVector = { 0.0f, 1.0f, 0.0f };


//For, OrthogonalProjectionMatrix
float left = -20.0f;
float right = 20.0f;
float top = 10.0f;
float bottom = -10.0f;
float config_near = 1.0f;
float config_far = 1000.0f;


//Value for the model 
vec3 cowPositioned = { 0.0f, 1.5f, -8.0f };
vec3 cowRotation = { 0.0f, -90.0f, 0.0f };
vec3 cowScale = { 1.0f, 1.0f, 1.0f };
 
vec3 teapotPositioned ={ 0.0f, -7.0f, 0.0f };
vec3 teapotRotation = {-90.0f, 0.0f, 180.0f};
vec3 teapotScale = { 1.0f, 1.0f, 1.0f };

vec3 triceratopsPositioned ={ -6.8f, 0.8f, 5.0f };
vec3 triceratopsRotation= { 0.0f, 0.0f, 0.0f };
vec3 triceratopsScale= { 0.1f, 0.1f, 0.1f };


//Asigment 1.7 
//

mat4 BuildModelLocalToWorld(vec3 translation, vec3 rotationInDegrees, vec3 Vectorscale) {

    vec3 rotationInRadius = radians(rotationInDegrees);

    //Scale 
    mat4 S = scale(mat4(1.0f), Vectorscale);

    // Rotate 
    mat4 Rx = rotate(mat4(1.0f), rotationInRadius.x, vec3(1, 0, 0));
    mat4 Ry = rotate(mat4(1.0f), rotationInRadius.y, vec3(0, 1, 0));
    mat4 Rz = rotate(mat4(1.0f), rotationInRadius.z, vec3(0, 0, 1));

    // Translation
    mat4 T = translate(mat4(1.0f), translation);

    // W= T(t)Rx(rx)Ry(ry)Rz(rz)S(s)
    mat4 W = T * Rx*Ry*Rz* S;

    return W;
}