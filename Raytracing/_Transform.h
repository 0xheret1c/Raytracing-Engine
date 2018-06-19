#pragma once
#include "core.h"

using namespace Eigen; // :'(

class _Transform 
{
private:

public:
	Vector3d position;
	Vector3d scale;
	Quaterniond rotation;
	
	_Transform()
	{
		position = Vector3d(0, 0, 0);
		scale = Vector3d(1, 1, 1);

		//Just to be safe.
		this->rotation =
			  AngleAxisd(0, Vector3d::UnitX())
			* AngleAxisd(0, Vector3d::UnitY())
			* AngleAxisd(0, Vector3d::UnitZ());
	}

	_Transform(Vector3d position, Vector3d rotation, Vector3d scale)
	{
		this->position = position;
		this->scale = scale;
		
		this->rotation =  AngleAxisd(rotation.x() * M_PI, Vector3d::UnitX())
						* AngleAxisd(rotation.y() * M_PI, Vector3d::UnitY())
						* AngleAxisd(rotation.z() * M_PI, Vector3d::UnitZ());
	}
};