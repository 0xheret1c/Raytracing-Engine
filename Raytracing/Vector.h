#pragma once
class Vector
{
private:
	unsigned int dimension;
public:
	double* components;
	unsigned int GetDimension();
	Vector();
	Vector(Vector& vector);
	Vector(unsigned int dimension);
	Vector(unsigned int dimension, double* components);
	~Vector();
	Vector operator+(const Vector& right);
	void operator+=(const Vector& right);
	Vector operator-(const Vector& right);
	void operator-=(const Vector& right);
	Vector operator*(const double& right);
	void operator*=(const double& right);
}; 
