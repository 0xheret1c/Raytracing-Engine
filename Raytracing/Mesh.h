#pragma once

//Forward declarations
class RaycastHit;

//Includes
#include "_Transform.h"
#include "Triangle.h"
#include "Ray.h"

//Include guards
#ifndef __MESH_H_INCLUDED__
#define __MESH_H_INCLUDED__

class Mesh
{
private:
	size_t triangleCount = 0;
	void calculateTriangels(size_t * _triangles, size_t _triangleCount)
	{
		size_t sizeTriangles = _triangleCount;
		triangleCount = sizeTriangles / 3;
		triangles = new Triangle[triangleCount];
		size_t c = 0;
		for (size_t i = 0; i < sizeTriangles; i += 3)
		{
			//TODO: scale einbauen
			Eigen::Vector3d v1((transform.rotation.toRotationMatrix() * verts[_triangles[i + 0]]) + transform.position);
			Eigen::Vector3d v2((transform.rotation.toRotationMatrix() * verts[_triangles[i + 1]]) + transform.position);
			Eigen::Vector3d v3((transform.rotation.toRotationMatrix() * verts[_triangles[i + 2]]) + transform.position);
			triangles[c] = Triangle(v1,v2,v3);
			c++;
		}

	}

public:
	//EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
	_Transform transform;
	Eigen::Vector3d* verts;
	Triangle* triangles;
	SDL_Color color;

	bool intersects(Ray ray, RaycastHit* hit,Triangle* ignore = nullptr)
	{
		size_t length = triangleCount;

		bool intersected = false;
		double closest = INFINITY;
		Triangle* closestTriangle = nullptr;
		Eigen::Vector3d closestPoint;
		for (size_t i = 0; i < length; i++)
		{
			if(&triangles[i] != ignore)
			{

				Eigen::Vector3d point;
				if(triangles[i].intersects(ray,&point))
				{
					intersected = true;
					double distance = (point - ray.origin).norm();
					if(distance < closest)
					{
						closest = distance;
						closestTriangle = &triangles[i];
						closestPoint = point;
					}
				}
			}
		}

		if(intersected)
		{
			hit->point = closestPoint;
			hit->triangle = closestTriangle;
			hit->triangleObject = *closestTriangle;
			hit->mesh = this;
		}
		return intersected;
	}

	Mesh()
	{

	}
	Mesh(Eigen::Vector3d* _verts,size_t * _triangles, size_t _triangleCount ,_Transform _transform, SDL_Color c)
	{
		color = c;
		verts = _verts;
		transform = _transform;
		calculateTriangels(_triangles, _triangleCount);
	}
	~Mesh()
	{
		//Cleanup
		delete[] verts;
		delete[] triangles;
	}
	
};
#endif