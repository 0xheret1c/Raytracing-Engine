#pragma once

#include <Eigen\Core>
#include "_Transform.h"
#include "Ray.h"
#include "Triangle.h"
#include "RaycastHit.h"


class Light
{
private:

public:
	//EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
	_Transform transform;
	Eigen::Vector3d direction;

	Light(){}

	Light(_Transform _transform)
	{
		transform = _transform;
	}

	Light(_Transform _transform, Eigen::Vector3d _direction)
	{
		transform = _transform;
		direction = _direction;
	}


};
