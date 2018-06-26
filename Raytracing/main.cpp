#define __DEBUG 1 // Debug mode

#include <stdio.h>
#include <iostream>
#include "./Core.h"
#include "Light.h"
#include "Primitive.h"
#include "Material.h"
#include "e_colors.h"

//Prototype

void traceTest();
const unsigned int WIDTH =  1920;
const unsigned int HEIGHT = 1080;
const size_t density = 3;
const size_t bounces = 3;

using namespace Eigen;
int main(int argc, char* argv[])
{
	traceTest();

	
	system("pause");
	
	return 0;
}

void traceTest()
{
	std::string path = "F:\\Arbeit\\Uni\\raytrace\\Raytracing-Engine\\Meshes\\Pagoda_Ornamental.rtmsh";
	GFXOutput out = GFXOutput(WIDTH, HEIGHT);
	Scene scene = Scene();
	
	//Materials
	Material mirror = Material(Utils::getColor(235,255,235), 0.85);
	Material satinRed = Material(Utils::getColor(0xFF0000), 0.05);
	Material metallicBlue = Material(Utils::getColor(0x0000FF), 0.45);
	Material metallicWhite = Material(Utils::getColor(0xFFFFFF), 0.20);
	Material shinyGreen = Material(Utils::getColor(0x00FF00), 0.2);
	
	//Cam
	Camera cam = Camera(WIDTH, HEIGHT,_Transform(Vector3d(0, 0, 2),Vector3d(12, 0, 0)), &scene);
	cam.setDensity(density);
	cam.setMaxBounces(bounces);
	//Mesh the cube
	Mesh mesh[] = {
		Primitive::Cube(_Transform(Vector3d(-1.5, -1 ,6),Vector3d(0,35,0), Vector3d(0.05,2.5, 2.5)),mirror),
		Primitive::Cube(_Transform(Vector3d(1.5, -1 ,6),Vector3d(0,-35,0), Vector3d(0.05,2.5, 2.5)),mirror),
		Primitive::Cube(_Transform(Vector3d(0, -1 ,5),Vector3d(0,0,0), Vector3d(1, 0.25, 1)),satinRed),
		Primitive::Cube(_Transform(Vector3d(0, -0.75 ,5),Vector3d(0,32,0), Vector3d(0.85, 0.25, 0.85)),shinyGreen),
		Mesh::importFromRTMSH(path,_Transform(Vector3d(0, -0.65, 5),Vector3d(0,31,0), Vector3d(0.07,0.07,0.07)),satinRed),
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