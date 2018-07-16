#pragma once

class BoundingBox {
private:

public:
	Eigen::Vector3d minPoint;
	Eigen::Vector3d maxPoint;

	BoundingBox() {

	}

	BoundingBox(Eigen::Vector3d origin) {
		minPoint = origin;
		maxPoint = origin;
	}

	void expand(Eigen::Vector3d &pos) {
		minPoint[0] = min(pos.x(), minPoint.x());
		minPoint[1] = min(pos.y(), minPoint.y());
		minPoint[2] = min(pos.z(), minPoint.z());

		maxPoint[0] = max(pos.x(), maxPoint.x());
		maxPoint[1] = max(pos.y(), maxPoint.y());
		maxPoint[2] = max(pos.z(), maxPoint.z());
	}

	void expand(BoundingBox box) {
		this->expand(box.minPoint);
		this->expand(box.maxPoint);
	}

	bool intersects(Ray &ray) {
		double tx1 = (minPoint.x() - ray.origin.x()) * ray.n_inv.x();
		double tx2 = (maxPoint.x() - ray.origin.x()) * ray.n_inv.x();

		double tmin = min(tx1, tx2);
		double tmax = max(tx1, tx2);

		double ty1 = (minPoint.y() - ray.origin.y()) * ray.n_inv.y();
		double ty2 = (maxPoint.y() - ray.origin.y()) * ray.n_inv.y();

		tmin = max(tmin, min(ty1, ty2));
		tmax = min(tmax, max(ty1, ty2));

		double tz1 = (minPoint.z() - ray.origin.z()) * ray.n_inv.z();
		double tz2 = (maxPoint.z() - ray.origin.z()) * ray.n_inv.z();

		tmin = max(tmin, min(tz1, tz2));
		tmax = min(tmax, max(tz1, tz2));

		return tmax >= tmin && tmax >= 0.0;
	}

	int longest_axis() {
		double x = abs(maxPoint.x() - minPoint.x());
		double y = abs(maxPoint.y() - minPoint.y());
		double z = abs(maxPoint.z() - minPoint.z());

		if (x >= y && x >= z) {
			return 0;
		}

		if (y >= x && y >= z) {
			return 1;
		}

		if (z >= x && z >= y) {
			return 2;
		}

		return 0;
	}
};