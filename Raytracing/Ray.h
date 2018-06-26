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

	Ray(Eigen::Vector3d _origin, Eigen::Vector3d _dir, Scene* _scene)
	{
		scene = _scene;
		origin = _origin;
		direction = _dir;
	}
	Ray(Eigen::Vector3d _origin, Eigen::Vector3d _dir)
	{
		origin = _origin;
		direction = _dir;
	}
	Ray()
	{
	}
};
