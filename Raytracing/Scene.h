#pragma once
//Forward declaration
//class Camera;

#include <Eigen/Core>

#include "Triangle.h"
#include "RaycastHit.h"
#include "Mesh.h"
#include "Light.h"


class Scene 
{
private:
	size_t meshCount = 0;
	size_t lightCount = 0;
	std::vector<Mesh> meshes;
	std::vector<Light> lights;
public:
	double globalIllumination = 0.45;
	//EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

	Camera camera;

	Scene()
	{

	}
	Scene(std::vector<Mesh> _meshes,size_t _meshCount, std::vector<Light> _lights,size_t _lightCount, Camera _cam)
	{
		meshCount = _meshCount;
		meshes = _meshes;
		lights = _lights;
		camera = _cam;
	}

	void setLights(std::vector<Light> _lights, size_t count)
	{
		lights = _lights;
		lightCount = count;
	}
	void setMeshes(std::vector<Mesh> _meshes, size_t count)
	{
		meshes = _meshes;
		meshCount = count;
	}

	double calculateLightIntensity(Eigen::Vector3d origin,Light light, Triangle* ignore = nullptr)
	{
		double epsilon = std::numeric_limits<double>::epsilon();
		//double epsilon = 0.01;
		RaycastHit hit;
		Ray ray = Ray(origin, -light.transform.forward(), this);
		if (intersects(ray, &hit, ignore))
		{
			double scalar = ignore->n.dot(light.transform.forward());
			if (abs(scalar) > 1.0 - epsilon)
			{
				return globalIllumination;
			}
			else
			{
				double angle = acos(scalar);
				//angle = (angle * 180f) / Mathf.PI;
				return (angle / M_PI) * globalIllumination;
			}
		}
		//return 1.0;

		double scalar = ignore->n.dot(light.transform.forward());
		if (abs(scalar) > 1.0 - epsilon)
		{
			return 1.0;
		}
		else
		{
			double angle = acos(scalar);
			//angle = (angle * 180f) / Mathf.PI;
			return (angle / M_PI);
		}

	}

	double getIllumination(Eigen::Vector3d point, Triangle* ignore = nullptr)
	{
		double illum = 0;
		size_t amountLights = lightCount;
		for (size_t i = 0; i < amountLights; i++)
		{
			illum += calculateLightIntensity(point,lights[i],ignore);
		}
		return illum;
	}

	bool intersects(Ray ray, RaycastHit* hit, Triangle* ignore = nullptr)
	{
		size_t length = meshCount;

		
		bool intersected = false;
		double closest = INFINITY;

		for (size_t i = 0; i < length; i++)
		{
			RaycastHit closestHit;
			if(meshes[i].intersects(ray,&closestHit,ignore))
			{
				double distance = (closestHit.point - ray.origin).norm();
				if(distance < closest)
				{
					*hit = closestHit;
					closest = distance;
					intersected = true;
				}
			}
		}

		return intersected;
	}
};
