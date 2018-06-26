#pragma once

//Foward declaration
class Ray;
class Scene;

//Includes
#include <time.h>
#include <Eigen\Core>
#include "_Transform.h"
#include "RaycastHit.h"



class Camera
{
private:

	unsigned int width = 200;
	unsigned int height = 200;
	unsigned int density = 5;
	double screenDistance = 0.5;
	double fov = 90;
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
			hit->color.r += hit->mesh->color.r;
			hit->color.g += hit->mesh->color.g;
			hit->color.b += hit->mesh->color.b;
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
		//Debug
		std::cout << "Started tracing... this might take a while!" << std::endl;
		const clock_t begin_time = clock();

		size_t pixelToTrace = height * width;
		size_t tracedPixel = 0;
		size_t lastPercent = 0;

		//--
		//Eigen::Matrix3d m = transform.rotation.toRotationMatrix(); // Funktioniert eventuell nicht
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

	

					direction =  transform.rotationMatrix * direction;
					
					RaycastHit hit;

					if (traceRay(direction,&hit,0))
					{
						/*Uint8 color = (Uint8)(Our_math::clamp01(hit.intensity) * 0xFF);
						*/
						r += Our_math::clamp01((hit.color.r / 0xFF) * hit.intensity);
						g += Our_math::clamp01((hit.color.g / 0xFF) * hit.intensity);
						b += Our_math::clamp01((hit.color.b / 0xFF)* hit.intensity);
					}
				}
				r /= (density * density);
				g /= (density * density);
				b /= (density * density);

				returnArray[x][height - y - 1].r = (Uint8)(Our_math::clamp01(r) * 0xFF);
				returnArray[x][height - y - 1].g = (Uint8)(Our_math::clamp01(g) * 0xFF);
				returnArray[x][height - y - 1].b = (Uint8)(Our_math::clamp01(b) * 0xFF);

				tracedPixel++;
			}

			//Debug
			size_t percent = (size_t)(((float)tracedPixel / (float)pixelToTrace) * 100);
			if (percent % 1 == 0 && percent != lastPercent)
			{
				float timePassedSecs = float(clock() - begin_time) / CLOCKS_PER_SEC;
				lastPercent = percent;
				float timeRemaining = (100 - percent) * (timePassedSecs / (percent));
				std::cout << "Traced " << percent << "% "
					<< tracedPixel << "/" << pixelToTrace << " pixels traced. "
					<< tracedPixel * (density * density) << "/" << pixelToTrace * (density * density) << " rays casted."
					<< " Est. Time Remaining: " << timeRemaining << " seconds."
					<< std::endl;
			}
		}
		float timePassedSecs = float(clock() - begin_time) / CLOCKS_PER_SEC;
		std::cout << "Trame finished in " << timePassedSecs << " seconds / " << 1 / timePassedSecs << " FPS." << std::endl;
		return returnArray;
	}
};
