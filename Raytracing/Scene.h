#pragma once
#include "Core.h"


class Scene 
{
private:


public:
	Mesh* meshes;
	Light* lights;
	Camera camera;

	Scene()
	{

	}
	Scene(Mesh* _meshes, Light* _lights, Camera _cam)
	{
		meshes = _meshes;
		lights = _lights;
		camera = _cam;
	}

	double globalIllumination = 0.2;

	bool intersects(Ray ray, RaycastHit hit, Triangle* ignore = nullptr)
	{
		size_t length = sizeof(meshes) / sizeof(Mesh);

		
		bool intersected = false;
		double closest = INFINITY;

		for (size_t i = 0; i < length; i++)
		{
			RaycastHit closestHit;
			if(meshes[i].intersects(ray,closestHit,ignore))
			{
				double distance = (closestHit.point - ray.origin).norm();
				if(distance < closest)
				{
					hit = closestHit;
					closest = distance;
					intersected = true;
				}
			}
		}

		return intersected;
	}

};