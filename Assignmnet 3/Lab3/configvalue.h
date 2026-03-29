//Global value to config, so easy to find them in   

#ifndef _CONFIGVALUE_H_
#define _CONFIGVALUE_H_

#define _USE_MATH_DEFINES // To get M_PI defined


#include "algebra.h"
#include "lab3_utils.h"
#include <math.h>

#define MAX_OBJECTS 2500
#define MAX_LIGHTS 100



//PArt 1 in lab 3, 200 cardilac  
// LAB_THREE 0
//  Camera, key press "4"

//Part 2
//LAB_THREE 1 

#define LAB_THREE 1


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


//Light have diffrent type 

enum LightType {
    LIGHT_TYPE_BACKGROUND,
    LIGHT_TYPE_HEADLIGHT,
    LIGHT_TYPE_LAMP,
    

};

//Lamps struct 

struct Light {
    Vector position;  //Postion
    Vector ambient;   //Ambient light 
    Vector diffuse;     //Diffuse light
    Vector specular;   // Specular light

    //For the spotligt 
    int isSpotLight;      //Is that a spotlight, 0 -> No 1 -> yes

    Vector direction;    //Witch direction have the light 
    
    float constant;     // prevents div with zero.
    float linear;        //controls falloff at short distance
    float quadratic;  // controls falloff at long distance

    
    float innerCutoff; // spotligt is brithigts 
    float outerCutoff;  // when the lights cut off from the spotlight

    //LightType type;
    int type;    //with type of light 
    bool enabled;  //Is the light on or off 

    //Animation for the light  
    Vector basePosition;       //where the light start 
    Vector translationPerFrame;  //how fast it move 
   
    int offsetFrame;      //if that shall start later or not (did not use it)
    int animationMaxLengthFrame;   //how many frame befor reset the animation 
    

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

//Struct with all the objekt/models 
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

extern int labPart1animationMaxLengthFrame;
extern int animationMaxLengthFrame;
extern int currentFrame;
extern const int maxFrame;


#endif


