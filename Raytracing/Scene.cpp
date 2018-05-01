#include "./Scene.h"
#include "./Mesh.h"
#include "./Polygon.h"
#include <iostream>

void Scene::addMesh(Mesh mesh)
{
	this->objects.push_back(mesh);
}

void Scene::addPolygon(Polygon polygon)
{
	Polygon temp[1];
	Mesh mesh = Mesh(temp, 1);
	this->addMesh(mesh);
}



void Scene::print() 
{
	for (std::list<Mesh>::iterator it = this->objects.begin(); it != this->objects.end(); ++it) 
	{
		it->print();
	}
}