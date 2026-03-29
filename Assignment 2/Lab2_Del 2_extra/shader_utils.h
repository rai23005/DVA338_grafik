#pragma once

//#define _CRT_SECURE_NO_WARNINGS

#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
	//If you follow the setup instructions provided for Visual Studio
	//The include path specified already includes "GL", so we can ignore it
#include <glew.h>
#include <freeglut.h>
#else
#include <GL/glew.h>
#endif




#include <string>

#include <iostream>
#include <fstream>
#include <sstream>
#include "configvalue.h"


std::string LoadShaderAsString(const std::string& filename);



extern GLuint basicShaderProgram;
extern GLuint interlaceShaderProgram;
extern GLuint activeShaderProgram;
extern GLuint phongShaderProgram;
extern GLuint cartoonShaderProgram;

extern GLuint phongExtraLightShaderProgram;
extern GLuint cartoonExtraLightShaderProgram;

extern GLuint flatShaderProgram;

void SwitchShader();

void SetLightUniforms(GLuint shaderProgram, const Light& sceneLight, const Vector& cameraPosition);
void SetMaterialUniforms(GLuint shaderProgram, const Material& material);
GLuint LoadShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);


//Asigment extra
void SetExtraLightUniforms(GLuint shaderProgram, const Light* lights, int numLights, const Vector& cameraPosition);