#pragma once
class Vector
{
public:
	/*Vars*/
	double x;
	double y;
	double z;
	/*Functions*/
	void print();
	/*Constructor*/
	Vector(Vector& vector);
	Vector();
	Vector(double components[3]);
	/*Operators*/
	Vector operator+(const Vector& right);
	void operator+=(const Vector& right);
	Vector operator-(const Vector& right);
	void operator-=(const Vector& right);
	Vector operator*(const double& right);
	void operator*=(const double& right);
}; 
