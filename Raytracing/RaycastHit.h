#pragma once
//Forward declarations
class Mesh;
//Includes
#include <Eigen\Core>

class RaycastHit
{
private:
public:
	//EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
	Mesh* mesh;
	//Triangle* triangle;
	//Triangle triangleObject;
	Eigen::Vector3d point;
	Eigen::Vector3d n;
	double intensity = 0;
	Eigen::Vector3f color;

	Eigen::Vector2d uv0;
	Eigen::Vector2d uv1;
	Eigen::Vector2d uv2;

	Eigen::Vector3d n0;
	Eigen::Vector3d n1;
	Eigen::Vector3d n2;

	RaycastHit()
	{
		color = Eigen::Vector3f(0, 0, 0);
	}

	RaycastHit(Mesh* _mesh, Eigen::Vector3d _point, Eigen::Vector3d _n)
	{
		mesh = _mesh;
		//triangle = _triangle;
		point = _point;
		//triangleObject = *triangle;
		n = _n;
		color = Eigen::Vector3f(0, 0, 0);
	}
};
