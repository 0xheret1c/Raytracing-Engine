#include <stdio.h>
#include <iostream>
#include "./Core.h"


int main()
{
	Scene s;
	Polygon a[12];
	/*w‹RFEL*/
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

	
	double vals[3][3];
	vals[0][0] = 1;
	vals[0][1] = 2;
	vals[0][2] = 3;

	vals[1][0] = 4;
	vals[1][1] = 5;
	vals[1][2] = 6;

	vals[2][0] = 7;
	vals[2][1] = 8;
	vals[2][2] = 9;
	Matrix matrix = Matrix(3, 3, (double**)vals);
	matrix.print();
	s.addMesh(Mesh(a, 12));
	s.print();


	system("pause");
	return 0;
}