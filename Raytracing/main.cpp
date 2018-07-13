#define __DEBUG 1 // Debug mode

#include <stdio.h>
#include <vector>
#include <iostream>
#include "./Core.h"
#include "Light.h"
#include "Primitive.h"
#include "Material.h"
#include "e_colors.h"
#include "Renderer.h"
#include "Importer.h"

//Prototype

void traceTest();

const unsigned int WIDTH =  1000;
const unsigned int HEIGHT = 1000;
const size_t density = 1;
const size_t bounces = 2;

using namespace Eigen;
int main(int argc, char* argv[])
{
	traceTest();

	return 0;
}

void traceTest()
{
	//int array_size = 0;
	//std::vector<Mesh> meshes = Mesh::importScene(array_size, "C:\\Users\\HInde\\OneDrive\\Dokumente\\scene.rtsc");
	//std::string path = ".\\Meshes\\";
	//Scene scene = Scene();
	
	//Materials
	/*Material mirror = Material(Utils::getColor(0x000500), 0.8);
	Material satinRed = Material(Utils::getColor(0xFF0000), 0.05);
	Material metallicBlue = Material(Utils::getColor(0x0000FF), 0.45);
	Material metallicWhite = Material(Utils::getColor(0xFFFFFF), 0.20);
	Material stone = Material(Utils::getColor(e_Colors::light_steel_blue), 0.01);
	Material shinyGreen = Material(Utils::getColor(0x00FF00), 0.45);*/

	
	//Cam
	/*Camera cam = Camera(WIDTH, HEIGHT,_Transform(Vector3d(0, 2, -7),Vector3d(0, 0, 0)), &scene);
	cam.setDensity(density);
	cam.setMaxBounces(bounces);
	Light light[1] =
	{
		Light(_Transform(Vector3d(0, 3, 0), Eigen::Vector3d(20, 45, 0)),Eigen::Vector3d(1337,1337,1337))
	};
	scene.setLights(light, sizeof(light) / sizeof(Light));*/
	//Mesh the cube

	//scene.camera = &cam;
	//scene.setMeshes(meshes, array_size);
	

	//meshes[0].toString();
	
	GFXOutput out = GFXOutput(WIDTH, HEIGHT);
	Scene scene = Importer::importScene("C:\\Users\\HInde\\OneDrive\\Dokumente\\scene.rtsc", WIDTH, HEIGHT, density, bounces);
	SDL_Color** screen = Renderer::render(&scene);
	out.setPixels(screen);

	out.initSDL();




	
	//delete[] screen;
}