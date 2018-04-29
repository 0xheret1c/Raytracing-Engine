#pragma once
#include "./Vector.h"
#include "./Polygon.h"
class Camera 
{
	Polygon plane[2];
	Vector pos;
	double fov;
	double pitch;
	double yaw;
	double distance;
	int planeWidth;
	int planeHeight;

public:
	Camera(double pos[3], double fov, double distance, double pitchYaw[2]);
	Vector getDirection();
	void setFov(double fov);


};