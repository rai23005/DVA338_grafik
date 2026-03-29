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

extern "C" {
#include "obj.h"
}




#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "configvalue.h"



typedef struct ShaderNode {
	GLuint programID;
	const char* name;
	struct ShaderNode* next;
} ShaderNode;

extern ShaderNode* shaderList;
extern ShaderNode* activeShader;

void addShader(const char* name, const char* vertexPath, const char* fragmentPath);
void switchToNextShader();



obj* load_obj_model(const char* filepath);
void add_obj_to_list(obj* model,
	const char* modelname,
	int id,
	Vector translation,
	Vector rotation,
	Vector vectorScale, 
	Vector translationPerFrame, 
	Vector rotationPerFrame, 
	Vector scalePerFrame,
	int animationMaxLengthFrame,
	int offsetFrame);


void prepare_obj(obj* model, GLuint shaderProgram);

void SetObjMaterialUniforms(GLuint shaderProgram, obj* model);


int getanimateFrameloop(int animationMaxLengthFrame, int currentFrame, int offsetFrame);


Vector animateVector(Vector base, Vector perfram, int frame);
float rotationWrapDegree(float degree);
Vector rationWrapVector(Vector base, Vector perfram, int frame);

float moveBackToStart(float value, float maxZ, float startZvalue);
