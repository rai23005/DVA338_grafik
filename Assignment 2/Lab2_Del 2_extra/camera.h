//Lab2 part 1 1-5

#ifndef _CAMERA_H
#define _CAMERA_H
#include "algebra.h"

typedef struct _Camera {
	Vector position;
	Vector rotation;
	double fov;
	double nearPlane;
	double farPlane;
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

#endif



