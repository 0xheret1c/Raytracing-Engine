#include "./Scene.h"
#include "./Mesh.h"
#include <iostream>

void Scene::addMesh(Mesh mesh)
{
	this->objects.push_back(mesh);
}

void Scene::addPolygon(Polygon polygon)
{
	Polygon* temp = new Polygon[1];
	temp[0] = polygon;
	Mesh mesh = Mesh(temp,1);
	this->addMesh(mesh);
	delete[] temp;
	
}

void Scene::print() 
{
	for (std::list<Mesh>::iterator it = this->objects.begin(); it != this->objects.end(); ++it) 
	{
		it->print();
	}
}