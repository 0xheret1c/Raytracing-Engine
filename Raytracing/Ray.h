#pragma once
#include "Core.h"


class Ray
{
private:
	Scene scene;
public:
	Eigen::Vector3d origin;
	Eigen::Vector3d direction;

	Ray(Eigen::Vector3d _origin, Eigen::Vector3d _dir, Scene _scene)
	{
		scene = _scene;
		origin = _origin;
		direction = _dir;
	}
	Ray()
	{
	}
};