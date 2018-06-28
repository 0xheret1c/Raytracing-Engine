#pragma once
#include <cstdlib>
#include <time.h>  
#include "Core.h"
#include <SDL.h>
#include <Eigen\Core>


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
		if (val > 1)
		{
			return 1;
		}
		return val;
	}

	static Eigen::Quaterniond toQuat(Eigen::Vector3d rotation) {
		Eigen::Quaterniond rot;
		rot = Eigen::AngleAxisd(rotation.x() * (M_PI) / 180, Eigen::Vector3d::UnitX())
			* Eigen::AngleAxisd(rotation.y() * (M_PI) / 180, Eigen::Vector3d::UnitY())
			* Eigen::AngleAxisd(rotation.z() * (M_PI) / 180, Eigen::Vector3d::UnitZ());
		return rot;
	}

};

