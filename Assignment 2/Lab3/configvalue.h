//Global value to config, so easy to find them in   

#ifndef _CONFIGVALUE_H_
#define _CONFIGVALUE_H_

#define _USE_MATH_DEFINES // To get M_PI defined


#include "algebra.h"
#include "mesh.h"
#include "lab3_utils.h"

#define MAX_OBJECTS 100
#define MAX_LIGHTS 100




#define LAB_EXTRA 1

#define LAB_THREE 0

extern Vector cameraPositioned;
extern Vector cameraRotation;

extern Vector cameraPositioned2;

extern Vector firstpersoncameraPositioned;
extern Vector firstpersoncameraRotation;
extern Vector thirdPersonViewPositioned;
extern Vector thirdPersonViewRotation;





extern float left;
extern float right;
extern float top;
extern float bottom;
extern float config_near;
extern float config_far;




enum LightType {
    LIGHT_TYPE_BACKGROUND,
    LIGHT_TYPE_HEADLIGHT,
    LIGHT_TYPE_LAMP,
    

};

struct Light {
    Vector position;
    Vector ambient;
    Vector diffuse;
    Vector specular;

    //For the spotligt 
    int isSpotLight;

    Vector direction;
    
    float constant;
    float linear;
    float quadratic;  

    
    float innerCutoff;
    float outerCutoff;

    //LightType type;
    int type;
    bool enabled;

    //Animation for the light  
    Vector basePosition;
    Vector translationPerFrame;
   
    int offsetFrame;
    int animationMaxLengthFrame;
    

};



extern Light lab3Light[MAX_LIGHTS];

extern Vector leftLamplightPosition;
extern Vector rightLamplightPosition;
extern Vector lampLightDirection;

extern float innerCutoff;
extern float outerCutoff;
extern float innerCutoffCardilac;
extern float outerCutoffCardilac;



//LAB3


typedef struct ObjNode {
    
    //Model 
    struct obj* model;
    

    //Diffrent value 
    const char* modelname;
    int id;
    Vector translation;
    Vector rotation;
    Vector scale;

    //For amationen
    Vector translationPerFrame;
    Vector rotationPerFrame;
    Vector scalePerFrame;

    int offsetFrame;
    int animationMaxLengthFrame;


} ObjNode;



extern int objectCount;
extern ObjNode objectArray[MAX_OBJECTS];

extern const char* pathCadillac;
extern const char* pathLamp;
extern const char* pathRoad;
extern const char* pathSkybox;
extern const char* pathDesert;




extern Vector zeroVector;
extern Vector cardillacTranslate;
extern Vector cardillacRotation;
extern Vector cardillacScale;

extern Vector cardillacHeadlightLeftPosition;


extern Vector cardillacHeadlightRigtPosition;

extern Vector cardillacHeadlightDirection;

extern Vector cardillac2000Scale;

extern Vector cardliacAmbient;
extern Vector cardliacDiffuse;
extern Vector cardliacSpecular;
extern float cardliacLinear;
extern float cardliacQuadratic;





extern Vector skyBoxTranslate;
extern Vector skyBoxRotation;
extern Vector skyBoxScale;

extern Vector roadTranslate;
extern Vector roadRotation;
extern Vector roadScale;



extern Vector lampTranslate;
extern Vector lampRotation;
extern Vector lampScale;

extern Vector lampLeftTranslate;
extern Vector lampLefttRotation;
extern Vector lampLefttScale;

extern Vector lampRightTranslate;
extern Vector lampRightRotation;
extern Vector lampRightScale;

extern Vector lampAmbient;
extern Vector lampDiffuse;
extern Vector lampSpecular;
extern float lampLinear;
extern float lampQuadratic;


extern Vector desertTranslate;
extern Vector desertRotation;
extern Vector desertScale;



extern Vector moveinZAxeln;
extern Vector rotationOneGradePerFrameYaxel;

extern float startZvalue;

extern int animationMaxLengthFrame;
extern int currentFrame;
extern const int maxFrame;


#endif


