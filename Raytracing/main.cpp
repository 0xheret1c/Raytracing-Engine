#include <stdio.h>
#include <iostream>
#include "./Core.h"

int main() 
{

	
	Scene s;

	s.addPolygon(Polygon(Vector(1, 2, 3), Vector(3, 2, 3), Vector(23, 2, 4)));
	s.addPolygon(Polygon(Vector(2, 5, 3), Vector(7, 6, 1), Vector(23, 2, 4)));
	s.addPolygon(Polygon(Vector(4, 4, 3), Vector(3, 2, 1), Vector(1, 423, 4)));
	s.addPolygon(Polygon(Vector(1.321, 2, 3), Vector(3, 2, 1), Vector(1, 2, 4)));
	s.addPolygon(Polygon(Vector(5, 23, 3), Vector(3, 2, 1), Vector(1, 43, 4)));
	s.addPolygon(Polygon(Vector(6, 12, 3), Vector(3, 6432, 1), Vector(1, 2, 4)));
	s.print();

	system("pause");
	return 0;
}