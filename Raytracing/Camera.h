#pragma once
#include "Core.h"

using namespace Eigen; // :'(
class Camera
{
private:
	unsigned int width = 800;
	unsigned int height = 480;
	unsigned int density = 2;
	double screenDistance = 0.5;
	double fov = 60;

	RaycastHit traceRay()
	{

	}

public:
	_Transform transform;
	Camera() 
	{
		transform = _Transform();
	}
	Camera(unsigned int _width, unsigned int _height, unsigned int _density, double _screenDistance, double _fov)
	{
		transform = _Transform();
		fov = _fov;
		screenDistance = _screenDistance;
		density = _density;
		width = _width;
		height = _height;
	}
	Camera(unsigned int _width, unsigned int _height, unsigned int _density, double _screenDistance, double _fov,_Transform _transform)
	{
		transform = _transform;
		fov = _fov;
		screenDistance = _screenDistance;
		density = _density;
		width = _width;
		height = _height;
	}
	Camera(_Transform _transform)
	{
		transform = _transform;
	}

	SDL_Color** Trace()
	{
		Matrix4d m = transform.rotation.matrix(); // Funktioniert eventuell nicht
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

					Vector3d direction = Vector3d(0,0,0);
					direction.x = tan(angleRadX) * screenDistance;
					direction.y = tan(angleRadY) * screenDistance;
					direction.z = screenDistance;
					//direction = m.MultiplyPoint3x4(direction);

					
				}
			}
		}


		return returnArray;
	}
};