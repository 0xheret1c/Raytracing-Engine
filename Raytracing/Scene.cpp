#include "./Scene.h"
#include "./Polygon.h"
#include <iostream>

void Scene::addPolygon(Polygon polygon)
{
	this->objects.push_back(polygon);
}



void Scene::print() 
{
	for (std::list<Polygon>::iterator it = objects.begin(); it != objects.end(); ++it) 
	{
		it->print();
	}
}