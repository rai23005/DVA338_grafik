//LAB2 1-5
// Extra from 400

//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
	//If you follow the setup instructions provided for Visual Studio
	//The include path specified already includes "GL", so we can ignore it
#include <glew.h>
#include <freeglut.h>
#elif defined(__APPLE__)
#define GL_SILENCE_DEPRECATION
#include <GL/glew.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif
#include "camera.h"	//algebra is included in camera.h
#include "shaders.h"
#include "mesh.h"

//All configValue 
#include "configvalue.h"


//PArt 2
#include "shader_utils.h"
#include <string>

bool switchShaders = true;


Camera cam = { cameraPositioned, cameraRotation, 60, 1, 10000 }; // Setup the global camera parameters





int screen_width = 1024;
int screen_height = 768;


//Asigment 3
float knotRotationForAnimate = 0.0f;
Mesh* knotModel;


Mesh* meshList = NULL; // Global pointer to linked list of triangle meshes

GLuint shprg; // Shader program id
int windowHandle;

// Global transform matrices
// V is the view transform
// P is the projection transform
// PV = P * V is the combined view-projection transform
Matrix V, P, PV;

//To swich between Perspective mode
bool usePerspective = true;

void printShaderErrorInfo(GLuint shaderProgram)
{
	GLint maxLength = 0;
	glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

	// The maxLength includes the NULL character
	GLchar* errorLog = (GLchar*)calloc(maxLength, sizeof(GLchar));
	glGetShaderInfoLog(shaderProgram, maxLength, &maxLength, &errorLog[0]);

	// Provide the infolog in whatever manor you deem best.
	printf("%s\n", errorLog);
	printf("\n");
	free(errorLog);
}
GLuint prepareShaderProgram(const char** vs_src, const char** fs_src) {
	GLint success = GL_FALSE;

	shprg = glCreateProgram();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, vs_src, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success) printf("Error in vertex shader!\n");
	else printf("Vertex shader compiled successfully!\n");
	if (success == GL_FALSE)
	{
		printShaderErrorInfo(vs);
		glDeleteShader(vs); // Don't leak the shader.
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, fs_src, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success) printf("Error in fragment shader!\n");
	else printf("Fragment shader compiled successfully!\n");
	if (success == GL_FALSE)
	{
		printShaderErrorInfo(fs);
		glDeleteShader(fs); // Don't leak the shader.
	}

	glAttachShader(shprg, vs);
	glAttachShader(shprg, fs);
	glLinkProgram(shprg);
	GLint isLinked = GL_FALSE;
	glGetProgramiv(shprg, GL_LINK_STATUS, &isLinked);
	if (!isLinked) printf("Link error in shader program!\n");
	else printf("Shader program linked successfully!\n");

	return shprg;
}

void prepareMesh(Mesh* mesh) {
	int sizeVerts = mesh->nv * 3 * sizeof(float);
	int sizeCols = mesh->nv * 3 * sizeof(float);
	int sizeTris = mesh->nt * 3 * sizeof(int);

	// For storage of state and other buffer objects needed for vertex specification
	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);

	// Allocate VBO and load mesh data (vertices and normals)
	glGenBuffers(1, &mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeVerts + sizeCols, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeVerts, (void*)mesh->vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeVerts, sizeCols, (void*)mesh->vnorms);

	// Allocate index buffer and load mesh indices
	glGenBuffers(1, &mesh->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeTris, (void*)mesh->triangles, GL_STATIC_DRAW);

	// Define the format of the vertex data
	GLint vPos = glGetAttribLocation(shprg, "vPos");
	glEnableVertexAttribArray(vPos);
	glVertexAttribPointer(vPos, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// Define the format of the vertex data 
	GLint vNorm = glGetAttribLocation(shprg, "vNorm");
	glEnableVertexAttribArray(vNorm);
	glVertexAttribPointer(vNorm, 3, GL_FLOAT, GL_FALSE, 0, (void*)(mesh->nv * 3 * sizeof(float)));

	glBindVertexArray(0);

}



void renderMesh(Mesh* mesh) {

	// Assignment TODO: Apply the transforms from local mesh coordinates to world coordinates here
	// Combine it with the viewing transform that is passed to the shader below*


	//Asigment 1.5 
	//Transforms from local, to the word kondinate
	Matrix W = BuildModelLocalToWordMatrix(mesh->translation, mesh->rotation, mesh->scale);


	//M = VW
	Matrix M = MatMatMul(V, W);



	PV = MatMatMul(P, M);


	// Pass the viewing transform to the shader
	GLint loc_PV = glGetUniformLocation(shprg, "PV");
	glUniformMatrix4fv(loc_PV, 1, GL_FALSE, PV.e);

	//Pass the model (world transform) to the shader 
	GLint loc_Model = glGetUniformLocation(shprg, "model");
	glUniformMatrix4fv(loc_Model, 1, GL_FALSE, W.e);



	// Select current resources 
	glBindVertexArray(mesh->vao);

	// To accomplish wireframe rendering (can be removed to get filled triangles)
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Draw only the line 


	//Asigmnet 1.4
	//FIll the triangel 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	// Draw all triangles
	glDrawElements(GL_TRIANGLES, mesh->nt * 3, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}



void display(void) {
	Mesh* mesh;

	//Asigmentt 1.4
	//Z-buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	/*
	Assignment TODO: The implementation of the View- and ProjectionMatrix functions in camera.cpp
	returns hardcoded matrices. Your assignment is to fix them.
	*/

	//Where is the camera 
	V = ViewMatrix(cam);


	//Switch bettwen Projection or Orthograic perspective
	if (usePerspective) {
		P = PerspectiveProjectionMatrix(cam, screen_width, screen_height);
	}
	else {
		P = OrthogonalProjectionMatrix(left, right, bottom, top, config_near, config_far);
	}


	// This finds the combined view-projection matrix
	PV = MatMatMul(P, V);




	// Select the shader program to be used during rendering 
	glUseProgram(activeShaderProgram);

	//Set up lights and camera for diffrent shader program 
	if (activeShaderProgram == phongShaderProgram || activeShaderProgram == cartoonShaderProgram) {
		SetLightUniforms(activeShaderProgram, sceneLight, cameraPositioned);
	}


	// Render all meshes in the scene
	mesh = meshList;

	while (mesh != NULL) {

		if (activeShaderProgram == phongShaderProgram || activeShaderProgram == cartoonShaderProgram) {
			SetMaterialUniforms(activeShaderProgram, mesh->material);
		}
		

		renderMesh(mesh);
		mesh = mesh->next;
	}

	glFlush();
}

void changeSize(int w, int h) {
	screen_width = w;
	screen_height = h;
	glViewport(0, 0, screen_width, screen_height);

}
void cleanUp(void);

//Assigment 1.2 
//What diffrent key press shall do 
void keypress(unsigned char key, int x, int y) {
	switch (key) {
	case 'x':
		cam.position.x -= 0.2f;
		break;
	case 'X':
		cam.position.x += 0.2f;
		break;
	case 'y':
		cam.position.y -= 0.2f;
		break;
	case 'Y':
		cam.position.y += 0.2f;
		break;
	case 'z':
		cam.position.z -= 0.2f;
		break;
	case 'Z':
		cam.position.z += 0.2f;
		break;

	case 'i':
		cam.rotation.x -= 0.2f;
		break;
	case 'I':
		cam.rotation.x += 0.2f;
		break;
	case 'j':
		cam.rotation.y -= 0.2f;
		break;
	case 'J':
		cam.rotation.y += 0.2f;
		break;
	case 'k':
		cam.rotation.z -= 0.2f;
		break;
	case 'K':
		cam.rotation.z += 0.2f;
		break;
	case 'p':
		usePerspective = !usePerspective;
		break;
	case 'P':
		usePerspective = !usePerspective;
		break;
	case 's':
		SwitchShader();
		break;
	case 'S':
		SwitchShader();
		break;


	case 'Q':
	case 'q':
#ifdef __APPLE__
		// MAC OS GLUT does not implement LeaveMainLoop().
		cleanUp();
		exit(0);
#else
		glutLeaveMainLoop();
#endif
		break;
	}
	glutPostRedisplay();
}


//Load diffrent shader program 
GLuint LoadShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) {

	std::string vertexShaderSource = LoadShaderAsString(vertexPath);
	std::string fragmentShaderSource = LoadShaderAsString(fragmentPath);

	// convert for c string, need for prepareShaderProgram();
	const char* vs_src = vertexShaderSource.c_str();
	const char* fs_src = fragmentShaderSource.c_str();


	return prepareShaderProgram(&vs_src, &fs_src);
}


void init(void) {


	//Load shaders program 
	basicShaderProgram = LoadShaderProgram(
		"../../DVA338_Lab1/vertex_shader.glsl",
		"../../DVA338_Lab1/fragment_shader.glsl");

	interlaceShaderProgram = LoadShaderProgram(
		"../../DVA338_Lab1/InterlacedVertexShader.glsl",
		"../../DVA338_Lab1/InterlacedFragShader.glsl");

	phongShaderProgram = LoadShaderProgram(
		"../../DVA338_Lab1/phong_VertexShader.glsl",
		"../../DVA338_Lab1/phong_FragShader.glsl");

	cartoonShaderProgram = LoadShaderProgram(
		"../../DVA338_Lab1/cartoon_VertexShader.glsl",
		"../../DVA338_Lab1/cartoon_FragShader.glsl");


	//Start shader program 
	activeShaderProgram = basicShaderProgram;



	// Setup OpenGL buffers for rendering of the meshes
	Mesh* mesh = meshList;
	while (mesh != NULL) {
		prepareMesh(mesh);
		mesh = mesh->next;
	}
}

void cleanUp(void) {
	printf("Running cleanUp function... ");
	// Free openGL resources
	// ...
	glutDestroyWindow(windowHandle);

	// Free meshes
	// ...

	printf("Done!\n\n");
}

// Include data for some triangle meshes (hard coded in struct variables)
#include "./models/mesh_bunny.h"
#include "./models/mesh_cow.h"
#include "./models/mesh_cube.h"
#include "./models/mesh_frog.h"
#include "./models/mesh_knot.h"
#include "./models/mesh_sphere.h"
#include "./models/mesh_teapot.h"
#include "./models/mesh_triceratops.h"


//Asigmnet 3
void Assigment3(int value) {
	std::cout << "prints something to the console! for asigment 3.1" << std::endl;

	glutTimerFunc(1000, Assigment3, 0);

}

//Function for rotation 
void TimerFunction(int value) {

	//part 3.2
	knotRotationForAnimate += 2.0f;

	meshList->rotation.y = knotRotationForAnimate;

	glutPostRedisplay();

	glutTimerFunc(20, TimerFunction, 0);


}





int main(int argc, char** argv) {

	// Setup freeGLUT
	unsigned int _glut_mode = GLUT_SINGLE | GLUT_RGB;
#ifdef __APPLE__
	_glut_mode |= GLUT_3_2_CORE_PROFILE;
#endif
	glutInitDisplayMode(_glut_mode);
	glutInit(&argc, argv);
	glutInitWindowSize(screen_width, screen_height);
	windowHandle = glutCreateWindow("DVA338 Programming Assignments");
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(keypress);
	//This is a freeglut define value. In MacOS GLUT, these functions do not exist.
#ifdef GLUT_CORE_PROFILE 
	glutInitContextVersion(4, 1);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
#endif

	glewExperimental = GL_TRUE;
	// Uses GLEW as OpenGL Loading Library to get access to modern core features as well as extensions
	GLenum err = glewInit();
	if (GLEW_OK != err) { fprintf(stdout, "Error: %s\n", glewGetErrorString(err)); return 1; }

	// Output OpenGL version info
	fprintf(stdout, "GLEW version: %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, "OpenGL version: %s\n", (const char*)glGetString(GL_VERSION));
	fprintf(stdout, "OpenGL vendor: %s\n\n", glGetString(GL_VENDOR));





	// Insert the 3D models you want in your scene here in a linked list of meshes
	// Note that "meshList" is a pointer to the first mesh and new meshes are added to the front of the list	
	//insertModel(&meshList, cow.nov, cow.verts, cow.nof, cow.faces, 20.0);
	//insertModel(&meshList, triceratops.nov, triceratops.verts, triceratops.nof, triceratops.faces, 3.0);
	//insertModel(&meshList, bunny.nov, bunny.verts, bunny.nof, bunny.faces, 60.0);	
	//insertModel(&meshList, cube.nov, cube.verts, cube.nof, cube.faces, 5.0);
	//insertModel(&meshList, frog.nov, frog.verts, frog.nof, frog.faces, 2.5);
	//insertModel(&meshList, knot.nov, knot.verts, knot.nof, knot.faces, 1.0);
	//insertModel(&meshList, sphere.nov, sphere.verts, sphere.nof, sphere.faces, 12.0);
	//insertModel(&meshList, teapot.nov, teapot.verts, teapot.nof, teapot.faces, 3.0);



	// Add that insert model will have to postion, roation and scale vectors 
	insertModel(&meshList, cow.nov, cow.verts, cow.nof, cow.faces, 20.0, cowPositioned, cowRotation, cowScale, cowMaterial);
	insertModel(&meshList, teapot.nov, teapot.verts, teapot.nof, teapot.faces, 3.0, teapotPositioned, teapotRotation, teapotScale, teapotMaterial);
	insertModel(&meshList, triceratops.nov, triceratops.verts, triceratops.nof, triceratops.faces, 3.0, triceratopsPositioned, triceratopsRotation, triceratopsScale, triceratopsMaterial);



	//Asigment 3.2
	//insertModel(&meshList, cube.nov, cube.verts, cube.nof, cube.faces, 5.0, knotPositioned, knotRotation, knotScale, triceratopsMaterial);
	//insertModel(&meshList, knot.nov, knot.verts, knot.nof, knot.faces, 1.0, cubePositioned, cubeRotation, cubeScale, cowMaterial);



	init();


	//Asigment 3.1
	//glutTimerFunc(1000, Assigment3, 0);
	//glutTimerFunc(20, TimerFunction, 0);

	glutMainLoop();

	cleanUp();
	return 0;
}







