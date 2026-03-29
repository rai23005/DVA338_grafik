#ifndef _MESH_H_
#define _MESH_H_

#include "algebra.h"



typedef struct _Triangle {
	int vInds[3]; //vertex indices
} Triangle;

//LAb2 asigment 2.3 
typedef struct _Material {
	Vector ambient;
	Vector diffuse;
	Vector specular;
	float shininess;
} Material;



typedef struct _Mesh {
	int nv;
	Vector* vertices;
	Vector* vnorms;
	int nt;
	Triangle* triangles;
	struct _Mesh* next;

	unsigned int vbo, ibo, vao; // OpenGL handles for rendering



	//Asigment 1.5
	//Update Mesh to get three vector to
	Vector translation;
	Vector rotation;
	Vector scale;

	//Asigment 2.3
	Material material;

} Mesh;

void insertModel(Mesh** objlist, int nv, float* vArr, int nt, int* tArr, float scale,
	Vector translation,
	Vector rotation,
	Vector vectorScale, Material material);

#endif




