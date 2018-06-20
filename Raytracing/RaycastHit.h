#pragma once
#include "Core.h"


class RaycastHit
{
private:
public:
	Mesh mesh;
	Triangle triangle;
	Eigen::Vector3d point;
	double intensity = 0;

	RaycastHit()
	{
	}
	RaycastHit(Mesh _mesh, Triangle _triangle, Eigen::Vector3d _point)
	{
		mesh = _mesh;
		triangle = _triangle;
		point = _point;
	}
};