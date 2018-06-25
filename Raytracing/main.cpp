#define __DEBUG 1 // Debug mode

#include <stdio.h>
#include <iostream>
#include "./Core.h"
#include "Light.h"
#include "Primitive.h"

//Prototype
void traceTest();
const unsigned int WIDTH =  950;
const unsigned int HEIGHT = 950;
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

	Camera cam = Camera(WIDTH, HEIGHT,_Transform(Vector3d(-1, 1.2,-2),Vector3d(12, 00, 00)), &scene);
	//Mesh the cube
	Mesh mesh[] = { 
		Primitive::Cube(_Transform(Vector3d(0, 0.5 ,5),Vector3d(0,2,32)),Utils::getColor(0xFF0000)),
		Primitive::Cube(_Transform(Vector3d(-1, 1.25 ,6),Vector3d(22,42,2)),Utils::getColor(0x00FF00)),
		Primitive::Cube(_Transform(Vector3d(-2.5, -1 ,7.5),Vector3d(45,45,45)),Utils::getColor(0x0000FF)),
		Primitive::Plane(_Transform(Vector3d(0,-1.5 ,0)),Utils::getColor(0xFFFFFF)) 
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