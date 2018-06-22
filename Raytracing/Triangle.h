#pragma once
#include "Core.h"

#ifndef __TRIANGLE_H_INCLUDED__
#define __TRIANGLE_H_INCLUDED__

class Triangle
{
private:
	Eigen::Vector3d v0;
	Eigen::Vector3d v1;
	Eigen::Vector3d v2;
	Eigen::Vector3d edge1;
	Eigen::Vector3d edge2;
public:
	Eigen::Vector3d n;

	bool intersects(Ray ray, Eigen::Vector3d intersection)
	{
		double epsilon = std::numeric_limits<double>::epsilon();
		Eigen::Vector3d h, s, q;
		double a, f, u, v;

		h = ray.direction.cross(edge2);
		a = edge1.dot(h);

		if (a > -epsilon && a < epsilon)
			return false;
		f = 1 / a;
		s = ray.origin - v0;
		u = f * (s.dot(h));

		if (u < 0.0 || u > 1.0)
			return false;

		q = s.cross(edge1);
		v = f * ray.direction.dot(q);

		if (v < 0.0 || u + v > 1.0)
			return false;

		float t = f * edge2.dot(q);
		if (t > epsilon)
		{
			intersection = ray.origin + ray.direction * t;
			return true;
		}
		return false;
	}

	Triangle(Eigen::Vector3d _v0, Eigen::Vector3d _v1, Eigen::Vector3d _v2)
	{
		v0 = _v0;
		v1 = _v1;
		v2 = _v2;
		edge1 = v1 - v0;
		edge2 = v2 - v0;
		n = edge1.cross(edge2).normalized();
	}
	Triangle()
	{
		v0 = Eigen::Vector3d(0, 0, 1);
		v1 = Eigen::Vector3d(0, 0, 2);
		v2 = Eigen::Vector3d(0, 0, 3);
		edge1 = v1 - v0;
		edge2 = v2 - v0;
		n = edge1.cross(edge2).normalized();
	}
};
#endif