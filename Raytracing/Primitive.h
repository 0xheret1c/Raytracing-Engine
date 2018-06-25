#pragma once
#include "Mesh.h"
#include "_Transform.h"
class Primitive
{
public:
	static Mesh Cube(_Transform trans, SDL_Color color)
	{
		Eigen::Vector3d verts[8 * 3] =
		{
			Eigen::Vector3d(0.5,-0.5,0.5),
			Eigen::Vector3d(-0.5,-0.5,0.5),
			Eigen::Vector3d(0.5,0.5,0.5),
			Eigen::Vector3d(-0.5,0.5,0.5),
			Eigen::Vector3d(0.5,0.5,-0.5),
			Eigen::Vector3d(-0.5,0.5,-0.5),
			Eigen::Vector3d(0.5,-0.5,-0.5),
			Eigen::Vector3d(-0.5,-0.5,-0.5),
			Eigen::Vector3d(0.5,0.5,0.5),
			Eigen::Vector3d(-0.5,0.5,0.5),
			Eigen::Vector3d(0.5,0.5,-0.5),
			Eigen::Vector3d(-0.5,0.5,-0.5),
			Eigen::Vector3d(0.5,-0.5,-0.5),
			Eigen::Vector3d(0.5,-0.5,0.5),
			Eigen::Vector3d(-0.5,-0.5,0.5),
			Eigen::Vector3d(-0.5,-0.5,-0.5),
			Eigen::Vector3d(-0.5,-0.5,0.5),
			Eigen::Vector3d(-0.5,0.5,0.5),
			Eigen::Vector3d(-0.5,0.5,-0.5),
			Eigen::Vector3d(-0.5,-0.5,-0.5),
			Eigen::Vector3d(0.5,-0.5,-0.5),
			Eigen::Vector3d(0.5,0.5,-0.5),
			Eigen::Vector3d(0.5,0.5,0.5),
			Eigen::Vector3d(0.5,-0.5,0.5),
		};
		size_t triangles[36] =
		{
			0,2,3,0,3,1,8,4,5,8,5,9,10,6,7,10,7,11,12,13,14,12,14,15,16,17,18,16,18,19,20,21,22,20,22,23
		};

		return Mesh(verts, triangles, 36, trans, color);
		
	}

	static Mesh Plane(_Transform trans, SDL_Color color)
	{
		Eigen::Vector3d verts[4] =
		{
			Eigen::Vector3d(-0.5, 0, -0.5),
			Eigen::Vector3d(-0.5, 0,  0.5),
			Eigen::Vector3d(0.5, 0, -0.5),
			Eigen::Vector3d(0.5, 0,  0.5)
		};
		size_t triangles[6] =
		{
			0,1,2,3,2,1
		};

		return Mesh(verts, triangles, 6, trans, color);

	}

	static Mesh Pyramid(_Transform trans, SDL_Color color)
	{
		Eigen::Vector3d verts[5] =
		{
			Eigen::Vector3d(0.5, 0  ,  0.5),	// v0
			Eigen::Vector3d(0.5, 0  , -0.5),	// v1
			Eigen::Vector3d(-0.5, 0  , -0.5),	// v2
			Eigen::Vector3d(-0.5, 0  ,  0.5),	// v3
			Eigen::Vector3d( 0  , 1,    0)	// v4
		};
		size_t triangles[18] =
		{
			0,1,4,
			1,2,4,
			2,3,4,
			3,0,4,
			0,1,2,
			0,2,3
		};

		return Mesh(verts, triangles, 18, trans, color);

	}
};