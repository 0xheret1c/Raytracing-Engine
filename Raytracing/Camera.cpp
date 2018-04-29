#include "./Camera.h"
#include <math.h>

Camera::Camera(double pos[3], double fov, double distance, double pitchYaw[2])
{
	this->pos.x = pos[0];
	this->pos.y = pos[1];
	this->pos.z = pos[2];


}
Vector Camera::getDirection() 
{
	Vector ret;
	ret.x = cos(pitch) * cos(yaw);
	ret.y = cos(pitch) * sin(yaw);
	ret.z = sin(pitch);
	return ret;
}

void Camera::setFov(double fov)
{
	this->fov = fov;
	this->distance = (this->planeWidth / 2) / tan(fov / 2);
}