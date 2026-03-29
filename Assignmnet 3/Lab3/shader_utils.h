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

extern GLuint activeShaderProgram;



GLuint LoadShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);

//Asigment extra
void SetExtraLightUniforms(GLuint shaderProgram, const Light* lights, int numLights, const Vector& cameraPosition);

void switchOnOfLight(Light* lights, LightType type, int totaltLight);


