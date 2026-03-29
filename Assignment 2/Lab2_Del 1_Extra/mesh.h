#ifndef _MESH_H_
#define _MESH_H_



#include "glm.hpp"
#include "matrix_transform.hpp"
using glm::vec3;
using glm::mat4;
using glm::normalize;
using glm::cross;

typedef struct _Triangle {
	int vInds[3]; //vertex indices
} Triangle;

typedef struct _Mesh { 
	int nv;				
	vec3 *vertices;
	vec3 *vnorms;
	int nt;				
	Triangle *triangles;
	struct _Mesh *next; 
		
	unsigned int vbo, ibo, vao; // OpenGL handles for rendering



	//Asigment 1.5
	//Update Mesh to get three vec3 to
	vec3 translation;
	vec3 rotation;
	vec3 scale;




} Mesh;

void insertModel(Mesh ** objlist, int nv, float * vArr, int nt, int * tArr, float scale = 1.0, 
	vec3 translation = { 0.0f, 0.0f, 0.0f }, 
	vec3 rotation = { 0.0f, 0.0f, 0.0f }, 
	vec3 vec3Scale = { 1.0f, 1.0f, 1.0f });

#endif
