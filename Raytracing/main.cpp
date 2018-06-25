#define __DEBUG 1 // Debug mode

#include <stdio.h>
#include <iostream>
#include "./Core.h"
#include "Light.h"
#include "Primitive.h"

//Prototype
void traceTest();
const unsigned int WIDTH = 1920*2;
const unsigned int HEIGHT = 1000;
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

	Camera cam = Camera(WIDTH, HEIGHT,_Transform(Vector3d(0, 0, 0),Vector3d(00, 00, 00)), &scene);
	//Mesh the cube
	SDL_Color c;
	c.r = 255;
	c.g = 100;
	c.b = 10;
	Mesh mesh[] = { 
		Primitive::Cube(_Transform(Vector3d(0, -1 ,5),Vector3d(0,2,32)),c),
		Primitive::Cube(_Transform(Vector3d(-1, -1 ,6),Vector3d(0,42,2)),c),
		Primitive::Cube(_Transform(Vector3d(-2.5, -1 ,7.5),Vector3d(0,11,-52)),c),
		Primitive::Plane(_Transform(Vector3d(0,-1.5 ,0)),c) 
	};
	Light light[1] =
	{
		Light(_Transform(Vector3d(0, 3, 0), Eigen::Vector3d(45, -30, 0)),Eigen::Vector3d(1337,1337,1337))
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