
#include <stdio.h>
#include <iostream>
#include "./Core.h"

int main(int argc, char* argv[])
{

	Scene s;
	GFXOutput out = GFXOutput(640,480);
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

	

	s.addMesh(Mesh(a, 12));
	//s.print();
	
	while (true)
	{
		out.setPixels();
		out.printScreen();
	}

	system("pause");
	return 0;
}