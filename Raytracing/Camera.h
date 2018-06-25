#pragma once

//Foward declaration
class Ray;
class Scene;

//Includes
#include <Eigen\Core>
#include "_Transform.h"
#include "RaycastHit.h"



//Include guards
#ifndef __CAMERA_H_INCLUDED
#define __CAMERA_H_INCLUDED

class Camera
{
private:

	unsigned int width = 200;
	unsigned int height = 200;
	unsigned int density = 3;
	double screenDistance = 0.5;
	double fov = 60;
	size_t maxBounces = 0;
	Scene* scene;

	bool traceRay(Eigen::Vector3d direction, RaycastHit* hit,size_t bounces, Triangle* ignore = nullptr)
	{
		Ray ray = Ray(transform.position, direction, scene);
		if(scene->intersects(ray,hit,ignore))
		{
			if(bounces >= maxBounces)
			{
				hit->intensity = scene->getIllumination(hit->point,hit->triangle);
			}
			return true;
		}
		return false;
	}



public:
	//EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
	_Transform transform;

	Camera(unsigned int _width, unsigned int _height, _Transform _transform, Scene* _scene)
	{
		transform = _transform;
		scene = _scene;
		width = _width;
		height = _height;
	}
	Camera(unsigned int _width, unsigned int _height, unsigned int _density, double _screenDistance, double _fov,Scene* _scene)
	{
		transform = _Transform();
		fov = _fov;
		screenDistance = _screenDistance;
		density = _density;
		width = _width;
		height = _height;
		scene = _scene;
	}
	Camera(unsigned int _width, unsigned int _height, unsigned int _density, double _screenDistance, double _fov,_Transform _transform, Scene* _scene)
	{
		transform = _transform;
		fov = _fov;
		screenDistance = _screenDistance;
		density = _density;
		width = _width;
		height = _height;
		scene = _scene;
	}
	Camera(_Transform _transform, Scene* _scene)
	{
		transform = _transform;
		scene = _scene;
	}
	SDL_Color** trace()
	{
		std::cout << "Tracing..." << std::endl;
		Eigen::Matrix3d m = transform.rotation.toRotationMatrix(); // Funktioniert eventuell nicht
		double fovY = fov * ((double)height / (double)width);
		double fovX = fov;

		SDL_Color** returnArray;
		returnArray = new SDL_Color*[width];
		for (size_t x = 0; x < width; x++)
		{
			returnArray[x] = new SDL_Color[height];
			for (size_t y = 0; y < height; y++)
			{
				returnArray[x][height - y - 1] = SDL_Color();
				returnArray[x][height - y - 1].a = 255;
				returnArray[x][height - y - 1].r = 0;
				returnArray[x][height - y - 1].g = 0;
				returnArray[x][height - y - 1].b = 120;

				double r = 0;
				double g = 0;
				double b = 0;

				for (size_t z = 0; z < density * density; z++)
				{
					double angleRadX = (fov / ((width - 1.0) * density)) * ((x*density) + (z%density)) - (fov / 2.0);
					angleRadX *= M_PI / 180.0;
					double angleRadY = (fovY / ((height - 1.0) * density)) * ((y*density) + (z / density)) - (fovY / 2.0);
					angleRadY *= M_PI / 180.0;

					double _x = tan(angleRadX) * screenDistance;
					double _y = tan(angleRadY) * screenDistance;
					double _z = screenDistance;
					Eigen::Vector3d direction = Eigen::Vector3d(_x,_y,_z);

	

					direction =  m * direction;
					
					RaycastHit hit;

					if (traceRay(direction,&hit,0))
					{
						/*Uint8 color = (Uint8)(Our_math::clamp01(hit.intensity) * 0xFF);

						returnArray[x][height - y - 1].r = color;
						returnArray[x][height - y - 1].g = color;
						returnArray[x][height - y - 1].b = color;*/
						r += Our_math::clamp01(hit.intensity);
						g += Our_math::clamp01(hit.intensity);
						b += Our_math::clamp01(hit.intensity);
					}
				}
				r /= (density * density);
				g /= (density * density);
				b /= (density * density);

				returnArray[x][height - y - 1].r = (Uint8)(Our_math::clamp01(r) * 0xFF);
				returnArray[x][height - y - 1].g = (Uint8)(Our_math::clamp01(g) * 0xFF);
				returnArray[x][height - y - 1].b = (Uint8)(Our_math::clamp01(b) * 0xFF);
			}
		}
		return returnArray;
		std::cout << "Done!" << std::endl;
	}
};
#endif __CAMERA_H_INCLUDED