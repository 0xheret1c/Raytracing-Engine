#include <stdio.h>

#include <iostream>
#include "./Vector.h"

int main() 
{
	double d[3] = { 1,2,3 };
	Vector a = Vector(3,d);
	Vector b = Vector(3,d);
	a = a+b;
	std::cout << b.components[2] << std::endl;
	a -= b;
	std::cout << b.components[2] << std::endl;
	a *= 5;
	std::cout << b.components[2] << std::endl;

	system("pause");
	return 0;
}