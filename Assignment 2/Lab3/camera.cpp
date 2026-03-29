////LAB2 part 1-5
////Lab2 extra start at 117

#include "camera.h"

#define _USE_MATH_DEFINES // To get M_PI defined
#include <math.h>


//Asigment 1.3
// Transformation projects the 3D scene onto a 2D plane by "ingnore" the depth (Z-values).
Matrix OrthogonalProjectionMatrix(float left, float right, float bottom, float top, float near, float far)

{
	Matrix P = { 0 };


	P.e[0] = 2 / (right - left);
	P.e[5] = 2 / (top - bottom);
	P.e[10] = 2 / (near - far);


	P.e[12] = -(right + left) / (right - left);
	P.e[13] = -(top + bottom) / (top - bottom);
	P.e[14] = -(far + near) / (far - near);
	P.e[15] = 1.0f;

	return P;

}


//Asigmnet 1.3
// Transformation projects the 3D scene onto a 2D plane with the depth (Z-values).
Matrix PerspectiveProjectionMatrix(Camera cam, int screenWidth, int screenHeight)
{

	// Assignment 1: Calculate the projection transform yourself 	
	// The matrix P should be calculated from camera parameters
	//// Therefore, you need to replace this hard-coded transform.
	//Matrix P;
	//P.e[0] = 1.299038f; P.e[4] = 0.000000f; P.e[ 8] =  0.000000f; P.e[12] =  0.0f;
	//P.e[1] = 0.000000f; P.e[5] = 1.732051f; P.e[ 9] =  0.000000f; P.e[13] =  0.0f;
	//P.e[2] = 0.000000f; P.e[6] = 0.000000f; P.e[10] = -1.000200f; P.e[14] = -2.000200f;
	//P.e[3] = 0.000000f; P.e[7] = 0.000000f; P.e[11] = -1.000000f; P.e[15] =  0.0f;

	//return P;

	Matrix P = { 0 };

	float fovy = (float)cam.fov * (M_PI / 180.0F);

	float aspect = (float)screenWidth / (float)screenHeight;

	float cotFOV = 1.0f / tanf(fovy / 2.0f);

	P.e[0] = cotFOV / aspect;
	P.e[5] = cotFOV;
	P.e[10] = (cam.farPlane + cam.nearPlane) / (cam.nearPlane - cam.farPlane);
	P.e[11] = -1.0f;
	P.e[14] = (2 * cam.farPlane * cam.nearPlane) / (cam.nearPlane - cam.farPlane);


	return P;
}


//Assigmnet 1.2
//Interface function for view matrix

// Function generates a view matrix that transforms world coordinates into camera coordinates.
Matrix ViewMatrix(Camera cam)
{
	// Assignment 1: Calculate the transform to view coordinates yourself 	
	// The matrix V should be calculated from camera parameters
	// Therefore, you need to replace this hard-coded transform. 
	//Matrix V;
	//V.e[0] = 1.0f; V.e[4] = 0.0f; V.e[ 8] = 0.0f; V.e[12] =   0.0f;
	//V.e[1] = 0.0f; V.e[5] = 1.0f; V.e[ 9] = 0.0f; V.e[13] =   0.0f;
	//V.e[2] = 0.0f; V.e[6] = 0.0f; V.e[10] = 1.0f; V.e[14] = -cam.position.z;
	//V.e[3] = 0.0f; V.e[7] = 0.0f; V.e[11] = 0.0f; V.e[15] =   1.0f;

	Matrix V = { 0 };

	float alpha = cam.rotation.x;
	float beta = cam.rotation.y;
	float gamma = cam.rotation.z;

	float cx = cam.position.x;
	float cy = cam.position.y;
	float cz = cam.position.z;

	Matrix Rx = RotationMatrix_On_X_Axel(-alpha);
	Matrix Ry = RotationMatrix_On_Y_Axel(-beta);
	Matrix Rz = RotationMatrix_On_Z_Axel(-gamma);

	Matrix Translation = TranslationMatrix(-cx, -cy, -cz);



	//V = Rz(−gamma)Ry(−beta)Rx(−alpha)T(−c)

	Matrix M1 = MatMatMul(Rx, Translation);
	Matrix M2 = MatMatMul(Ry, M1);
	V = MatMatMul(Rz, M2);




	return V;
}



//To have diffrent camera 

Camera cameras[MAX_CAMERAS];

int currentCameraIndex = 0;
int cameraCount = 0;

//To have multi camera 
void addCamera(const char* name, Vector position,Vector rotation,double fov,double nearPlane,double farPlane) {

	if (cameraCount >= MAX_CAMERAS)
	{std::cout << "The limit of Cameras, incresse the MAX_CAMERAS value" << std::endl;
	return;}

	cameras[cameraCount].name = name;
	cameras[cameraCount].position = position;
	cameras[cameraCount].rotation = rotation;
	cameras[cameraCount].fov = fov;
	cameras[cameraCount].nearPlane = nearPlane;
	cameras[cameraCount].farPlane = farPlane;

	cameras[cameraCount].startPosition = position;
	cameras[cameraCount].startRotation = rotation;
	

	cameraCount++;
}

//To select camera 
void selectCamera(int index) {
	currentCameraIndex = index;
	cameras[index].position = cameras[index].startPosition;
	cameras[index].rotation = cameras[index].startRotation;


};


