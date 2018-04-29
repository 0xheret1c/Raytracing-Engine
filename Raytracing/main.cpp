#include <stdio.h>

#include <iostream>
#include "./Core.h"

int main() 
{

	double d[3] = { 1,2,3 };

	Vector a = Vector(d);
	Vector b = Vector(d);
	Vector c = Vector(a);
	a += b;
	a.print();
	a = a + c;
	a.print();

	system("pause");
	return 0;
}