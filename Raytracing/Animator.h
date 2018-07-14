#pragma once

class Animator {
private:
	std::vector<Eigen::Vector3d> positions;
	std::vector<Eigen::Vector3d> rotations;
	std::vector<Eigen::Vector3d> scales;
	int curFrame = 0;
	int frameCount = 0;

public:
	Animator() {

	}

	void addFrame(Eigen::Vector3d position, Eigen::Vector3d rotation, Eigen::Vector3d scale) {
		this->positions.push_back(position);
		this->rotations.push_back(rotation);
		this->scales.push_back(scale);
		this->frameCount++;
	}

	_Transform getFrame(int frame) {
		frame = frame % this->frameCount;
		return _Transform(positions[frame], rotations[frame], scales[frame]);
	}

	_Transform nextFrame() {
		this->curFrame++;
		this->curFrame = this->curFrame % this->frameCount;
		return _Transform(positions[this->curFrame], rotations[this->curFrame], scales[this->curFrame]);
	}
};