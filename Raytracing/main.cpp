
#include <stdio.h>
#include <iostream>
#include "./Core.h"
#include "SDL.h"

int main(int argc, char* argv[])
{



	Scene s;
	Polygon a[12];
	/*WÜRFEL*/
	a[0] = Polygon(Vector(10, 0, 0), Vector(1, -10, 0), Vector(10, -10, 10));
	a[1] = Polygon(Vector(10, 0, 0), Vector(10, 0, 10), Vector(10, -10, 10));

	a[3] = Polygon(Vector(20, 0, 0), Vector(20, -10, 0), Vector(20, -10, 10));
	a[3] = Polygon(Vector(20, 0, 0), Vector(20, 0, 10), Vector(20, -10, 10));

	a[4] = Polygon(Vector(10, -10, 10), Vector(10, -10, 0), Vector(20, -10, 0));
	a[5] = Polygon(Vector(10, -10, 10), Vector(20, -10, 10), Vector(20, -10, 0));

	a[6] = Polygon(Vector(10, 0, 10), Vector(10, 0, 0), Vector(20, 0, 0));
	a[7] = Polygon(Vector(10, 0, 10), Vector(20, 0, 10), Vector(20, 0, 0));

	a[8] = Polygon(Vector(10, 0, 0), Vector(10, -10, 0), Vector(20, 0, 0));
	a[9] = Polygon(Vector(20, -10, 0), Vector(10, -10, 0), Vector(20, 0, 0));

	a[10] = Polygon(Vector(10, 0, 10), Vector(10, -10, 10), Vector(20, 0, 10));
	a[11] = Polygon(Vector(20, -10, 10), Vector(10, -10, 10), Vector(20, 0, 10));

	
	
	Matrix matrix = Matrix(3, 3);
	matrix.setValue(0, 0, 1);
	matrix.setValue(0, 1, 2);
	matrix.setValue(0, 2, 3);
	matrix.setValue(1, 0, 4);
	matrix.setValue(1, 1, 5);
	matrix.setValue(1, 2, 6);
	matrix.setValue(2, 0, 7);
	matrix.setValue(2, 1, 8);
	matrix.setValue(2, 2, 9);
	matrix.print();
	s.addMesh(Mesh(a, 12));
	s.print();

	SDL_Init(SDL_INIT_EVERYTHING);
	system("pause");
	return 0;
}