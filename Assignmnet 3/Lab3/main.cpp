//PArt 1 on line 
//Line 525 

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
#include "lab3_utils.h"
#define _USE_MATH_DEFINES // To get M_PI defined


extern "C" {
#include "obj.h"
}


//All configValue 
#include "configvalue.h"


//PArt 2
#include "shader_utils.h"
#include <string>


bool switchShaders = true;
bool carSpotlightOn = true;


Camera cam;

//Size of the screen 
int screen_width = 1024;
int screen_height = 768;


//Number of the lights
int lightCount = sizeof(lab3Light) / sizeof(lab3Light[0]);


//Mesh* meshList = NULL; // Global pointer to linked list of triangle meshes

//GLuint shprg; // Shader program id
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

	GLuint shprg = glCreateProgram();

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



//Matrix to get where object have move each frame
Matrix animateMatrix(ObjNode* objectNode, int frame) {


	//caluate where the model is in the world after x frame 
	Vector scale = animateVector(objectNode->scale, objectNode->scalePerFrame, frame);

	Vector translation = animateVector(objectNode->translation, objectNode->translationPerFrame, frame);

	Vector rotation = rationWrapVector(objectNode->rotation, objectNode->rotationPerFrame, frame);

	//Do a matrix with all transofrmations the model 
	Matrix S = ScalingMatrix(scale.x, scale.y, scale.z);
	Matrix T = TranslationMatrix(translation.x, translation.y, translation.z);
	Matrix Rxmat = RotationMatrix_On_X_Axel(rotation.x);
	Matrix Rymat = RotationMatrix_On_Y_Axel(rotation.y);
	Matrix Rzmat = RotationMatrix_On_Z_Axel(rotation.z);

	// R = Rz * Ry * Rx
	Matrix Rmat = MatMatMul(Rzmat, MatMatMul(Rymat, Rxmat));

	// W = T * R * S
	Matrix TR = MatMatMul(T, Rmat);
	Matrix W = MatMatMul(TR, S);

	return W;

}


// Render where all object will be in the sceen 
void renderObj(ObjNode* objectNode) {

	int frame = getanimateFrameloop(objectNode->animationMaxLengthFrame, currentFrame, objectNode->offsetFrame);
	

	Matrix W = animateMatrix(objectNode, frame);


	//V=Where is the camera 
	// W= where is the model
	// P = with persektiv will be use
	
	
	Matrix M = MatMatMul(V, W);

	// PV = P * M
	Matrix PV = MatMatMul(P, M);

	// Add PV and model to shaders 
	GLint loc_PV = glGetUniformLocation(activeShaderProgram, "PV");
	glUniformMatrix4fv(loc_PV, 1, GL_FALSE, PV.e);

	GLint loc_Model = glGetUniformLocation(activeShaderProgram, "model");
	glUniformMatrix4fv(loc_Model, 1, GL_FALSE, W.e);

	
	obj_render(objectNode->model);
}


//Uppdate where light is after some frame
void updateLightAnimation(Light* light, int currentFrame) {

	int localFrame = getanimateFrameloop(light->animationMaxLengthFrame, currentFrame, light->offsetFrame);
	light->position = animateVector(light->basePosition, light->translationPerFrame, localFrame);

}



//What will be display one the screen 
void display(void) {

	Camera cam = cameras[currentCameraIndex];

	//Z-buffer, the deapth 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

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

	//Uppdate where all lights is 
	for (int i = 0; i < lightCount; i++) {
		updateLightAnimation(&lab3Light[i], currentFrame);
	}

	//Send the light information to the shader 
	SetExtraLightUniforms(activeShaderProgram, lab3Light, lightCount, cameraPositioned);
		

	//What shader that will be use 
	glUseProgram(activeShaderProgram);
	


	//For each objekt in the list, render them 
	for (int i = 0; i < objectCount; i++) {
		

		//Send in material value for the objekt to shader 
		SetObjMaterialUniforms(activeShaderProgram, objectArray[i].model);

		//If the object is skybox, for not get "light on XYZ axel "
		if (strcmp(objectArray[i].modelname, "skybox") == 0) {
			GLint locSkybox = glGetUniformLocation(activeShaderProgram, "isSkybox");
			glUniform1i(locSkybox, 1); 
		}
		else {
			GLint locSkybox = glGetUniformLocation(activeShaderProgram, "isSkybox");
			glUniform1i(locSkybox, 0); 
		}



		renderObj(&objectArray[i]);
	}



	glFlush();
}

void changeSize(int w, int h) {
	screen_width = w;
	screen_height = h;
	glViewport(0, 0, screen_width, screen_height);

}
void cleanUp(void);


//What diffrent key press shall do 
void keypress(unsigned char key, int x, int y) {

	Camera* cam = &cameras[currentCameraIndex];



	switch (key) {

		//MOve the camera
	case 'x':
		cam->position.x -= 0.2f;
		break;
	case 'X':
		cam->position.x += 0.2f;
		break;
	case 'y':
		cam->position.y -= 0.2f;
		break;
	case 'Y':
		cam->position.y += 0.2f;
		break;
	case 'z':
		cam->position.z -= 1.2f;
		break;
	case 'Z':
		cam->position.z += 1.2f;
		break;

	case 'i':
		cam->rotation.x -= 1.2f;
		break;
	case 'I':
		cam->rotation.x += 1.2f;
		break;
	case 'j':
		cam->rotation.y -= 1.2f;
		break;
	case 'J':
		cam->rotation.y += 1.2f;
		break;
	case 'k':
		cam->rotation.z -= 1.2f;
		break;
	case 'K':
		cam->rotation.z += 1.2f;
		break;

		//Switch persektiv
	case 'p':
		usePerspective = !usePerspective;
		break;
	case 'P':
		usePerspective = !usePerspective;
		break;

		//Change the shader program that will use 
	case 's':
		switchToNextShader();
		break;
	case 'S':
		switchToNextShader();
		break;

		//Select camera
	case '1':
		selectCamera(2);
		break;
	case '2':
		selectCamera(1);
		break;
	case '3':
		selectCamera(0);
		break;
	case '4':
		selectCamera(3);
		break;

		////Turn on and of the light on cardilac
	case 'l':
		switchOnOfLight(lab3Light, LIGHT_TYPE_HEADLIGHT, lightCount);

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

//Start seting function 
void init(void) {


	lightCount = sizeof(lab3Light) / sizeof(lab3Light[0]);


	//Add Cameras 

	addCamera("thirdPersonCamera", thirdPersonViewPositioned, thirdPersonViewRotation, 60, 1, 10000);
	addCamera("sideViewCamera", cameraPositioned, cameraRotation, 60, 1, 10000);	
	addCamera("firstpersonViewCamera", firstpersoncameraPositioned, firstpersoncameraRotation, 60, 1, 10000);

	addCamera("2000_Cardilac", cameraPositioned2, firstpersoncameraRotation, 60, 1, 10000);

	//Add shader program 

	addShader("LAB3_Phong", "../../dva338_lab1/Lab3_advance_VertexShader.glsl",
		"../../dva338_lab1/LAB3_phong_FragShader_extra_light.glsl");

	addShader("LAB3_Cartoon", "../../dva338_lab1/Lab3_advance_VertexShader.glsl",
		"../../dva338_lab1/LAB3_cartoon_FragShade_extra_light.glsl");


	addShader("BasicShaderProgram", "../../DVA338_Lab1/vertex_shader.glsl",
		"../../DVA338_Lab1/fragment_shader.glsl");

	addShader("interlaceShaderProgram", "../../DVA338_Lab1/InterlacedVertexShader.glsl",
		"../../DVA338_Lab1/InterlacedFragShader.glsl");

	////Path for add model in the schen 
	obj* cadillacModel = load_obj_model(pathCadillac);
	obj* skyBoxModel = load_obj_model(pathSkybox);
	obj* roadModel = load_obj_model(pathRoad);
	obj* lampModel = load_obj_model(pathLamp);
	obj* desertModel = load_obj_model(pathDesert);



	if (LAB_THREE == 0) {
			//////////////PART 1
			// Do 2000 put in 2000 cardilac to the sceen, part 1 in assigment  
			Vector cadillacScale2000 = { 0.3f, 0.3f, 0.3f };
			

			int instanceID = 0;
			for (int x = -20; x <= 18; x += 2) {
				for (int y = -20; y <= 18; y += 2) {
					for (int z = -5; z >= -13; z -= 2) {
						Vector translate = { (float)x, (float)y, (float)z };

					
						
							//Diffretn translationP 
							Vector translationPerFrame = {
								0.01f * (rand() % 3 - 1), // -0.01 to  0.01
								0.01f * (rand() % 3 - 1),
								0.01f * (rand() % 3 - 1)
							};

							// Diffrent rotation, -3 to +3 
							Vector rotationPerFrame = {
								(float)(rand() % 11 - 5),   // -5 to +5 grade n axel
								(float)(rand() % 11 - 5),
								(float)(rand() % 11 - 5)
							};

							// Diffrent rotation, -3 to +3 
							Vector scalePerFrame = {
								0.001f * (rand() % 3 - 1), // -0.001 to 0.001
								0.001f * (rand() % 3 - 1),
								0.001f * (rand() % 3 - 1)
							};

							//Diffretn offset 
							int offsetFrame = rand() % 200;

							char name[64];
							snprintf(name, sizeof(name), "cadillac_%d", instanceID++);


							//Add the diffrent cadilaci 
							add_obj_to_list(
								cadillacModel,
								name,
								instanceID,
								translate,
								zeroVector,
								cadillacScale2000,
								//zeroVector,//trans
								translationPerFrame,
								//zeroVector, //rotation
								rotationPerFrame,
								//zeroVector, //Scale 
								scalePerFrame,
								labPart1animationMaxLengthFrame,
								offsetFrame
							);
						
					}
				}
			}

			///PART 1

	}


	else{



		//Add models 
		add_obj_to_list(cadillacModel, "cardillac", 0, cardillacTranslate, cardillacRotation, cardillacScale, zeroVector, zeroVector, zeroVector, animationMaxLengthFrame, 0);


		//Add multi lamp after the road 
		float lampPlace = -200;
		for (int i = 0; i <= 2; i++)
		{
			Vector leftside = { -4.5, 1.0f, lampPlace };
			Vector rightside = { 4.0f, 1.0f, lampPlace };

			add_obj_to_list(lampModel, "lampLeft", 0, leftside, lampLefttRotation, lampScale, moveinZAxeln, zeroVector, zeroVector, animationMaxLengthFrame, 0);
			add_obj_to_list(lampModel, "lampRigt", 0, rightside, lampRightRotation, lampScale, moveinZAxeln, zeroVector, zeroVector, animationMaxLengthFrame, 0);
			lampPlace = lampPlace + 100.0f;
		}

		//Add multi Road sektions
		float roadPlace = -200;
		for (int i = 0; i <= 10; i++)
		{

			Vector roadTranslate = { 0.0f, -1.5f, roadPlace };
			add_obj_to_list(roadModel, "road", 0, roadTranslate, roadRotation, roadScale, moveinZAxeln, zeroVector, zeroVector, 192, 0);

			roadPlace = roadPlace + 24.0f;
		}


	
		//Add multi desert models 
		float desertplace = -200;
		for (int i = 0; i <= 11; i++)
		{

			Vector desertTranslateleft = { 13.5f, -1.7f, desertplace };
			Vector desertTranslateRight = { -13.5f, -1.7f, desertplace };
			Vector desertTranslateleftSecondRow = { 28.5f, -1.7f, desertplace };
			Vector desertTranslateRightSecondRow = { -28.5f, -1.7f, desertplace };
			add_obj_to_list(desertModel, "desert", 0, desertTranslateleft, desertRotation, desertScale, moveinZAxeln, zeroVector, zeroVector, 195, 0);
			add_obj_to_list(desertModel, "desert", 0, desertTranslateRight, desertRotation, desertScale, moveinZAxeln, zeroVector, zeroVector, 195, 0);

	
			add_obj_to_list(desertModel, "desert", 0, desertTranslateleftSecondRow, desertRotation, desertScale, moveinZAxeln, zeroVector, zeroVector, 195, 0);
			add_obj_to_list(desertModel, "desert", 0, desertTranslateRightSecondRow, desertRotation, desertScale, moveinZAxeln, zeroVector, zeroVector, 195, 0);

			desertplace = desertplace + 20.0f;
		}

	//Skybox
		add_obj_to_list(skyBoxModel, "skybox", 0, skyBoxTranslate, skyBoxRotation, skyBoxScale, zeroVector, zeroVector, zeroVector, animationMaxLengthFrame, 0);
	}



	//Prepare the objekt so all have right material, and value for the shader stor in it 
	for (int i = 0; i < objectCount; i++) {
		prepare_obj(objectArray[i].model, activeShaderProgram);
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



//Frame uppdate 
void Frameuppdate(int value) {


	currentFrame++;

	//To avoid over flow 
	if (currentFrame >= maxFrame) { currentFrame = 0; }


	glutPostRedisplay();

	
	glutTimerFunc(20, Frameuppdate, 0);

};





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




	glutTimerFunc(20, Frameuppdate, 0);
	

	init();
	glutMainLoop();

	cleanUp();
	return 0;
}


