
#include <stdio.h>
#include <iostream>
#include "./Core.h"
#include "Scene.h"

int main(int argc, char* argv[])
{
	GFXOutput out = GFXOutput(800, 480);
	Scene scene = Scene();
	Camera cam = Camera(_Transform(), scene);
	scene.camera = cam;
	Eigen::Vector3d verts[8 * 3] = 
	{ 
		Eigen::Vector3d(0.5,-0.5,0.5),
		Eigen::Vector3d(-0.5,-0.5,0.5),
		Eigen::Vector3d(0.5,0.5,0.5),
		Eigen::Vector3d(-0.5,0.5,0.5),
		Eigen::Vector3d(0.5,0.5,-0.5),
		Eigen::Vector3d(-0.5,0.5,-0.5),
		Eigen::Vector3d(0.5,-0.5,-0.5),
		Eigen::Vector3d(-0.5,-0.5,-0.5),
		Eigen::Vector3d(0.5,0.5,0.5),
		Eigen::Vector3d(-0.5,0.5,0.5),
		Eigen::Vector3d(0.5,0.5,-0.5),
		Eigen::Vector3d(-0.5,0.5,-0.5),
		Eigen::Vector3d(0.5,-0.5,-0.5),
		Eigen::Vector3d(0.5,-0.5,0.5),
		Eigen::Vector3d(-0.5,-0.5,0.5),
		Eigen::Vector3d(-0.5,-0.5,-0.5),
		Eigen::Vector3d(-0.5,-0.5,0.5),
		Eigen::Vector3d(-0.5,0.5,0.5),
		Eigen::Vector3d(-0.5,0.5,-0.5),
		Eigen::Vector3d(-0.5,-0.5,-0.5),
		Eigen::Vector3d(0.5,-0.5,-0.5),
		Eigen::Vector3d(0.5,0.5,-0.5),
		Eigen::Vector3d(0.5,0.5,0.5),
		Eigen::Vector3d(0.5,-0.5,0.5),
	};
	
	size_t triangles[36] =
	{
		0,2,3,0,3,1,8,4,5,8,5,9,10,6,7,10,7,11,12,13,14,12,14,15,16,17,18,16,18,19,20,21,22,20,22,23
	};

	SDL_Color c;
	c.r = 255;
	c.g = 100;
	c.b = 10;
	Mesh mesh[1] = 
	{ Mesh(verts, triangles,
		_Transform(Eigen::Vector3d(0, 0, 5), Eigen::Vector3d(0, 0, 0), Eigen::Vector3d(0, 0, 0)),
		c) };
	scene.meshes = mesh;
	Light light[1] = 
	{ 
		Light(_Transform(Eigen::Vector3d(0, 3, 0), Eigen::Vector3d(0, 0, 0), Eigen::Vector3d(0, 0, 0)),Eigen::Vector3d(1337,1337,1337),scene)
	};
	scene.lights = light;
	
	out.setPixels(cam.trace());
	out.printScreen();

	system("pause");
	return 0;
}