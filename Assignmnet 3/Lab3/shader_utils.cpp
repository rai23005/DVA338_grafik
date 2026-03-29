#include "shader_utils.h"
#include <glew.h>

//diffret shaer program 
GLuint activeShaderProgram;

//Function to load a textfile and store it in a string
//source https://www.youtube.com/watch?v=hLv5T2loDZw&ab_channel=MikeShah
std::string LoadShaderAsString(const std::string& filename) {

    std::string result = "";
    std::string line = "";

    std::ifstream myFile(filename.c_str());

    if (myFile.is_open()) {
        //std::cout << "Successfully loaded: " << filename << std::endl;
        while (std::getline(myFile, line)) {
            result += line + '\n';
        }
        myFile.close();
    }
    else
    {
        std::cerr << "ERROR: Could not open shader file: " << filename << std::endl;
        return "";
    }

    return result;
}


//Send in lights and camera value to Shaders program that will use 
void SetExtraLightUniforms(GLuint shaderProgram, const Light* lights, int numLights, const Vector& cameraPosition) {

    char name[128];

    int activeLights = 0;

    for (int i = 0; i < numLights; ++i) {
        
        //If the light is on or off
        if (lights[i].enabled == true) { 
       

        snprintf(name, sizeof(name), "lights[%d].position", i);
        glUniform3f(glGetUniformLocation(shaderProgram, name),
            lights[i].position.x,
            lights[i].position.y,
            lights[i].position.z);

        snprintf(name, sizeof(name), "lights[%d].ambient", i);
        glUniform3f(glGetUniformLocation(shaderProgram, name),
            lights[i].ambient.x,
            lights[i].ambient.y,
            lights[i].ambient.z);

        snprintf(name, sizeof(name), "lights[%d].diffuse", i);
        glUniform3f(glGetUniformLocation(shaderProgram, name),
            lights[i].diffuse.x,
            lights[i].diffuse.y,
            lights[i].diffuse.z);

        snprintf(name, sizeof(name), "lights[%d].specular", i);
        glUniform3f(glGetUniformLocation(shaderProgram, name),
            lights[i].specular.x,
            lights[i].specular.y,
            lights[i].specular.z);


        //For the spotligt  

        snprintf(name, sizeof(name), "lights[%d].isSpotLight", i);
        glUniform1i(glGetUniformLocation(shaderProgram, name), lights[i].isSpotLight);

        
        Vector normalizDirektion = Normalize(lights[i].direction);

        snprintf(name, sizeof(name), "lights[%d].direction", i);
        glUniform3f(glGetUniformLocation(shaderProgram, name),
            normalizDirektion.x, normalizDirektion.y, normalizDirektion.z);

       
        snprintf(name, sizeof(name), "lights[%d].constant", i);
        glUniform1f(glGetUniformLocation(shaderProgram, name), lights[i].constant);

        snprintf(name, sizeof(name), "lights[%d].linear", i);
        glUniform1f(glGetUniformLocation(shaderProgram, name), lights[i].linear);

        snprintf(name, sizeof(name), "lights[%d].quadratic", i);
        glUniform1f(glGetUniformLocation(shaderProgram, name), lights[i].quadratic);

      
        snprintf(name, sizeof(name), "lights[%d].innerCutoff", i);
        glUniform1f(glGetUniformLocation(shaderProgram, name), lights[i].innerCutoff);

        snprintf(name, sizeof(name), "lights[%d].outerCutoff", i);
        glUniform1f(glGetUniformLocation(shaderProgram, name), lights[i].outerCutoff);

       
        snprintf(name, sizeof(name), "lights[%d].enabled", i);
        glUniform1i(glGetUniformLocation(shaderProgram, name), lights[i].enabled);



        ++activeLights;
        }
    }

    glUniform1i(glGetUniformLocation(shaderProgram, "numLights"), activeLights);



    // Where is the Camera position
    GLint locViewPos = glGetUniformLocation(shaderProgram, "viewPos");
    glUniform3f(locViewPos, cameraPosition.x, cameraPosition.y, cameraPosition.z);
}



//To switch on and of car head lights 
void switchOnOfLight(Light* lights, LightType type, int totaltLight) {
    for (int i = 0; i < totaltLight; i++) {
        
        if (lights[i].type == type) {
            if (lights[i].enabled) {               
                lights[i].enabled = false;               
            }
            else {                
                lights[i].enabled = true;            
            }
        }
    }
}

