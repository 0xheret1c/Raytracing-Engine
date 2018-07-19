#pragma once

//Forward declarations
class RaycastHit;

//Includes
#include <iostream>
#include <fstream>	// Importing meshs from filesystem.
#include "_Transform.h"
#include "Ray.h"
#include "Texture.h"
#include "Material.h"
#include "BoundingBox.h"
#include "Triangle.h"
#include "KDNode.h"

#define CULLING



class Mesh
{
private:
	//Ray-sphere intersection
	/*Eigen::Vector3d min;
	Eigen::Vector3d max;
	Eigen::Vector3d center;
	double radius;*/
	
	BoundingBox boundingBox;
	KDNode* node;
	std::vector<Triangle> triangles;

	/*bool checkSphereInterception(Ray ray)
	{
	
		Eigen::Vector3d e = center - ray.origin;
		double eLength = e.norm();
		double a = e.dot(ray.direction);
		if ((pow(radius,2) - pow(eLength,2) + pow(a,2)) < 0)
		{
			return false;
		}
		return true;
	}

	void checkBounds(Eigen::Vector3d pos)
	{
		min[0] = pos.x() < min.x() ? pos.x() : min.x();
		min[1] = pos.y() < min.y() ? pos.y() : min.y();
		min[2] = pos.z() < min.z() ? pos.z() : min.z();

		max[0] = pos.x() > max.x() ? pos.x() : max.x();
		max[1] = pos.y() > max.y() ? pos.y() : max.y();
		max[2] = pos.z() > max.z() ? pos.z() : max.z();
	}

	void calculateBounds()
	{
		max = Eigen::Vector3d(-INFINITY, -INFINITY, -INFINITY);
		min = Eigen::Vector3d(+INFINITY, +INFINITY, +INFINITY);
		for(int i = 0; i < vertCount; i++){
			checkBounds(transform.translate(verts[i]));
		}
		radius = (max - min).norm() / 2.0;
		center = (max + min) / 2.0;
	}*/

	void calculateBounds() {
		/*boundingBox = BoundingBox(transform.translate(verts[0]));

		for (int i = 1; i < vertCount; i++) {
			boundingBox.expand(transform.translate(verts[i]));
		}*/

		std::vector<Triangle*> trianglePointers;

		for (int i = 0; i < triCount; i += 3) {
			Eigen::Vector3d v0 = transform.translate(verts[tris[i]]);
			Eigen::Vector3d v1 = transform.translate(verts[tris[i + 1]]);
			Eigen::Vector3d v2 = transform.translate(verts[tris[i + 2]]);
			trianglePointers.push_back(new Triangle(v0, v1, v2, uv[tris[i]], uv[tris[i+1]], uv[tris[i+2]]));
		}

		node = KDNode::build(trianglePointers, 0);
	}

public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

	_Transform transform;
	Animator animator;

	Eigen::Vector3d* verts;
	int vertCount;

	int* tris;
	int triCount;

	Eigen::Vector2d* uv;
	int uvCount;

	Material mat;
	Texture texture;
	

	/*bool intersects(Ray ray, RaycastHit* hit)
	{
		if (!boundingBox.intersects(ray))
		{
			return false;
		}
		bool intersected = false;
		double closest = INFINITY;

		Eigen::Vector3d n(0, 0, 0);
		Eigen::Vector3d point(0, 0, 0);

		for (int i = 0; i < triCount; i += 3) {
			Eigen::Vector3d v0 = transform.translate(verts[tris[i]]);
			Eigen::Vector3d v1 = transform.translate(verts[tris[i + 1]]);
			Eigen::Vector3d v2 = transform.translate(verts[tris[i + 2]]);
			double t = 0;
			double u = 0;
			double v = 0;

			if (rayTriangleIntersect(ray.origin, ray.direction, v0, v1, v2, t, u, v)) {
				intersected = true;
				Eigen::Vector3d hitPoint = ray.origin + t * ray.direction;
				double distance = (hitPoint - ray.origin).norm();
				if (distance < closest)
				{
					closest = distance;
					point = hitPoint;
					n = (v1 - v0).cross(v2 - v0);
				}
			}
		}

		if(intersected)
		{
			hit->point = point;
			hit->n = n.normalized();
			hit->mesh = this;
		}
		return intersected;
	}*/

	bool intersects(Ray ray, RaycastHit* hit, double& t, double& tmin) {
		double u = 0;
		double v = 0;
		double umin = 0;
		double vmin = 0;
		if (KDNode::hit(node, ray, t, u, v, umin, vmin, tmin, hit)) {
			hit->mesh = this;
			//std::cout << "Getting UV pos" << std::endl;

			//Eigen::Vector2d uvPos = triangle->getUV(umin, vmin);
			Eigen::Vector2d uvPos = hit->uv0;
			uvPos += (hit->uv1 - hit->uv0) * umin;
			uvPos += (hit->uv2 - hit->uv0) * vmin;

			//std::cout << "U: " << uvPos.x() << std::endl;
			//std::cout << "V: " << uvPos.y() << std::endl;
			Eigen::Vector3f color = this->mat.color.cwiseProduct(texture.getPixel(uvPos[0], uvPos[1]));
			hit->color = color;
			return true;
		}
		return false;
	}

	Mesh()
	{
		//min = Eigen::Vector3d(-INFINITY, -INFINITY, -INFINITY);
		//max = Eigen::Vector3d(+INFINITY, +INFINITY, +INFINITY);
		calculateBounds();
	}

	Mesh(Eigen::Vector3d* _verts,int _vertCount, Eigen::Vector2d* _uv, int _uvCount, int * _triangles, int _triangleCount, _Transform _transform, Material material, Texture _texture)
	{
		mat = material;
		verts = _verts;
		transform = _transform;
		//max = Eigen::Vector3d(-INFINITY, -INFINITY, -INFINITY);
		//min = Eigen::Vector3d(+INFINITY, +INFINITY, +INFINITY);
		tris = _triangles;
		triCount = _triangleCount;
		vertCount = _vertCount;

		uv = _uv;
		uvCount = _uvCount;

		texture = _texture;

		calculateBounds();
	}

	Mesh(Eigen::Vector3d* _verts, int _vertCount, Eigen::Vector2d* _uv, int _uvCount, int * _triangles, int _triangleCount, Animator _animator, Material material, Texture _texture)
	{
		mat = material;
		verts = _verts;
		animator = _animator;
		transform = animator.getFrame(0);
		//max = Eigen::Vector3d(-INFINITY, -INFINITY, -INFINITY);
		//min = Eigen::Vector3d(+INFINITY, +INFINITY, +INFINITY);
		tris = _triangles;
		triCount = _triangleCount;

		uv = _uv;
		uvCount = _uvCount;

		texture = _texture;

		vertCount = _vertCount;
		calculateBounds();
	}

	~Mesh()
	{
		//TODO: VERTS CLEAR FIXEN!!!!
		//for (int i = 0; i < vertCount; i++)
		//{
		//	verts[i].resize(0);
		//}
		//delete[] verts;
		//delete[] triangles;
		//delete[] tris;
	}

	void toString() {
		std::cout << "Triangles int[" << triCount << "] = {";
		for (int i = 0; i < triCount; i++) {
			std::cout << tris[i] << (i < triCount - 1 ? ", " : "");
		}
		std::cout << "}" << std::endl;

		std::cout << "Vertices Vector3d[" << vertCount << "] = {";
		for (int i = 0; i < vertCount; i++) {
			std::cout << "(" << verts[i].x() << ", " << verts[i].y() << ", " << verts[i].z() << ")" << (i < vertCount - 1 ? ", " : "");
		}
		std::cout << "}" << std::endl;
	}

	bool rayTriangleIntersect(
		const Eigen::Vector3d &orig, const Eigen::Vector3d &dir,
		const Eigen::Vector3d &v0, const Eigen::Vector3d &v1, const Eigen::Vector3d &v2,
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

	void nextFrame() {
		transform = animator.nextFrame();
		calculateBounds();
	}

	void setFrame(int frame) {
		animator.setFrame(frame);
		transform = animator.getFrame();
		calculateBounds();
	}
};
