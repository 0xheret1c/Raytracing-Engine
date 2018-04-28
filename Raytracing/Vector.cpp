#include "Vector.h"
#include <stdlib.h> /*malloc, free*/


Vector::Vector(unsigned int _dimension)
{
	this->dimension = _dimension;
	this->components = (double*)malloc(sizeof(double) * _dimension);
	/*Null everything*/
	for (size_t i = 0; i < _dimension; i++)
	{
		this->components[i] = NULL;
	}
	
	return;
}

Vector::Vector(unsigned int _dimension, double* _components)
{
	this->dimension = _dimension;
	this->components = (double*)malloc(sizeof(double) * _dimension);

	/*Copy "_components" into components*/
	for (size_t i = 0; i < _dimension; i++)
	{
		this->components[i] = _components[i];
	}

	return;
}

Vector Vector::operator+(Vector &right)
{	
	Vector d = Vector(this->dimension);
	for (size_t i = 0; i < this->dimension; i++)
	{
		d.components[i] = this->components[i] + right.components[i];
	}
	return d;
}

void Vector::operator+=(Vector &right)
{
	for (size_t i = 0; i < this->dimension; i++)
	{
		this->components[i] += right.components[i];
	}
	return;
}

Vector Vector::operator-(Vector &right)
{
	Vector d = Vector(this->dimension);
	for (size_t i = 0; i < this->dimension; i++)
	{
		d.components[i] = this->components[i] - right.components[i];
	}
	return d;
}

void Vector::operator-=(Vector &right)
{
	for (size_t i = 0; i < this->dimension; i++)
	{
		this->components[i] -= right.components[i];
	}
	return;
}

Vector Vector::operator*(double right)
{
	Vector d = Vector(this->dimension);
	for (size_t i = 0; i < this->dimension; i++)
	{
		d.components[i] = this->components[i] * right;
	}
	return d;
}

void Vector::operator*=(double right)
{
	for (size_t i = 0; i < this->dimension; i++)
	{
		this->components[i] *= right;
	}
	return;
}


Vector::~Vector() 
{
	free(this->components);

	return;
}