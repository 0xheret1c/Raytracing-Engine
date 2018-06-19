#pragma once
#include <cstdlib>
#include <time.h>  
class Utils
{
public:
	static double** allocate2DArray(unsigned int width, unsigned int height);
	static void delete2DArray(unsigned int width, unsigned int height, double** _array);
	static int _rand(int min, int max);
};

int Utils::_rand(int min, int max)
{


	int random = std::rand() % max + min;
	return random;
}

double** Utils::allocate2DArray(unsigned int width, unsigned int height)
{
	double** ret = new double*[height];
	for (size_t i = 0; i < height; i++)
	{
		ret[i] = new double[width];
	}
	return ret;
}
void Utils::delete2DArray(unsigned int width, unsigned int height, double** _array)
{
	for (size_t i = 0; i < height; i++)
	{
		delete[] _array[i];
	}
	delete[] _array;
}