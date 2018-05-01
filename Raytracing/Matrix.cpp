#include "./Matrix.h"
#include <iostream>

Matrix::Matrix(const unsigned int _height, const unsigned  int _width) : height(_height), width(_width)
{
	allocate(_height, _width);
}

Matrix::Matrix(const unsigned int _height, const unsigned int _width, double** values) : height(_height), width(_width)
{
	allocate(_height, _width);
	for (size_t y = 0; y < _height; y++)
	{
		for (size_t x = 0;x < _width; x++)
		{
			this->setValue(y, x, values[y][x]);
		}
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < this->height;i++)
	{
		delete[] this->matrix[i];
	}
	delete[] this->matrix;
}

void Matrix::allocate(const int _height, const int _width) 
{
	this->matrix = new double*[_height];
	for (int i = 0; i < _height; i++)
	{
		this->matrix[i] = new double[_width];
	}
}

void Matrix::print() 
{
	for (size_t y = 0; y < this->height; y++)
	{
		for (size_t x = 0; x <  this->width; x++)
		{
			std::cout << this->matrix[y][x] << " ";
		}
		std::cout << std::endl;
	}
}

void Matrix::setValue(unsigned int y,unsigned int x, double value) 
{
	if (y > this->height - 1){ return; /*error*/}
	if (x > this->width - 1) { return;/*error*/ }

	this->matrix[y][x] = value;
}

double Matrix::getValue(unsigned int y, unsigned int x)
{
	if (y > this->height - 1) { return NULL; /*error*/ }
	if (x > this->width - 1) { return NULL;/*error*/ }
	return this->matrix[y][x];
}

unsigned int Matrix::getHeight()
{
	return this->height;
}
unsigned int Matrix::getWidth() 
{
	return this->width;
}

void Matrix::setMatrix(double** values) 
{
	for (size_t y = 0; y < this->height; y++)
	{
		for (size_t x = 0; x < this->width; x++)
		{
			this->matrix[y][x] = values[y][x];
		}
	}
}
