#pragma once
class Matrix 
{
private:
	const unsigned int height;
	const unsigned int width;
	double** matrix;
	void allocate(const int height, const int width);

public:
	Matrix(const unsigned int height, unsigned const int width);
	Matrix(const unsigned int height, unsigned const int width, double** values);
	~Matrix();
	void setValue(unsigned int y, unsigned int x,double value);
	double getValue(unsigned int y, unsigned  int x);
	unsigned int getHeight();
	unsigned int getWidth();
	void setMatrix(double** values);
	void print();

};