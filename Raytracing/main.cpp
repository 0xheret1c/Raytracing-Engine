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
#include "Menu.h"

//Prototype

void traceTest();

const unsigned int WIDTH =  1000;
const unsigned int HEIGHT = 750;
const size_t density = 1;
const size_t bounces = 2;

using namespace Eigen;

std::string menu()
{
	std::string header = "\t=== RAYTRACER ===\r\n";
	std::string message = header + "Select the scene you want to render.\r\nPress arrow up and down to navigate and enter to confirm.";
	std::vector<std::string> fileNames = Importer::getFileNames(".\\Scenes");
	std::string* elements = &fileNames[0];
	size_t elementsc = fileNames.size();
	int areYouSure = 0;
	int selection = 0;
	do
	{
		selection = Menu::menu(message, elements, elementsc, 200);
		areYouSure = Menu::yesOrNo(header + "Do you want to render \"" + elements[selection] + "\"? This might take some time.",200);
	}
	while(areYouSure != 1);
	return ".\\Scenes\\" + fileNames[selection];
}

int main(int argc, char* argv[])
{
	
	
	std::string sceneToRender = menu();
	GFXOutput out = GFXOutput(WIDTH, HEIGHT);
	Scene scene = Importer::importScene(sceneToRender, WIDTH, HEIGHT, density, bounces);
	SDL_Color** screen = Renderer::render(&scene);
	out.setPixels(screen);
	out.initSDL();
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
	
	
	//delete[] screen;
}