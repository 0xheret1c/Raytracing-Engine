/*class _Transform;
class Camera;
class Light;
class Mesh 
{

};

class RaycastHit
{
	RaycastHit(Mesh, Triangle, Eigen::Vector3d);
	RaycastHit();
};
class Scene
{
	bool intersects(Ray, RaycastHit, Triangle);
};
class Ray
{

	Ray(Eigen::Vector3d, Eigen::Vector3d, Scene);
	Ray();
};
class Triangle;*/




#pragma once
/*Eigen*/
#include <Eigen\Core>
#include <Eigen\Geometry>

/*Our stuff*/
#include "Our_math.h"
#include "Utils.h"
#include "GFXOutput.h"

/*Geometry n stuff*/
#include "_Transform.h"
#include "Ray.h"
#include "Triangle.h"
#include "Camera.h"
#include "Mesh.h"
#include "Light.h"
#include "Scene.h"
#include "RaycastHit.h"





