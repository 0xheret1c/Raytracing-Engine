#include "Vector.h"
#include <iostream>
Vector::Vector()
{
	this->dimension = 3;
	this->components = new double[3];
	/*Null everything*/
	for (size_t i = 0; i < 3; i++)
	{
		this->components[i] = 0;
	}

	return;
}

Vector::Vector(Vector& vector) 
{
	
	this->dimension = vector.GetDimension(); 
	this->components = new double[this->dimension];
	for (size_t i = 0; i < this->dimension; i++)
	{
		this->components[i] = vector.components[i];
	}
}

unsigned int Vector::GetDimension() 
{
	return this->dimension;
}

Vector::Vector(unsigned int _dimension)
{
	this->dimension = _dimension;
	this->components = new double[_dimension];
	/*Null everything*/
	for (size_t i = 0; i < _dimension; i++)
	{
		this->components[i] = 0;
	}
	
	return;
}

Vector::Vector(unsigned int _dimension, double* _components)
{
	this->dimension = _dimension;
	this->components = new double[_dimension];

	/*Copy "_components" into components*/
	for (size_t i = 0; i < _dimension; i++)
	{
		this->components[i] = _components[i];
	}

	return;
}

Vector Vector::operator+(const Vector &right)
{	
	Vector d = Vector(this->dimension);
	for (size_t i = 0; i < this->dimension; i++)
	{
		d.components[i] = this->components[i] + right.components[i];
	}

	return d;
}

void Vector::operator+=(const Vector &right)
{
	for (size_t i = 0; i < this->dimension; i++)
	{
		this->components[i] += right.components[i];
	}
	return;
}

Vector Vector::operator-(const Vector &right)
{
	Vector d = Vector(this->dimension);
	for (size_t i = 0; i < this->dimension; i++)
	{
		d.components[i] = this->components[i] - right.components[i];
	}
	return d;
}

void Vector::operator-=(const Vector &right)
{
	for (size_t i = 0; i < this->dimension; i++)
	{
		this->components[i] -= right.components[i];
	}
	return;
}

Vector Vector::operator*(const double& right)
{
	Vector d = Vector(this->dimension);
	for (size_t i = 0; i < this->dimension; i++)
	{
		d.components[i] = this->components[i] * right;
	}
	return d;
}

void Vector::operator*=(const double& right)
{
	for (size_t i = 0; i < this->dimension; i++)
	{
		this->components[i] *= right;
	}
	return;
}

Vector::~Vector() 
{
	delete[] this->components;
	return;
}