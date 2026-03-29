#include "camera.h"

#define _USE_MATH_DEFINES // To get M_PI defined
#include <math.h>


//Asigment 1.3
// Transformation projects the 3D scene onto a 2D plane by "ingnore" the depth (Z-values).
mat4 OrthogonalProjectionMatrix(float left, float right, float bottom, float top, float near, float far)

{
	mat4 P(1.0f); // Identity matrix

	P[0][0] = 2.0f / (right - left);
	P[1][1] = 2.0f / (top - bottom);
	P[2][2] = 2.0f / (near - far);

	P[3][0] = -(right + left) / (right - left);
	P[3][1] = -(top + bottom) / (top - bottom);
	P[3][2] = -(far + near) / (far - near);
	P[3][3] = 1.0f;

	return P;
}


//Asigmnet 1.3
// Transformation projects the 3D scene onto a 2D plane with the depth (Z-values).
mat4 PerspectiveProjectionMatrix(Camera cam, int screenWidth, int screenHeight)
{

	// Assignment 1: Calculate the projection transform yourself 	
	// The mat4 P should be calculated from camera parameters
	//// Therefore, you need to replace this hard-coded transform.
	//mat4 P;
	//P.e[0] = 1.299038f; P.e[4] = 0.000000f; P.e[ 8] =  0.000000f; P.e[12] =  0.0f;
	//P.e[1] = 0.000000f; P.e[5] = 1.732051f; P.e[ 9] =  0.000000f; P.e[13] =  0.0f;
	//P.e[2] = 0.000000f; P.e[6] = 0.000000f; P.e[10] = -1.000200f; P.e[14] = -2.000200f;
	//P.e[3] = 0.000000f; P.e[7] = 0.000000f; P.e[11] = -1.000000f; P.e[15] =  0.0f;

	//return P;

	mat4 P(0.0f);

	float fovy = (float)cam.fov * (M_PI / 180.0F);

	float aspect = (float)screenWidth / (float)screenHeight;

	float cotFOV = 1.0f / tanf(fovy / 2.0f);

	P[0][0] = cotFOV / aspect;
	P[1][1] = cotFOV;
	P[2][2] = (cam.farPlane + cam.nearPlane) / (cam.nearPlane - cam.farPlane);
	P[2][3] = -1.0f;
	P[3][2] = (2 * cam.farPlane * cam.nearPlane) / (cam.nearPlane - cam.farPlane);


	return P;
}


//Assigmnet 1.2
//Interface function for view mat4


// Function generates a view mat4 that transforms world coordinates into camera coordinates.
mat4 ViewMatrix(Camera cam)
{


	mat4 V = mat4(1.0f);
	float alpha = cam.rotation.x;
	float beta = cam.rotation.y;
	float gamma = cam.rotation.z;

	float cx = cam.position.x;
	float cy = cam.position.y;
	float cz = cam.position.z;


	mat4 Rx = rotate(mat4(1.0f), -alpha, vec3(1.0f, 0.0f, 0.0f));  
	mat4 Ry = rotate(mat4(1.0f), -beta, vec3(0.0f, 1.0f, 0.0f));   
	mat4 Rz = rotate(mat4(1.0f), -gamma, vec3(0.0f, 0.0f, 1.0f));  

	mat4 Translation = translate(mat4(1.0f), -vec3(cx, cy, cz));

	//V = Rz(−gamma)Ry(−beta)Rx(−alpha)T(−c)
	mat4 M1 = Rx * Translation; 
	mat4 M2 = Ry * M1;          
	 V = Rz * M2;            
	

	
	return V;

	
}


//Asigment 1.6 EXTRA

//What we looking at 
mat4 lookAt(vec3 c_cameraPosition,	vec3 v_viewDir,vec3 u_worldUp) {
	vec3 cameraForward = normalize(v_viewDir);
	vec3 cameraRight = normalize(cross(v_viewDir, u_worldUp));
	vec3 cameraUp = normalize(cross(cameraRight, v_viewDir));


	mat4 result(1.0f);

	//Camera  lockal X axel
	result[0][0] = cameraRight.x;
	result[1][0] = cameraRight.y;
	result[2][0] = cameraRight.z;

	//Camera lockal in Y axel
	result[0][1] = cameraUp.x;
	result[1][1] = cameraUp.y;
	result[2][1] = cameraUp.z;

	//Camera lockal in Z axeln 
	result[0][2] = -cameraForward.x;
	result[1][2] = -cameraForward.y;
	result[2][2] = -cameraForward.z;


	//Where the camera is in the word 
	result[3][0] = dot(cameraRight, c_cameraPosition);
	result[3][1] = dot(cameraUp, c_cameraPosition);
	result[3][2] = dot(cameraForward, c_cameraPosition);
	
	result[3][3] = 1.0f;

	return result;

}


//Asigment 1.6 
//To move camera in Six degrees of freedom (6-DOF) 
void MoveCamera(Camera& cam, MoveDirection dir) {

	vec3 forward = normalize(cam.viewDirection);
	vec3 right = normalize(cross(forward, cam.upVector));
	vec3 up = normalize(cross(right, forward));

	switch (dir) {
	case MoveCameraFarward:  cam.position = cam.position + forward; break;
	case MoveCameraBackward: cam.position = cam.position - forward; break;
	case MoveCameraRight:    cam.position = cam.position + right; break;
	case MoveCameraLeft:     cam.position = cam.position - right; break;
	case MoveCameraUp:       cam.position = cam.position + up; break;
	case MoveCameraDown:     cam.position = cam.position - up; break;

	}


}


//Asigment 1.6 
//To move camera (rotation part) in Six degrees of freedom (6-DOF)
void rotateCamera(Camera& cam, CameraRotation rot) {

	float degree = 0.1f;
	vec3 forward = normalize(cam.viewDirection);
	vec3 right = normalize(cross(forward, cam.upVector));
	vec3 up = normalize(cam.upVector);

	mat4 rotationMatrix;

	switch (rot) {

	case CameraYawRight:
		rotationMatrix = rotate(mat4(1.0), -degree, up);
		cam.viewDirection = normalize(vec3(rotationMatrix * vec4(forward, 0.0f)));
		break;
			 
	case CameraYawLeft: 
		rotationMatrix = rotate(mat4(1.0), degree, up);
		cam.viewDirection = normalize(vec3(rotationMatrix * vec4(forward, 0.0f)));				
		break;

	case CameraPitchUp: 
		rotationMatrix = rotate(mat4(1.0), -degree, right);
		cam.viewDirection = normalize(vec3(rotationMatrix * vec4(forward, 0.0f)));
		cam.upVector = normalize(vec3(rotationMatrix * vec4(up, 0.0f)));
		break;

	case CameraPitchDown: 
		rotationMatrix = rotate(mat4(1.0), degree, right);
		cam.viewDirection = normalize(vec3(rotationMatrix * vec4(forward, 0.0f)));
		cam.upVector = normalize(vec3(rotationMatrix * vec4(up, 0.0f)));
		break;

		
	case CameraRollRight : 
		rotationMatrix = rotate(mat4(1.0f), -degree, forward);
		cam.upVector = normalize(vec3(rotationMatrix * vec4(up, 0.0f)));			
		break;

	case CameraRollLeft :
		rotationMatrix = rotate(mat4(1.0f), degree, forward);
		cam.upVector = normalize(vec3(rotationMatrix * vec4(up, 0.0f))); 
		break;
	
	
	}

}


//Function to reste camera to start value 
void resetCamera(Camera& cam) {
		cam.position = cameraStartPositioned;
		cam.rotation = cameraStartRotation;
		cam.viewDirection = cameraStartViewDirection;
		cam.upVector = cameraStartUpVector;
		
}