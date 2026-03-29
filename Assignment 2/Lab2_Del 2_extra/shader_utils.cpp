#include "shader_utils.h"
#include <glew.h>


GLuint basicShaderProgram;
GLuint interlaceShaderProgram;
GLuint activeShaderProgram;
GLuint phongShaderProgram;
GLuint cartoonShaderProgram;

GLuint phongExtraLightShaderProgram;
GLuint cartoonExtraLightShaderProgram;
GLuint flatShaderProgram;


//Function to load a textfile and store it in a string
//source https://www.youtube.com/watch?v=hLv5T2loDZw&ab_channel=MikeShah
std::string LoadShaderAsString(const std::string& filename) {

    std::string result = "";
    std::string line = "";

    std::ifstream myFile(filename.c_str());

    if (myFile.is_open()) {
        std::cout << "Successfully loaded: " << filename << std::endl;
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

//Switch bettewn shader program 
void SwitchShader() {
    if (activeShaderProgram == basicShaderProgram) {
        activeShaderProgram = interlaceShaderProgram;

    }
    else if (activeShaderProgram == interlaceShaderProgram) {
        activeShaderProgram = phongShaderProgram;


    }
    else if (activeShaderProgram == phongShaderProgram) {
        activeShaderProgram = phongExtraLightShaderProgram;
    }
    else if (activeShaderProgram == phongExtraLightShaderProgram) {
        activeShaderProgram = cartoonShaderProgram;
    }
    //else if (activeShaderProgram == cartoonShaderProgram) {
    //    activeShaderProgram = cartoonExtraLightShaderProgram;
    //}

    //else if (activeShaderProgram == cartoonExtraLightShaderProgram) {
    //    activeShaderProgram = flatShaderProgram;
    //}

    
    else {
        activeShaderProgram = basicShaderProgram;

    }
  

}

//Set up light and camera in shader
void SetLightUniforms(GLuint shaderProgram, const Light& sceneLight, const Vector& cameraPosition) {
    // Ljusets position
    GLint locLightPos = glGetUniformLocation(shaderProgram, "light.position");
    glUniform3f(locLightPos, sceneLight.position.x, sceneLight.position.y, sceneLight.position.z);

    // Ambient light
    GLint locLightAmbient = glGetUniformLocation(shaderProgram, "light.ambient");
    glUniform3f(locLightAmbient, sceneLight.ambient.x, sceneLight.ambient.y, sceneLight.ambient.z);

    // Diffus light
    GLint locLightDiffuse = glGetUniformLocation(shaderProgram, "light.diffuse");
    glUniform3f(locLightDiffuse, sceneLight.diffuse.x, sceneLight.diffuse.y, sceneLight.diffuse.z);

    // Specular
    GLint locLightSpecular = glGetUniformLocation(shaderProgram, "light.specular");
    glUniform3f(locLightSpecular, sceneLight.specular.x, sceneLight.specular.y, sceneLight.specular.z);

    // Camera Position 
    GLint locViewPos = glGetUniformLocation(shaderProgram, "viewPos");
    glUniform3f(locViewPos, cameraPosition.x, cameraPosition.y, cameraPosition.z);
}

//Set material value for the shader
void SetMaterialUniforms(GLuint shaderProgram, const Material& material) {

    glUniform3f(glGetUniformLocation(shaderProgram, "material.ambient"),
        material.ambient.x, material.ambient.y, material.ambient.z);


    glUniform3f(glGetUniformLocation(shaderProgram, "material.diffuse"),
        material.diffuse.x, material.diffuse.y, material.diffuse.z);


    glUniform3f(glGetUniformLocation(shaderProgram, "material.specular"),
        material.specular.x, material.specular.y, material.specular.z);


    glUniform1f(glGetUniformLocation(shaderProgram, "material.shininess"), material.shininess);
}


//Extra 
//Set up multi light and camera in shader

void SetExtraLightUniforms(GLuint shaderProgram, const Light* lights, int numLights, const Vector& cameraPosition) {
    char name[128];

    glUniform1i(glGetUniformLocation(shaderProgram, "numLights"), numLights);

    for (int i = 0; i < numLights; ++i) {
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
    }

    // Skicka kamerans position
    GLint locViewPos = glGetUniformLocation(shaderProgram, "viewPos");
    glUniform3f(locViewPos, cameraPosition.x, cameraPosition.y, cameraPosition.z);
}



