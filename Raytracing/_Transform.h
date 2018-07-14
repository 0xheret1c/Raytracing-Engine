#pragma once
#include <Eigen\Core>


class _Transform 
{
private:

public:
	//EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
	Eigen::Vector3d position;
	Eigen::Vector3d scale;
	Eigen::Quaterniond rotation;
	Eigen::Matrix3d rotationMatrix;
	
	Eigen::Vector3d forward()
	{
		return rotationMatrix * Eigen::Vector3d::UnitZ();
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

		this->rotationMatrix = this->rotation.toRotationMatrix();
	}


	_Transform(Eigen::Vector3d position)
	{
		this->position = position;
		this->scale = Eigen::Vector3d(1, 1, 1);

		this->rotation =
			Eigen::AngleAxisd(0, Eigen::Vector3d::UnitX())
			* Eigen::AngleAxisd(0, Eigen::Vector3d::UnitY())
			* Eigen::AngleAxisd(0, Eigen::Vector3d::UnitZ());

		this->rotationMatrix = this->rotation.toRotationMatrix();
	}

	_Transform(Eigen::Vector3d position, Eigen::Vector3d rotation)
	{
		this->position = position;
		this->scale = Eigen::Vector3d(1, 1, 1);

		this->rotation = Eigen::AngleAxisd(rotation.y() * (M_PI) / 180, Eigen::Vector3d::UnitY())
						* Eigen::AngleAxisd(rotation.x() * (M_PI) / 180, Eigen::Vector3d::UnitX())
						* Eigen::AngleAxisd(rotation.z() * (M_PI) / 180, Eigen::Vector3d::UnitZ());

		this->rotationMatrix = this->rotation.toRotationMatrix();
	}


	_Transform(Eigen::Vector3d position, Eigen::Vector3d rotation, Eigen::Vector3d scale)
	{
		this->position = position;
		this->scale = scale;
		
		this->rotation = Eigen::AngleAxisd(rotation.y() * (M_PI) / 180, Eigen::Vector3d::UnitY())
						* Eigen::AngleAxisd(rotation.x() * (M_PI) / 180, Eigen::Vector3d::UnitX())
						* Eigen::AngleAxisd(rotation.z() * (M_PI) / 180, Eigen::Vector3d::UnitZ());

		this->rotationMatrix = this->rotation.toRotationMatrix();
	}

	Eigen::Vector3d translate(Eigen::Vector3d vector) {
		return (rotationMatrix * vector.cwiseProduct(scale)) + position;
	}

	void Rotate(Eigen::Vector3d rotation) {
		this->rotation *= Eigen::AngleAxisd(rotation.y() * (M_PI) / 180, Eigen::Vector3d::UnitY())
						* Eigen::AngleAxisd(rotation.x() * (M_PI) / 180, Eigen::Vector3d::UnitX())
						* Eigen::AngleAxisd(rotation.z() * (M_PI) / 180, Eigen::Vector3d::UnitZ());
		this->rotationMatrix = this->rotation.toRotationMatrix();
	}

	void RecalculateMatrix() {
		this->rotationMatrix = this->rotation.toRotationMatrix();
	}
};