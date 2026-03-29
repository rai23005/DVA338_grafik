#include "RayTracer.h"
#include "Vec3.h" 
#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480
RayTracer* initTracer(int width, int height)
{
	RayTracer* rayTracer = new RayTracer(width, height);
	
	// Vec3f(A, B, C), D);
	// A = x-coordinate
	// B = y- coordinate
	// C = z- coordinate
	// D =  Radius for the sphere 


	//The diffrent property for the material  
	Material blueMaterial(
		Vec3f(0.0f, 0.0f, 0.2f),   // ambient
		Vec3f(0.0f, 0.0f, 1.0f),   // diffuse
		Vec3f(0.3f, 0.3f, 0.3f),   // specular
		10.0f                     // shininess
	);

	Material redMaterial(
		Vec3f(0.2f, 0.0f, 0.0f),   // ambient
		Vec3f(1.0f, 0.0f, 0.0f),   // diffuse
		Vec3f(0.3f, 0.3f, 0.3f),   // specular
		16.0f                     // shininess
	);

	Material greenMaterial(
		Vec3f(0.0f, 0.2f, 0.0f),   // ambient
		Vec3f(0.0f, 1.0f, 0.0f),   // diffuse
		Vec3f(0.3f, 0.3f, 0.3f),   // specular
		64.0f                     // shininess
	);
	
	//Add two diffretn sphere to the image, red and one green
	rayTracer->addSphere(Vec3f(0.0f, 0.0f, -10.0f), 1.0f, redMaterial);
	rayTracer->addSphere(Vec3f(2.2f, 0.0f, -11.0f), 0.9f, greenMaterial);


	rayTracer->addSphere(Vec3f(2.2f, -100.0f, -40.0f), 90.9f, blueMaterial);
	
	//Add blue plane to the image
	//rayTracer->addPlane(Vec3f(0, -1, 0), Vec3f(0, 1, 0), blueMaterial);
	

	// Add a light sours 
	Light pointLight;
	pointLight.position = Vec3f(-10.0f, 10.0f, 10.0f);
	pointLight.color = Vec3f(0.7f, 0.7f, 1.0f);

	rayTracer->addLight(pointLight);


	return rayTracer;
}

void runTracer(RayTracer* tracer)
{
	tracer->fireRays();
	tracer->toPPM("DVA338_Raytracer_output.ppm");
	tracer->toBMP("DVA338_Raytracer_output.bmp");
}

void destroyTracer(RayTracer* tracer)
{
	delete tracer;
}

int main(int argc, char **argv) {
	RayTracer* tracer = initTracer(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	runTracer(tracer);
	destroyTracer(tracer);
	return 0;
}
