#pragma once
#include "Core.h"


class Camera
{
private:
	Scene scene;
	unsigned int width = 800;
	unsigned int height = 480;
	unsigned int density = 1;
	double screenDistance = 0.5;
	double fov = 60;
	size_t maxBounces = 0;

	bool traceRay(Eigen::Vector3d direction, RaycastHit hit,size_t bounces, Triangle* ignore = nullptr)
	{
		Ray ray = Ray(transform.position, direction, scene);
		if(scene.intersects(ray,hit,ignore))
		{
			if(bounces >= maxBounces)
			{
				size_t amountLights = sizeof(scene.lights) / sizeof(Light);
				for (size_t i = 0; i < amountLights; i++)
				{
					hit.intensity += scene.lights[i].calculateLightIntensity(hit.point,&hit.triangle);
				}
			}
			return true;
		}
		return false;
	}



public:
	_Transform transform;
	Camera() 
	{
		transform = _Transform();
		scene = Scene();
	}
	Camera(unsigned int _width, unsigned int _height, unsigned int _density, double _screenDistance, double _fov,Scene _scene)
	{
		transform = _Transform();
		fov = _fov;
		screenDistance = _screenDistance;
		density = _density;
		width = _width;
		height = _height;
		scene = _scene;
	}
	Camera(unsigned int _width, unsigned int _height, unsigned int _density, double _screenDistance, double _fov,_Transform _transform, Scene _scene)
	{
		transform = _transform;
		fov = _fov;
		screenDistance = _screenDistance;
		density = _density;
		width = _width;
		height = _height;
		scene = _scene;
	}
	Camera(_Transform _transform, Scene _scene)
	{
		transform = _transform;
		scene = _scene;
	}
	SDL_Color** trace()
	{
		Eigen::Matrix3d m = transform.rotation.toRotationMatrix(); // Funktioniert eventuell nicht
		double fovY = fov * ((double)height / (double)width);
		double fovX = fov;

		SDL_Color** returnArray = 0;
		returnArray = new SDL_Color*[width];
		for (size_t x = 0; x < width; x++)
		{
			returnArray[x] = new SDL_Color[width];
			for (size_t y = 0; y < height; y++)
			{
				returnArray[x][y].a = 0xFF;
				returnArray[x][y].r = 0x00;
				returnArray[x][y].g = 0x00;
				returnArray[x][y].b = 0x00;

				for (size_t z = 0; z < density * density; z++)
				{
					float angleRadX = (fov / ((width - 1.0) * density)) * ((x*density) + (z%density)) - (fov / 2.0);
					angleRadX *= M_PI / 180.0;
					float angleRadY = (fovY / ((height - 1.0) * density)) * ((y*density) + (z / density)) - (fovY / 2.0);
					angleRadY *= M_PI / 180.0;

					Eigen::Vector3d direction = Eigen::Vector3d(0,0,0);
					direction.x = tan(angleRadX) * screenDistance;
					direction.y = tan(angleRadY) * screenDistance;
					direction.z = screenDistance;

					direction =  m * direction;
					
					RaycastHit hit;
	
					if (traceRay(direction,hit,0))
					{
						unsigned char color = Our_math::clamp01(hit.intensity) * 0xFF;
						returnArray[x][y].r = color;
						returnArray[x][y].g = color;
						returnArray[x][y].b = color;
					}
				}
			}
		}

		return returnArray;
	}
};