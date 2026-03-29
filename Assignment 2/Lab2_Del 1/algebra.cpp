#define _USE_MATH_DEFINES // To get M_PI defined
#include <math.h>
#include <stdio.h>
#include "algebra.h"

Vector CrossProduct(Vector a, Vector b) {
	Vector v = { a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x };
	return v;
}

float DotProduct(Vector a, Vector b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vector Subtract(Vector a, Vector b) {
	Vector v = { a.x-b.x, a.y-b.y, a.z-b.z };
	return v;
}    

Vector Add(Vector a, Vector b) {
	Vector v = { a.x+b.x, a.y+b.y, a.z+b.z };
	return v;
}    

float Length(Vector a) {
	return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

Vector Normalize(Vector a) {
	float len = Length(a);
	Vector v = { a.x/len, a.y/len, a.z/len };
	return v;
}

Vector ScalarVecMul(float t, Vector a) {
	Vector b = { t*a.x, t*a.y, t*a.z };
	return b;
}

HomVector MatVecMul(Matrix a, Vector b) {
	HomVector h;
	h.x = b.x*a.e[0] + b.y*a.e[4] + b.z*a.e[8] + a.e[12];
	h.y = b.x*a.e[1] + b.y*a.e[5] + b.z*a.e[9] + a.e[13];
	h.z = b.x*a.e[2] + b.y*a.e[6] + b.z*a.e[10] + a.e[14];
	h.w = b.x*a.e[3] + b.y*a.e[7] + b.z*a.e[11] + a.e[15];
	return h;
}

Vector Homogenize(HomVector h) {
	Vector a;
	if (h.w == 0.0) {
		fprintf(stderr, "Homogenize: w = 0\n");
		a.x = a.y = a.z = 9999999;
		return a;
	}
	a.x = h.x / h.w;
	a.y = h.y / h.w;
	a.z = h.z / h.w;
	return a;
}

Matrix MatMatMul(Matrix a, Matrix b) {
	Matrix c;
	int i, j, k;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			c.e[j*4+i] = 0.0;
			for (k = 0; k < 4; k++)
				c.e[j*4+i] += a.e[k*4+i] * b.e[j*4+k];
		}
	}
	return c;
}

void PrintVector(char const *name, Vector a) {
	printf("%s: %6.5lf %6.5lf %6.5lf\n", name, a.x, a.y, a.z);
}

void PrintHomVector(char const *name, HomVector a) {
	printf("%s: %6.5lf %6.5lf %6.5lf %6.5lf\n", name, a.x, a.y, a.z, a.w);
}

void PrintMatrix(char const *name, Matrix a) { 
	int i,j;

	printf("%s:\n", name);
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			printf("%6.5lf ", a.e[j*4+i]);
		}
		printf("\n");
	}
}

//Asigment 1.4
//Get a normal for a triangel when use onlye three points
Vector SurfaceNormal(Vector a, Vector b, Vector c)
{
	Vector u = Subtract(b, a);
	Vector w = Subtract(c, a); 
	Vector n = CrossProduct(u, w);
	
	return Normalize(n);
}


//Asigment 1.2 Viewing Transformation

// TranslationMatrix for 3d
Matrix TranslationMatrix(float tx, float ty, float tz) {

	Matrix move = {0};
	move.e[0] = 1.0f;
	move.e[5] = 1.0f;
	move.e[10] = 1.0f;
		
	move.e[12] = tx;
	move.e[13] = ty;
	move.e[14] = tz;

	move.e[15] = 1.0f;

	return move;
}

Matrix ScalingMatrix(float sx, float sy, float sz) {
	
	Matrix scale={ 0 };
		
	scale.e[0] = sx;
	scale.e[5] = sy;
	scale.e[10] = sz;
	scale.e[15] = 1.0f;

	return scale;
}

//Matrix for rotation of diffrent Axel
Matrix RotationMatrix_On_X_Axel(float degree) {

	Matrix rotateX = {0};

	float radian = degree * (M_PI / 180.0F);
	
	float cosValue = cosf(radian);
	float sinValue = sinf(radian);
	
	rotateX.e[0] = 1.0f;
	rotateX.e[5] = cosValue;
	rotateX.e[6] = sinValue;
	rotateX.e[9] = -sinValue;
	rotateX.e[10] = cosValue;
	rotateX.e[15] = 1.0f;

	return rotateX;
}

Matrix RotationMatrix_On_Y_Axel(float degree)
{

	Matrix rotateY = { 0 };

	float radian = degree * (M_PI / 180.0F);


	float cosValue = cosf(radian);
	float sinValue = sinf(radian);

	rotateY.e[0] = cosValue; 
	rotateY.e[2] = -sinValue;
	rotateY.e[5] = 1.0f;
	rotateY.e[8] = sinValue;
	rotateY.e[10] = cosValue;
	rotateY.e[15] = 1.0f;

	return rotateY;
}
Matrix RotationMatrix_On_Z_Axel(float degree) {

	Matrix rotateZ = { 0 };
	float radian = degree * (M_PI / 180.0F);


	float cosValue = cosf(radian);
	float sinValue = sinf(radian);
	
	rotateZ.e[0] = cosValue;
	rotateZ.e[1] = sinValue;
	rotateZ.e[4] = -sinValue;
	rotateZ.e[5] = cosValue;
	rotateZ.e[10] = 1.0f;
	rotateZ.e[15] = 1.0f;

	return rotateZ;
}



//Asigmnet 1.5
//Builds a transformation matrix to move a 3D model from local object space to world coordinates.
// IF you have to move it like W = T(t)Rx(rx)Ry(ry)Rz(rz)S(s)

Matrix BuildModelLocalToWordMatrix(Vector translation, Vector rotation, Vector scale) {

	Matrix S = ScalingMatrix(scale.x, scale.y, scale.z);
	Matrix Rx = RotationMatrix_On_X_Axel(rotation.x);
	Matrix Ry = RotationMatrix_On_Y_Axel(rotation.y);
	Matrix Rz = RotationMatrix_On_Z_Axel(rotation.z);
	Matrix T = TranslationMatrix(translation.x, translation.y, translation.z);

	//MatMatMul(Matrix a, Matrix b)


	//W = T(t)Rx(rx)Ry(ry)Rz(rz)S(s)

	Matrix m1 = MatMatMul(Rz, S);
	Matrix m2 = MatMatMul(Ry, m1);
	Matrix m3 = MatMatMul(Rx, m2);
	Matrix w = MatMatMul(T, m3);

	return w;
}