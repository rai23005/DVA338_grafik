////Lab2 

#include "configvalue.h"

//Camera start value
Vector cameraPositioned = { 0,0,20 };
Vector cameraRotation = { 0.0f, 0.0f, 0.0f };

//Camra assigment 3.2 
//Vector cameraPositioned = { 5,7,20 };
//Vector cameraRotation = { -13.0f, 13.0f, 0.0f };

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

//Value for the material for the diffrent model 
Material cowMaterial = {
   { 0.329412f, 0.223529f, 0.027451f},// Ambient  
{ 0.780392f, 0.568627f, 0.113725f },  // Diffuse
{ 0.992157f, 0.941176f, 0.807843f }, // Specular
27.9f  // Shininess;
}; 


Vector teapotPositioned = { 0.0f, -7.0f, 0.0f };
Vector teapotRotation = { -90.0f, 0.0f, 180.0f };
Vector teapotScale = { 1.0f, 1.0f, 1.0f };

Material teapotMaterial = {
    {0.19225f, 0.19225f, 0.19225f},
    {0.50754f, 0.50754f, 0.50754f},
    {0.508273f, 0.508273f, 0.508273f},
    51.2f 
};


Vector triceratopsPositioned = { -6.8f, 0.8f, 5.0f };
Vector triceratopsRotation = { 0.0f, 0.0f, 0.0f };
Vector triceratopsScale = { 0.1f, 0.1f, 0.1f };

Material triceratopsMaterial = {
    {0.05f, 0.0f, 0.0f},
    {0.6f, 0.4f, 0.4f},
    {0.7f, 0.04f, 0.04f},
    10.0f
};



//Asigmnet 3.2

Vector knotPositioned = { 0.0f, 4.0f, 0.0f };
Vector knotRotation = { 0.0f, 0.0f, 0.0f };
Vector knotScale = { 0.4f, 0.4f, 0.4f };

Vector cubePositioned = { -10.0f, -1.0f, -10.0f };
Vector cubeRotation = { 0.0f, 0.0f, 0.0f };
Vector cubeScale = { 4.0f, 0.1f, 4.0f };

//The light 
Light sceneLight = {
    {-20.0f, 10.0f, 10.0f},
    {0.2f, 0.2f, 0.2f},
    {0.9f, 0.9f, 0.7f},
    {1.0f, 1.0f, 1.0f}
};


