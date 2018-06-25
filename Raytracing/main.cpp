#define __DEBUG 1 // Debug mode

#include <stdio.h>
#include <iostream>
#include "./Core.h"
#include "Light.h"
#include "Primitive.h"
#include "e_colors.h"

//Prototype
void traceTest();
const unsigned int WIDTH =  1000;
const unsigned int HEIGHT = 800;
using namespace Eigen;
int main(int argc, char* argv[])
{

	/*SDL_Color c;
	c.r = 255;
	c.a = 255;
	c.g = 255;
	c.b = 255;
	Scene scene = Scene();
	Vector3d verts[3];
	verts[0] = Vector3d(0, 0, 1);
	verts[1] = Vector3d(0, 1, 1);
	verts[2] = Vector3d(1, 0, 1);
	size_t tri[] = {1,2,3};
	Mesh mesh[] = { Mesh(verts,tri,3,_Transform(),c)};
	scene.setMeshes(mesh,1);
	Ray r = Ray(Vector3d(0.1, 0.1, -1), Vector3d(0, 0, 1));
	
	Triangle t = Triangle(verts[0], verts[1], verts[2]);


	if (scene.intersects(r,&RaycastHit()))
	{
		std::cout << "hit" << std::endl;
	}
	else
	{
		std::cout << "shit" << std::endl;
	}
	*/
	traceTest();

	system("pause");
	return 0;
}

void traceTest()
{
	GFXOutput out = GFXOutput(WIDTH, HEIGHT);

	Scene scene = Scene();

	Camera cam = Camera(WIDTH, HEIGHT,_Transform(Vector3d(0, 1,-2),Vector3d(12, 0, 0)), &scene);
	//Mesh the cube
	Mesh mesh[] = { 
		Primitive::Cube(_Transform(Vector3d(0, -1 ,5),Vector3d(0,0,0), Vector3d(1, 0.25, 1)),Utils::getColor(e_Colors::blue)),
		Primitive::Cube(_Transform(Vector3d(0, -0.75 ,5),Vector3d(0,45,0), Vector3d(0.5, 0.25, 0.5)),Utils::getColor(e_Colors::chart_reuse)),
		Primitive::Pyramid(_Transform(Vector3d(0, -0.65, 5),Vector3d(0,10,0), Vector3d(0.30,0.30,0.30)),Utils::getColor(e_Colors::red)),
		Primitive::Plane(_Transform(Vector3d(0,-1.125 ,0), Vector3d(0,0,0), Vector3d(500, 1, 500)),Utils::getColor(e_Colors::white))
	};
	Light light[1] =
	{
		Light(_Transform(Vector3d(0, 3, 0), Eigen::Vector3d(20, 45, 0)),Eigen::Vector3d(1337,1337,1337))
	};

	
	scene.camera = &cam;	//set cam
	scene.setLights(light, 1);
	scene.setMeshes(mesh,4);
	SDL_Color** screen = cam.trace();
	out.setPixels(screen);
	out.initSDL();
	delete[] screen;
	//system("pause");
}