#pragma once
#include <cstdlib>
#include <time.h>  
#include <iostream>
#include <SDL.h>


#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__

class Utils
{
public:
	static void LOG(const char* message)
	{
#ifdef __DEBUG
		std::cout << message << std::endl;
#endif // DEBUG
	}
	static double** allocate2DArray(unsigned int width, unsigned int height)
	{
		double** ret = new double*[height];
		for (size_t i = 0; i < height; i++)
		{
			ret[i] = new double[width];
		}
		return ret;
	}
	static void delete2DArray(unsigned int width, unsigned int height, double** _array)
	{
		for (size_t i = 0; i < height; i++)
		{
			delete[] _array[i];
		}
		delete[] _array;
	}
	static int _rand(int min, int max)
	{

		int random = std::rand() % max + min;
		return random;
	}

	static SDL_Color getColor(Uint8 r, Uint8 g, Uint8 b)
	{
		SDL_Color color;
		color.a = 0xFF;
		color.r = r;
		color.g = g;
		color.b = b;
		return color;
	}

};
#endif