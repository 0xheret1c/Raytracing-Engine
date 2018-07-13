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
	SDL_Color color;

	RaycastHit()
	{
		color.a = 0xFF;
		color.r = 0x00;
		color.g = 0x00;
		color.b = 0x00;
	}
	RaycastHit(Mesh* _mesh, Eigen::Vector3d _point, Eigen::Vector3d _n)
	{
		mesh = _mesh;
		//triangle = _triangle;
		point = _point;
		//triangleObject = *triangle;
		n = _n;
		color.a = 0xFF;
		color.r = 0x00;
		color.g = 0x00;
		color.b = 0x00;
	}
};
