#pragma once

#include <Eigen\Core>
#include "_Transform.h"
#include "Ray.h"
#include "RaycastHit.h"


class Light
{
private:

public:
	//EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
	_Transform transform;
	Animator animator;
	Eigen::Vector3d direction;

	Light(){}

	Light(_Transform _transform)
	{
		transform = _transform;
	}

	Light(Animator _animator)
	{
		animator = _animator;
		transform = animator.getFrame(0);
	}

	Light(_Transform _transform, Eigen::Vector3d _direction)
	{
		transform = _transform;
		direction = _direction;
	}

	void nextFrame() {
		transform = animator.nextFrame();
	}

	void setFrame(int frame) {
		animator.setFrame(frame);
		transform = animator.getFrame(frame);
	}


};
