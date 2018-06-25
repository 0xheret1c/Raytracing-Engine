#pragma once
//Forward declarations
class Mesh;
//Includes
#include <Eigen\Core>
#include "Triangle.h"


//include guards
#ifndef __RAYCASTHIT_H_INCLUDED__
#define __RAYCASTHIT_H_INCLUDED__
class RaycastHit
{
private:
public:
	//EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
	Mesh* mesh;
	Triangle* triangle;
	Triangle triangleObject;
	Eigen::Vector3d point;
	double intensity = 0;
	SDL_Color color;

	RaycastHit()
	{
		color.a = 0xFF;
		color.r = 0x00;
		color.g = 0x00;
		color.b = 0x00;
	}
	RaycastHit(Mesh* _mesh, Triangle* _triangle, Eigen::Vector3d _point)
	{
		mesh = _mesh;
		triangle = _triangle;
		point = _point;
		triangleObject = *triangle;
		color.a = 0xFF;
		color.r = 0x00;
		color.g = 0x00;
		color.b = 0x00;
	}
};
#endif