#pragma once
#include <cstdlib>
#include <time.h>  
#include "Core.h"

#ifndef __OUR_MATH_H_INCLUDED__
#define __OUR_MATH_H_INCLUDED__

class Our_math
{
public:
	static inline double perlinNoise2(double x, double y)
	{
		int n = (int)x + (int)y * 57;
		n = (n << 13) ^ n;
		int nn = (n *(n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
		return 1.0 - ((double)nn / 1073741824.0);
	}

	static inline double clamp01(double val)
	{
		return (val < 0.0 ? 0.0 : (val > 1.0 ? 1.0 : val));
	}

};

#endif