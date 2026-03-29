//Lab2 part 1 1-5

#ifndef _CAMERA_H
#define _CAMERA_H
#include "algebra.h"
#include <iostream>


typedef struct _Camera {
	Vector position;
	Vector rotation;
	double fov;
	double nearPlane;
	double farPlane;
	const char* name;

	Vector startPosition;
	Vector startRotation;

} Camera;

Matrix PerspectiveProjectionMatrix(
	Camera cam,
	int screenWidth,
	int screenHeight);
Matrix ViewMatrix(Camera cam);

Matrix OrthogonalProjectionMatrix(
	float left,
	float right,
	float bottom,
	float top,
	float near,
	float far);



Matrix ViewMatrix(Camera cam);


#define MAX_CAMERAS 5
extern Camera cameras[MAX_CAMERAS];
extern int currentCameraIndex;
extern int cameraCount;


void addCamera(const char* name, Vector position, Vector rotation, double fov, double nearPlane, double farPlane);



void selectCamera(int index);




#endif



