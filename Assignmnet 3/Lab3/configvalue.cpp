//Change here to get the defult value 

#include "configvalue.h"


//Camera lab3
Vector cameraPositioned = { 0,5,3 };
Vector cameraRotation = { -30.0f, 0.0f, 0.0f };

Vector firstpersoncameraPositioned = { -0.4,0.3,-5 };
Vector firstpersoncameraRotation = { 0.0f, 0.0f, 0.0f };


Vector thirdPersonViewPositioned= { -5,0,0 };
Vector thirdPersonViewRotation = { 0.0f, -45.0f, 0.0f };

//Part 1 multi cadilac 
Vector cameraPositioned2 = { 0,0,5 };


//For the camera 
//For, OrthogonalProjectionMatrix
float left = -20.0f;
float right = 20.0f;
float top = 10.0f;
float bottom = -10.0f;
float config_near = 1.0f;
float config_far = 1000.0f;


Vector position;
Vector ambient;
Vector diffuse;
Vector specular;

//For the spotligt 
int isSpotLight;

vec3 direction;

float constant;
float linear;
float quadratic;

float cutoff;


const char* name;


//How many object that is 
int objectCount = 0;
ObjNode objectArray[MAX_OBJECTS];


//Array with all light value
//Lights array 
Light lab3Light[] = {
    
    //Background light 
    {
        { 0.0f, 0.0f, 0.0f },   // position
        { 0.2f, 0.2f, 0.2f },       // ambient
        { 1.0f, 1.0f, 1.0f }, // diffuse
        { 0.2f,0.2f,0.2f }, // specular
    0,                           // isSpotLight = false
    { 0.0f, 0.0f, 0.0f },        // direction
    1.0f,                        // constant
    0.0f,                        // linear 
    0.0f,                        // quadratic
    0.0f,                        // innerCutoff
    0.0f,                        // outerCutoff
    LIGHT_TYPE_BACKGROUND,         //
    true,                       // enabled
    zeroVector,                 // basePosition
    zeroVector,                 // translationPerFrame
    0.0f,                       // offsetFrame
    animationMaxLengthFrame     // animationMaxLengthFrame

    },



    //Lamp 1 row, farrest away 
        {
        { 3.0, 2.0f, -202.0f },
        lampAmbient,
        lampDiffuse,
        lampSpecular,
        1,
        lampLightDirection,
        1.0f,
        lampLinear,
        lampQuadratic,
        innerCutoff,
        outerCutoff,
        LIGHT_TYPE_LAMP,
        true,
        { 3.0, 2.0f, -202.0f },
        moveinZAxeln,
         0.0f,
        animationMaxLengthFrame
         },

          {
        { -3.0, 2.0f, -202.0f },
        lampAmbient,
        lampDiffuse,
        lampSpecular,
        1,
        lampLightDirection,
        1.0f,
        lampLinear,
        lampQuadratic,
        innerCutoff,
        outerCutoff,
        LIGHT_TYPE_LAMP,
        true,
        { -3.0, 2.0f, -202.0f },
        moveinZAxeln,
         0.0f,
        animationMaxLengthFrame
        },


    //row 2
          {
          { 3.0, 2.0f, -102.0f },
          lampAmbient,
          lampDiffuse,
          lampSpecular,
          1,
          lampLightDirection,
          1.0f,
          lampLinear,
          lampQuadratic,
          innerCutoff,
          outerCutoff,
          LIGHT_TYPE_LAMP,

          true,
          { 3.0, 2.0f, -102.0f },
          moveinZAxeln,
           0.0f,
          animationMaxLengthFrame
          },
            {
          { -3.0, 2.0f, -102.0f },
          lampAmbient,
          lampDiffuse,
          lampSpecular,
          1,
          lampLightDirection,
          1.0f,
          lampLinear,
          lampQuadratic,
          innerCutoff,
          outerCutoff,
          LIGHT_TYPE_LAMP,
          true,
           { -3.0, 2.0f, -102.0f },
          moveinZAxeln,
           0.0f,
          animationMaxLengthFrame
            },
   // Lampa row 3
            {
            { 3.0, 2.0f, -2.0f },
            lampAmbient,
            lampDiffuse,
            lampSpecular,
            1,
            lampLightDirection,
            1.0f,
            lampLinear,
            lampQuadratic,
            innerCutoff,
            outerCutoff,
            LIGHT_TYPE_LAMP,
            true,
            { 3.0, 2.0f, -2.0f },
            moveinZAxeln,
             0.0f,
            animationMaxLengthFrame
            },

              {
            { -3.0, 2.0f, -2.0f },
            lampAmbient,
            lampDiffuse,
            lampSpecular,
            1,
            lampLightDirection,
            1.0f,
            lampLinear,
            lampQuadratic,
            innerCutoff,
            outerCutoff,
            LIGHT_TYPE_LAMP,
            true,
             { -3.0, 2.0f, -2.0f },
            moveinZAxeln,
             0.0f,
            animationMaxLengthFrame
              },

    ////Cardilacs headlight 
                  {
       cardillacHeadlightLeftPosition,   //  left headlight 
       cardliacAmbient,
       cardliacDiffuse,
       cardliacSpecular,
        1,
        cardillacHeadlightDirection,
        1.0f,
        cardliacLinear,
        cardliacQuadratic,
        innerCutoffCardilac,
        outerCutoffCardilac,
        LIGHT_TYPE_HEADLIGHT,
        true,
        cardillacHeadlightLeftPosition,
                zeroVector,
        0.0f,
        animationMaxLengthFrame

                  },



    {
        cardillacHeadlightRigtPosition,    // right headlight
        cardliacAmbient,
        cardliacDiffuse,
        cardliacSpecular,
        1,
        cardillacHeadlightDirection,
        1.0f,
        cardliacLinear,
       cardliacQuadratic,
        innerCutoffCardilac,
        outerCutoffCardilac,
        LIGHT_TYPE_HEADLIGHT,
        true,
        cardillacHeadlightRigtPosition,
         zeroVector,
         0.0f,
        animationMaxLengthFrame
    }


};




//Model path
const char* pathCadillac = "C:\\Users\\Rasmus\\OneDrive - Mälardalens universitet\\DVA338 - Grafik\\Assignment 2\\DevOgl\\DVA338_Lab1\\Assets\\Cadillac\\cadillac.obj";
const char* pathLamp= "C:\\Users\\Rasmus\\OneDrive - Mälardalens universitet\\DVA338 - Grafik\\Assignment 2\\DevOgl\\DVA338_Lab1\\Assets\\RoadSkybox\\lamp.obj";
const char* pathRoad="C:\\Users\\Rasmus\\OneDrive - Mälardalens universitet\\DVA338 - Grafik\\Assignment 2\\DevOgl\\DVA338_Lab1\\Assets\\RoadSkybox\\road.obj";
const char* pathSkybox = "C:\\Users\\Rasmus\\OneDrive - Mälardalens universitet\\DVA338 - Grafik\\Assignment 2\\DevOgl\\DVA338_Lab1\\Assets\\RoadSkybox\\cubemap.obj";
const char* pathDesert = "C:\\Users\\Rasmus\\OneDrive - Mälardalens universitet\\DVA338 - Grafik\\Assignment 2\\DevOgl\\DVA338_Lab1\\Assets\\RoadSkybox\\desert.obj";



//Model diffrent value
Vector cardillacTranslate = { 0.0f, -1.0f, -5.0f };
Vector cardillacRotation = { -90.0f,0.0f, 0.0f };
Vector cardillacScale = { 1.0f, 1.0f, 1.0f };





//Lamps value 
Vector leftLamplightPosition = { 3.0, 3.0f, 0.0f };
Vector rightLamplightPosition = { -3.0, 3.0f, 0.0f };


Vector lampLightDirection = { 0.0f, -1.0f, 0.0f };


Vector lampScale = { 1.0f, 1.0f, 1.0f };

Vector lampLeftTranslate = { 25.0f, 1.0f, -1.0f };
Vector lampLefttRotation = { 0.0f, 180.0f, 0.0f };


Vector lampRightTranslate = { -1.0f, 1.0f, 7.0f };
Vector lampRightRotation = { 0.0f, 0.0f, 0.0f };



// A zero vecktor 
Vector zeroVector = { 0.0f ,0.0f ,0.0f };

//The rest of the model
Vector skyBoxTranslate = { 0.0, 0.0f, 0.0f };
Vector skyBoxRotation = { 0.0, 0.0f, 0.0f };
Vector skyBoxScale = { 1000.0, 1000.0f, 1000.0f };


Vector roadRotation = { 0.0f, 0.0f, 0.0f };
Vector roadScale = { 1.0f, 1.0f, 1.0f };


 

Vector desertRotation = { 0.0f, 0.0f, 0.0f };
Vector desertScale = { 2.5f, 2.5f, 2.5f };

//start value for postion 
float startZvalue= -200.0f; 


//Light value 

//Cardilac value
Vector cardillac2000Scale = { 0.3f, 0.3f, 0.3f };

//CArdilacs headlight value 
Vector cardillacHeadlightLeftPosition = { -2.0f, 1.0f, -12.0f};
Vector cardillacHeadlightRigtPosition = { 2.0f, 1.0f, -12.0f};

Vector cardillacHeadlightDirection = { 0.0f, 0.0f, -1.0f };


Vector cardliacAmbient = { 0.3f, 0.3f, 0.3f };
Vector cardliacDiffuse = { 1.0f, 1.0f, 1.0f };
Vector cardliacSpecular = { 1.0f, 1.0f, 1.0f };
float cardliacLinear = 0.09f;
float cardliacQuadratic = 0.0032f;


float innerCutoffCardilac = 0.85; //std::cos(2.5f * M_PI / 180.0f);
float outerCutoffCardilac = 0.70;// std::cos(4.0f * M_PI / 180.0f);





//Lamp post 
Vector lampAmbient = { 0.3f, 0.3f, 0.3f };
Vector lampDiffuse = { 1.0f, 1.0f, 1.0f };
Vector lampSpecular = { 1.0f, 1.0f, 1.0f };
float lampLinear = 0.09f;
float lampQuadratic = 0.0032f;


//Light post 
float innerCutoff = 0.7; 
float outerCutoff = 0.6; 


//Animations 
Vector moveinZAxeln = { 0.0f ,0.0f ,0.5f };
//Vector moveinZAxeln = { 0.0f ,0.0f ,0.0f };
Vector rotationOneGradePerFrameYaxel = { 0.0f ,1.0f ,0.0f };


int labPart1animationMaxLengthFrame = 20000;
int animationMaxLengthFrame = 200;
int currentFrame = 0;
const int maxFrame = 100000;
        

 
