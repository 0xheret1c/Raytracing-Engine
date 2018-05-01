#pragma once
#include <list>
#include "./Polygon.h"
class Mesh
{
private:
    std::list<Polygon> polygons;
public:
	Mesh(Polygon* polygons, size_t polyCount);

    void print();
	static Mesh fromRTM(char* path, Vector pos, double scale);
};