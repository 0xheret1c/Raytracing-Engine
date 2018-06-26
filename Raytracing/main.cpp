#define __DEBUG 1 // Debug mode

#include <stdio.h>
#include <iostream>
#include "./Core.h"
#include "Light.h"
#include "Primitive.h"
#include "e_colors.h"

//Prototype

void traceTest();
const unsigned int WIDTH =  700;
const unsigned int HEIGHT = 700;

using namespace Eigen;
int main(int argc, char* argv[])
{


	traceTest();

	
	system("pause");
	
	return 0;
}

void traceTest()
{
	std::string path = "C:\\Users\\Marius\\Documents\\GitHub\\Raytracing-Engine\\Meshes\\Pagoda_Ornamental.rtmsh";
	GFXOutput out = GFXOutput(WIDTH, HEIGHT);
	Scene scene = Scene();
	Camera cam = Camera(WIDTH, HEIGHT,_Transform(Vector3d(0, 0,-1),Vector3d(12, 0, 0)), &scene);
	//Mesh the cube
	Mesh mesh[] = { 
		Primitive::Cube(_Transform(Vector3d(0, -1 ,5),Vector3d(0,0,0), Vector3d(1, 0.25, 1)),Utils::getColor(e_Colors::blue)),
		Primitive::Cube(_Transform(Vector3d(0, -0.75 ,5),Vector3d(0,45,0), Vector3d(0.5, 0.25, 0.5)),Utils::getColor(e_Colors::chart_reuse)),
		Mesh::importFromRTMSH(path,_Transform(Vector3d(0, 0.5, 5),Vector3d(0,10,0), Vector3d(0.1,0.1,0.1)),Utils::getColor(e_Colors::red)),
		Primitive::Plane(_Transform(Vector3d(0,-1.125 ,0), Vector3d(0,0,0), Vector3d(500, 1, 500)),Utils::getColor(e_Colors::white))
	};
	Light light[1] =
	{
		Light(_Transform(Vector3d(0, 3, 0), Eigen::Vector3d(20, 45, 0)),Eigen::Vector3d(1337,1337,1337))
	};

	scene.camera = &cam;	
	scene.setLights(light, sizeof(light) / sizeof(Light));
	scene.setMeshes(mesh,  sizeof(mesh)  / sizeof(Mesh));
	SDL_Color** screen = cam.trace();
	out.setPixels(screen);
	out.initSDL();
	delete[] screen;
	//system("pause");
}