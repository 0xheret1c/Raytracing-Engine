#pragma once
#include <Eigen\Core>

#ifndef __TRANSFORM_H_INCLUDED__
#define __TRANSFORM_H_INCLUDED__

class _Transform 
{
private:

public:
	Eigen::Vector3d position;
	Eigen::Vector3d scale;
	Eigen::Quaterniond rotation;
	
	Eigen::Vector3d forward()
	{
		return rotation.toRotationMatrix() * Eigen::Vector3d::UnitZ();
 	}

	_Transform()
	{
		position = Eigen::Vector3d(0, 0, 0);
		scale = Eigen::Vector3d(1, 1, 1);

		//Just to be safe.
		this->rotation =
			Eigen::AngleAxisd(0, Eigen::Vector3d::UnitX())
			* Eigen::AngleAxisd(0, Eigen::Vector3d::UnitY())
			* Eigen::AngleAxisd(0, Eigen::Vector3d::UnitZ());
	}

	_Transform(Eigen::Vector3d position, Eigen::Vector3d rotation, Eigen::Vector3d scale)
	{
		this->position = position;
		this->scale = scale;
		
		this->rotation =  Eigen::AngleAxisd(rotation.x() * (M_PI) / 180, Eigen::Vector3d::UnitX())
						* Eigen::AngleAxisd(rotation.y() * (M_PI) / 180, Eigen::Vector3d::UnitY())
						* Eigen::AngleAxisd(rotation.z() * (M_PI) / 180, Eigen::Vector3d::UnitZ());
	}
};
#endif 