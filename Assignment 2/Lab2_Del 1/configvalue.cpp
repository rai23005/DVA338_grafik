#include "configvalue.h"

//Camera start value
Vector cameraPositioned = { 0,0,20 };
Vector cameraRotation = { 0.0f, 0.0f, 0.0f };



//For, OrthogonalProjectionMatrix
float left = -20.0f;
float right = 20.0f;
float top = 10.0f;
float bottom = -10.0f;
float config_near = 1.0f;
float config_far = 1000.0f;


//Value for the model 
Vector cowPositioned = { 0.0f, 1.5f, -8.0f };
 Vector cowRotation = { 0.0f, -90.0f, 0.0f };
 Vector cowScale = { 1.0f, 1.0f, 1.0f };
 
 Vector teapotPositioned ={ 0.0f, -7.0f, 0.0f };
 Vector teapotRotation = {-90.0f, 0.0f, 180.0f};
 Vector teapotScale = { 1.0f, 1.0f, 1.0f };

 Vector triceratopsPositioned ={ -6.8f, 0.8f, 5.0f };
 Vector triceratopsRotation= { 0.0f, 0.0f, 0.0f };
 Vector triceratopsScale= { 0.1f, 0.1f, 0.1f };
