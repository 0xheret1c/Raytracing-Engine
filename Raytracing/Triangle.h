

class Triangle
{
private:
	Eigen::Vector3d v0;
	Eigen::Vector3d v1;
	Eigen::Vector3d v2;

public:
	//EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
	Eigen::Vector3d n;

	bool rayTriangleIntersect(
		const Eigen::Vector3d &orig, const Eigen::Vector3d &dir,
		double &t, double &u, double &v)
	{
		double epsilon = std::numeric_limits<double>::epsilon();
		Eigen::Vector3d v0v1 = v1 - v0;
		Eigen::Vector3d v0v2 = v2 - v0;
		Eigen::Vector3d pvec = dir.cross(v0v2);
		double det = v0v1.dot(pvec);
		#ifdef CULLING
				// if the determinant is negative the triangle is backfacing
				// if the determinant is close to 0, the ray misses the triangle
				if (det < epsilon) return false;
		#else
				// ray and triangle are parallel if det is close to 0
				if (fabs(det) < epsilon) return false;
		#endif
		double invDet = 1 / det;

		Eigen::Vector3d tvec = orig - v0;
		u = tvec.dot(pvec) * invDet;
		if (u < 0 || u > 1) return false;

		Eigen::Vector3d qvec = tvec.cross(v0v1);
		v = dir.dot(qvec) * invDet;
		if (v < 0 || u + v > 1) return false;

		t = v0v2.dot(qvec) * invDet;

		if (t > 0) {
			return true;
		}

		return false;
	}

	Triangle(Eigen::Vector3d _v0, Eigen::Vector3d _v1, Eigen::Vector3d _v2)
	{
		v0 = _v0;
		v1 = _v1;
		v2 = _v2;
		n = (v1 - v0).cross(v2 - v0).normalized();
	}
	Triangle()
	{
		v0 = Eigen::Vector3d(0, 0, 1);
		v1 = Eigen::Vector3d(0, 0, 2);
		v2 = Eigen::Vector3d(0, 0, 3);
		n = (v1 - v0).cross(v2 - v0).normalized();
	}

	Eigen::Vector3d get_midpoint() {
		return (v0 + v1 + v2) * (1.0/3.0);
	}

	BoundingBox get_bounding_box() {
		BoundingBox bbox = BoundingBox(v0);
		bbox.expand(v1);
		bbox.expand(v2);
		return bbox;
	}
};
