#pragma once
class Utils
{
	static double** allocate2DArray(unsigned int width, unsigned int height);
	static void delete2DArray(unsigned int width, unsigned int height, double** _array);
};

double** Utils::allocate2DArray(unsigned int width, unsigned int height)
{
	double** ret = new double*[height];
	for (int i = 0; i < height; i++)
	{
		ret[i] = new double[width];
	}
	return ret;
}
void Utils::delete2DArray(unsigned int width, unsigned int height, double** _array)
{
	for (int i = 0; i < height; i++)
	{
		delete[] _array[i];
	}
	delete[] _array;
}