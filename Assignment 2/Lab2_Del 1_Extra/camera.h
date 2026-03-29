#ifndef _CAMERA_H
#define _CAMERA_H



#include "configvalue.h"

//Asigment 
#include "glm.hpp"
#include "matrix_transform.hpp"
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::translate;
using glm::rotate;
using glm::normalize;
using glm::cross;
using glm::dot;

//For asigment 1.6 extra 
//Enum value for camera moment 
enum MoveDirection { MoveCameraFarward, MoveCameraBackward, 
	MoveCameraLeft, MoveCameraRight, 
	MoveCameraUp, MoveCameraDown, ResetCamera};

enum CameraRotation { CameraYawRight, CameraYawLeft, 
	CameraPitchUp,CameraPitchDown,  
	CameraRollRight, CameraRollLeft };

typedef struct _Camera {
	vec3 position;
	vec3 rotation;

	//asigment 1.6 EXTRA
	vec3 viewDirection;
	vec3 upVector;

	double fov; 
	double nearPlane; 
	double farPlane; 




} Camera;

mat4 PerspectiveProjectionMatrix(
	Camera cam, 
	int screenWidth, 
	int screenHeight);


mat4 OrthogonalProjectionMatrix(
	float left, 
	float right, 
	float bottom, 
	float top, 
	float near, 
	float far);
	


mat4 ViewMatrix(Camera cam);

mat4 lookAt(vec3 c_cameraPosition,
	vec3 v_viewDirection,
	vec3 u_up);


//Asigment 1.6
void MoveCamera(Camera& cam, MoveDirection dir);

void rotateCamera(Camera& cam, CameraRotation rot);

void resetCamera(Camera& cam);

#endif