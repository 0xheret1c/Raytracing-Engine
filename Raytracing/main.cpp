#include <stdio.h>

#include <iostream>
#include "./Core.h"

int main() 
{

	double d[3] = { 1,2,3 };

	Vector a = Vector(3,d);

	Vector b = Vector(3, d);
	Vector c = Vector(a);

	std::cout << c.components[2] << std::endl;
	a = a+b;
	std::cout << a.components[2] << std::endl;
	a -= b;
	std::cout << a.components[2] << std::endl;
	a *= 5;
	std::cout << a.components[2] << std::endl;

	system("pause");
	return 0;
}