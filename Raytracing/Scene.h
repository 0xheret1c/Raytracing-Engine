#pragma once
//Forward declaration
//class Camera;

#include <Eigen/Core>
#include <vector>
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
	double globalIllumination = 0.2;
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

	Mesh* getMesh(int index) {
		return &meshes[index];
	}

	void setMeshes(std::vector<Mesh> _meshes, size_t count)
	{
		meshes = _meshes;
		meshCount = count;
	}

	double calculateLightIntensity(Eigen::Vector3d origin,Light light, Eigen::Vector3d normal)
	{
		double epsilon = std::numeric_limits<double>::epsilon();
		//double epsilon = 0.01;
		RaycastHit hit;
		origin += normal * (epsilon*10000);
		Ray ray = Ray(origin, -light.transform.forward(), this);
		if (intersects(ray, &hit))
		{
			return (1.0 - Our_math::clamp01(normal.dot(light.transform.forward()))) * globalIllumination;
		}

		return Our_math::clamp01(normal.dot(-light.transform.forward())) * (1.0 - globalIllumination) + globalIllumination;
	}

	double getIllumination(Eigen::Vector3d point, Eigen::Vector3d normal)
	{
		double illum = 0;
		size_t amountLights = lightCount;
		for (size_t i = 0; i < amountLights; i++)
		{
			illum += calculateLightIntensity(point,lights[i], normal);
		}
		return illum;
	}

	bool intersects(Ray ray, RaycastHit* hit)
	{
		bool intersected = false;

		double t = 0;
		double tmin = INFINITY;

		for (int i = 0; i < meshCount; i++) {
			if (meshes[i].intersects(ray, hit, t, tmin)) {
				intersected = true;
			}
		}

		return intersected;
	}

	void update() {
		camera.nextFrame();
		for (int i = 0; i < lightCount; i++) {
			lights[i].nextFrame();
		}
		for (int i = 0; i < meshCount; i++) {
			meshes[i].nextFrame();
		}
	}

	void setFrame(int frame) {
		camera.setFrame(frame);
		for (int i = 0; i < lightCount; i++) {
			lights[i].setFrame(frame);
		}
		for (int i = 0; i < meshCount; i++) {
			meshes[i].setFrame(frame);
		}
	}
};
