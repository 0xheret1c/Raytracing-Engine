#pragma once

//Foward declaration
class Ray;

//Includes
#include <time.h>
#include <Eigen\Core>
#include "_Transform.h"
#include "RaycastHit.h"
#include "Material.h"



class Camera
{
private:


	/*Eigen::Vector3f traceDiffuse(Eigen::Vector3d reflection, RaycastHit hit, Triangle *ignore = nullptr) {
		//double angleRadX = Utils::_rand();
		//double angleRadY = (fovY / ((height - 1.0) * density)) * ((y*density) + (z / density)) - (fovY / 2.0);
	}*/



public:
	unsigned int width = 200;
	unsigned int height = 200;
	unsigned int density = 1;
	double screenDistance = 1.0;
	double fov = 60;
	size_t maxBounces = 1;
	_Transform transform;

	void setMaxBounces(size_t val)
	{
		maxBounces = val;
	}
	void setDensity(size_t val)
	{
		density = val;
	}
	void setSize(unsigned int _width, unsigned int _height)
	{
		width = _width;
		height = _height;
		std::cout << "Set Width: " << _width << std::endl;
		std::cout << "Set Height: " << _height << std::endl;
	}

	Camera()
	{

	}

	Camera(unsigned int _width, unsigned int _height, _Transform _transform)
	{
		transform = _transform;
		width = _width;
		height = _height;
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
};
