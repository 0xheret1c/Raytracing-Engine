#include "./Polygon.h"
#include <iostream>

Polygon::Polygon()
{
	this->a.x = NULL;
	this->a.y = NULL;
	this->a.z = NULL;
	this->b.x = NULL;
	this->b.y = NULL;
	this->b.z = NULL;
	this->c.x = NULL;
	this->c.y = NULL;
	this->c.z = NULL;
}

Polygon::Polygon(Vector verts[3])
{
	this->a = verts[0];
	this->b = verts[1];
	this->c = verts[2];
}

Polygon::Polygon(double a[3], double b[3], double c[3])
{
	this->a = Vector(a);
	this->b = Vector(b);
	this->c = Vector(c);
}

Polygon::Polygon(const Polygon& polygon)
{
	this->a = polygon.a;
	this->b = polygon.b;
	this->c = polygon.c;
}

Polygon::Polygon(Vector a, Vector b, Vector c)
{
	this->a = Vector(a);
	this->b = Vector(b);
	this->c = Vector(c);
}

void Polygon::print() 
{
	std::cout << "POLYGON:" << std::endl;
	std::cout << "\t";
	this->a.print();
	std::cout << "\t";
	this->b.print();
	std::cout << "\t";
	this->c.print();
	
}

