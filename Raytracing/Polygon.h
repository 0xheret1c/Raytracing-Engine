#pragma once
#include <list>
#include "Vector.h"
#include "Material.h"
class Polygon
{
private:
	Vector a;
	Vector b;
	Vector c;
	Material material;

public:
	Polygon();
	Polygon(const Polygon& polygon);
	Polygon(double a[3], double b[3], double c[3]);
	Polygon(Vector verts[3]);
	Polygon(Vector a, Vector b, Vector c);
	void print();
};