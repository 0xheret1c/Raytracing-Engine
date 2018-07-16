#pragma once
class Scene;

#include <Eigen/Core>


class Ray
{
private:
	Scene* scene;
public:
	//EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
	Eigen::Vector3d origin;
	Eigen::Vector3d direction;
	Eigen::Vector3d n_inv;

	Ray(Eigen::Vector3d _origin, Eigen::Vector3d _dir, Scene* _scene)
	{
		scene = _scene;
		origin = _origin;
		direction = _dir;
		direction = direction.normalized();
		n_inv = Eigen::Vector3d(1.0 / direction.x(), 1.0 / direction.y(), 1.0 / direction.z());
	}

	Ray(Eigen::Vector3d _origin, Eigen::Vector3d _dir)
	{
		origin = _origin;
		direction = _dir;
		direction = direction.normalized();
		n_inv = Eigen::Vector3d(1.0 / direction.x(), 1.0 / direction.y(), 1.0 / direction.z());
	}

	Ray()
	{

	}
};
