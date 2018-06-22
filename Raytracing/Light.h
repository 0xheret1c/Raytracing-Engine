#pragma once
#include "Core.h"

#ifndef __LIGHT_H_INCLUDED__
#define __LIGHT_H_INCLUDED__
class Light
{
private:

public:
	_Transform transform;
	Eigen::Vector3d direction;
	Scene scene;

	Light(){}
	Light(_Transform _transform, Eigen::Vector3d _direction, Scene _scene)
	{
		transform = _transform;
		direction = _direction;
		scene = _scene;
	}

	double calculateLightIntensity(Eigen::Vector3d origin,Triangle* ignore = nullptr)
	{
		RaycastHit hit;
		Ray ray = Ray(origin, transform.position - origin, scene);
		if (scene.intersects(ray, hit, ignore))
		{
			return scene.globalIllumination;
		}
		return 1.0;
	}
};
#endif