#pragma once
#include <stdlib.h>
#include <list>
#include "./Mesh.h"

class Scene
{
private:
	std::list<Mesh> objects;
public:

	void addMesh(Mesh mesh);
	void addPolygon(Polygon polygon);
	void print();
};