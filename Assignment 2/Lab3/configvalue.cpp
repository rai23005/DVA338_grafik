////Lab2 

#include "configvalue.h"



//Camera lab3
Vector cameraPositioned = { 0,5,17 };
Vector cameraRotation = { -30.0f, 0.0f, 0.0f };

Vector firstpersoncameraPositioned = { -0.4,0.3,7 };
Vector firstpersoncameraRotation = { 0.0f, 0.0f, 0.0f };


Vector thirdPersonViewPositioned= { -5,0,11 };
Vector thirdPersonViewRotation = { 0.0f, -45.0f, 0.0f };


Vector cameraPositioned2 = { 0,0,20 };



//For, OrthogonalProjectionMatrix
float left = -20.0f;
float right = 20.0f;
float top = 10.0f;
float bottom = -10.0f;
float config_near = 1.0f;
float config_far = 1000.0f;


//Extra asigment 


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

int objectCount = 0;
ObjNode objectArray[MAX_OBJECTS];









//Lights array 
Light lab3Light[] = {
    {
        { -20.0f, 50.0f, 0.0f },   // position
        { 0.1f, 0.1f, 0.1f },       // ambient
        { 1.0f, 1.0f, 1.0f }, // diffuse
        { 1.0f,1.0f,1.0f }, // specular
        0,                          // isSpotLight = false
        { 0.0f, 0.0f, 0.0f },       //Direction
        1.0f,                       // constant
        0.0f,                       // linear
        0.0f,                       // quadratic
       0.0f,                         //innerCutoff
       0.0f,                        // outerCutoff
       LIGHT_TYPE_BACKGROUND,           //light type
        true,                           //enabled
        zeroVector,                     //basePosition
        zeroVector,     //translationPerFrame
        0.0f, //offset 
        animationMaxLengthFrame //animationMaxLengthFrame

    },



    //Lamp 1 row
        {
        { 3.0, 2.0f, -200.0f },
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
        { 3.0, 2.0f, -200.0f },
        moveinZAxeln,
         0.0f,
        animationMaxLengthFrame
         },

          {
        { -3.0, 2.0f, -200.0f },
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
        { -3.0, 2.0f, -200.0f },
        moveinZAxeln,
         0.0f,
        animationMaxLengthFrame
        },


    //row 2
          {
          { 3.0, 2.0f, -100.0f },
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
          { 3.0, 2.0f, -100.0f },
          moveinZAxeln,
           0.0f,
          animationMaxLengthFrame
          },
            {
          { -3.0, 2.0f, -100.0f },
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
           { -3.0, 2.0f, -100.0f },
          moveinZAxeln,
           0.0f,
          animationMaxLengthFrame
            },
   // Lampa row 3
            {
            { 3.0, 2.0f, 0.0f },
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
            { 3.0, 2.0f, 0.0f },
            moveinZAxeln,
             0.0f,
            animationMaxLengthFrame
            },

              {
            { -3.0, 2.0f, 0.0f },
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
             { -3.0, 2.0f, 0.0f },
            moveinZAxeln,
             0.0f,
            animationMaxLengthFrame
              },


                  {
       cardillacHeadlightLeftPosition,   //  left headlight 
       cardliacAmbient,
       cardliacDiffuse,
       cardliacSpecular,
        1,
        cardillacHeadlightDirection,
        1.0f,
        0.09f,
        0.032f,
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
        0.09f,
        0.032f,
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
Vector cardillacTranslate = { 0.0f, -1.0f, 7.0f };
Vector cardillacRotation = { -90.0f,0.0f, 0.0f };
Vector cardillacScale = { 1.0f, 1.0f, 1.0f };


//Lamps value
Vector leftLamplightPosition = { 3.0, 3.0f, 0.0f };
Vector rightLamplightPosition = { -3.0, 3.0f, 0.0f };
Vector lampLightDirection = { 0.0f, -1.0f, 0.0f };

Vector lampTranslate = { -1.0f, 1.0f, -1.0f };
Vector lampRotation = { 90.0f, 90, 90.0f };
Vector lampScale = { 1.0f, 1.0f, 1.0f };

Vector lampLeftTranslate = { 25.0f, 1.0f, -1.0f };
Vector lampLefttRotation = { 0.0f, 180.0f, 0.0f };
Vector lampLefttScale = { 1.0f, 1.0f, 1.0f };

Vector lampRightTranslate = { -1.0f, 1.0f, 7.0f };
Vector lampRightRotation = { 0.0f, 0.0f, 0.0f };
Vector lampRightScale = { 1.0f, 1.0f, 1.0f };



Vector zeroVector = { 0.0f ,0.0f ,0.0f };

//The rest of the model
Vector skyBoxTranslate = { 0.0, 0.0f, 0.0f };
Vector skyBoxRotation = { 0.0, 0.0f, 0.0f };
Vector skyBoxScale = { 1000.0, 1000.0f, 1000.0f };

Vector roadRotation = { 0.0f, 0.0f, 0.0f };
Vector roadScale = { 1.0f, 1.0f, 1.0f };


float startZvalue= -200.0f;  

Vector desertRotation = { -0.0f, 0.0f, 0.0f };
Vector desertScale = { 2.5f, 2.5f, 2.5f };


//Light value 

//Cardilac value
Vector cardillac2000Scale = { 0.3f, 0.3f, 0.3f };
Vector cardillacHeadlightLeftPosition = { -2.0f, 1.0f, 0.0f};
Vector cardillacHeadlightRigtPosition = { 2.0f, 1.0f, 0.0f};

Vector cardillacHeadlightDirection = { 0.0f, -0.3f, -1.0f };


Vector cardliacAmbient = { 0.1f, 0.1f, 0.1f };
Vector cardliacDiffuse = { 0.8f, 0.8f, 0.8f };
Vector cardliacSpecular = { 1.0f, 1.0f, 1.0f };
float cardliacLinear;
float cardliacQuadratic;


float innerCutoffCardilac = std::cos(6.0f * M_PI / 180.0f);   
float outerCutoffCardilac = std::cos(10.0f * M_PI / 180.0f);  



//Lamp post 
Vector lampAmbient = { 0.05f, 0.05f, 0.05f };
Vector lampDiffuse = { 1.0f, 1.0f, 1.0f };
Vector lampSpecular = { 1.0f, 1.0f, 1.0f };
float lampLinear = 0.09f;
float lampQuadratic = 0.0032f;


//Light
float innerCutoff = std::cos(6.0f * M_PI / 180.0f);
float outerCutoff = std::cos(6.5f * M_PI / 180.0f);



//Animations 
Vector moveinZAxeln = { 0.0f ,0.0f ,0.5f };
//Vector moveinZAxeln = { 0.0f ,0.0f ,0.0f };
Vector rotationOneGradePerFrameYaxel = { 0.0f ,1.0f ,0.0f };




int animationMaxLengthFrame = 200;
int currentFrame = 0;
const int maxFrame = 1000000;
        

 
