#pragma once
class Vector
{
private:
	unsigned int dimension;
public:
	double* components;
	unsigned int getDimension();
	Vector(unsigned int dimension);
	Vector(unsigned int dimension, double* components);
	~Vector();
	Vector operator+(Vector& right);
	void operator+=(Vector& right);
	Vector operator-(Vector& right);
	void operator-=(Vector& right);
	Vector operator*(double right);
	void operator*=(double right);
}; 
