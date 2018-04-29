#include "Vector.h"
#include <iostream>
/*Constructor*/
Vector::Vector()
{

	this->x = 0;
	this->y = 0;
	this->z = 0;

	return;
}
Vector::Vector(double components[3])
{

	this->x = components[0];
	this->y = components[1];
	this->z = components[2];

	return;
}

Vector::Vector(Vector& vector) 
{
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
}

/*Functions*/
void Vector::print() 
{
	std::cout << "(" << this->x << " | " << this->y << " | " << this->z << ")" << std::endl;
}

/*Operators*/
Vector Vector::operator+(const Vector  &right)
{	
	Vector d;
	d.x = this->x + right.x;
	d.y = this->y + right.y;
	d.z = this->z + right.z;
	
	return d;
}

void Vector::operator+=(const Vector &right)
{
	this->x = right.x;
	this->y = right.y;
	this->z = right.z;
	
	return;
}

Vector Vector::operator-(const Vector &right)
{
	Vector d;
	d.x = this->x - right.x;
	d.y = this->y - right.y;
	d.z = this->z - right.z;
	return d;
}

void Vector::operator-=(const Vector &right)
{
	this->x -= right.x;
	this->y -= right.y;
	this->z -= right.z;

	return;
}

Vector Vector::operator*(const double& right)
{
	Vector d;
	d.x = this->x * right;
	d.y = this->y * right;
	d.z = this->z * right;
	return d;
}

void Vector::operator*=(const double& right)
{
	this->x *= right;
	this->y *= right;
	this->z *= right;

	return;
}

