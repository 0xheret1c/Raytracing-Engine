#include "./Mesh.h"
#include "./Polygon.h"
#include<iostream>
#include<fstream>
#include <algorithm>

void Mesh::print()
{
    for (std::list<Polygon>::iterator it = this->polygons.begin(); it != this->polygons.end(); ++it) 
	{
		it->print();
	}
}

Mesh::Mesh(Polygon* polygons, size_t polyCount)
{
	for (size_t i = 0; i < polyCount; i++)
	{
		this->polygons.push_back(polygons[i]);
	}
}

Polygon* Mesh::toArray()
{
	size_t size = polygons.size();
	Polygon* ret = new Polygon[size];
	for(size_t i = 0; i < size; i++)
	{
		
	}
	return nullptr;
}

static Mesh fromRTM(char* path, Vector pos, double scale) 
{

}
