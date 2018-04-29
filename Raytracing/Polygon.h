#pragma once
#include <list>
#include "Vector.h"
class Polygon
{
private:
	Vector a;
	Vector b;
	Vector c;
public:
	Polygon(const Polygon& polygon);
	Polygon(double a[3], double b[3], double c[3]);
	Polygon(Vector verts[3]);
	Polygon(Vector a, Vector b, Vector c);
	void print();
};