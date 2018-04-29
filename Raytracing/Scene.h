#pragma once
#include <stdlib.h>
#include <list>
#include "./Polygon.h"

class Scene
{
private:
	std::list<Polygon> objects;
public:
	void addPolygon(Polygon polygon);
	//void addMesh(Mesh mesh);
	void print();
};