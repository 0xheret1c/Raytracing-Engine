#pragma once

//Forward declarations
class RaycastHit;

//Includes
#include <iostream>
#include <fstream>	// Importing meshs from filesystem.
#include "_Transform.h"
#include "Triangle.h"
#include "Ray.h"
#include "Material.h"



class Mesh
{
private:
	int triangleCount = 0;
	
	//Ray-sphere intersection
	Eigen::Vector3d min;
	Eigen::Vector3d max;
	Eigen::Vector3d center;
	double radius;
	//--

	bool checkSphereInterception(Ray ray)
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

	void calculateTriangels(int * _triangles, int _triangleCount)
	{
		int sizeTriangles = _triangleCount;
		triangleCount = sizeTriangles / 3;
		triangles = new Triangle[triangleCount];
		int c = 0;
		for (int i = 0; i < sizeTriangles; i += 3)
		{
			//TODO: scale einbauen
			Eigen::Vector3d v1((transform.rotationMatrix * verts[_triangles[i + 0]].cwiseProduct(transform.scale)) + transform.position);
			Eigen::Vector3d v2((transform.rotationMatrix * verts[_triangles[i + 1]].cwiseProduct(transform.scale)) + transform.position);
			Eigen::Vector3d v3((transform.rotationMatrix * verts[_triangles[i + 2]].cwiseProduct(transform.scale)) + transform.position);
			triangles[c] = Triangle(v1,v2,v3);
			c++;
			checkBounds(v1);
			checkBounds(v2);
			checkBounds(v3);
		}

		center = (min + max) / 2;
		radius = (max - center).norm();

	}

public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

	_Transform transform;
	Eigen::Vector3d* verts;
	int* tris;
	int triCount;
	Triangle* triangles;
	SDL_Color color;
	Material mat;
	int vertCount;

	bool intersects(Ray ray, RaycastHit* hit,Triangle* ignore = nullptr)
	{
		if (!checkSphereInterception(ray))
		{
			return false;
		}
		int length = triangleCount;
		bool intersected = false;
		double closest = INFINITY;
		Triangle* closestTriangle = nullptr;
		Eigen::Vector3d closestPoint;
		for (int i = 0; i < length; i++)
		{
			if(&triangles[i] != ignore)
			{

				Eigen::Vector3d point;
				if(triangles[i].intersects(ray,&point))
				{
					intersected = true;
					double distance = (point - ray.origin).norm();
					if(distance < closest)
					{
						closest = distance;
						closestTriangle = &triangles[i];
						closestPoint = point;
					}
				}
			}
		}

		if(intersected)
		{
			hit->point = closestPoint;
			hit->triangle = closestTriangle;
			hit->triangleObject = *closestTriangle;
			hit->mesh = this;
		}
		return intersected;
	}

	Mesh()
	{
		min = Eigen::Vector3d(-INFINITY, -INFINITY, -INFINITY);
		max = Eigen::Vector3d(+INFINITY, +INFINITY, +INFINITY);
	}

	Mesh(Eigen::Vector3d* _verts,int _vertscount, int * _triangles, int _triangleCount, _Transform _transform, SDL_Color c)
	{
		mat = Material();
		color = c;
		verts = _verts;
		transform = _transform;
		max = Eigen::Vector3d(-INFINITY, -INFINITY, -INFINITY);
		min = Eigen::Vector3d(+INFINITY, +INFINITY, +INFINITY);
		calculateTriangels(_triangles, _triangleCount);
		tris = _triangles;
		triCount = _triangleCount;
		_vertscount = _vertscount;
	}
	Mesh(Eigen::Vector3d* _verts,int _vertCount, int * _triangles, int _triangleCount, _Transform _transform, Material material)
	{
		mat = material;
		color = material.color;
		verts = _verts;
		transform = _transform;
		max = Eigen::Vector3d(-INFINITY, -INFINITY, -INFINITY);
		min = Eigen::Vector3d(+INFINITY, +INFINITY, +INFINITY);
		calculateTriangels(_triangles, _triangleCount);
		tris = _triangles;
		triCount = _triangleCount;
		vertCount = _vertCount;
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
	
	static Mesh importFromRTMSH(std::string path, _Transform _transform, SDL_Color _c)
	{
		std::ifstream file;
		int* __triangles = 0;
		Eigen::Vector3d*  __verts = 0;

		std::string line;
		int trianglecount = 0;
		int vertcount = 0;
		file.open(path, std::ios::in);	// open in input mode
		std::cout << "Importing \"" << path << "\"." << std::endl;

		if (file.is_open()) {
			while (!file.eof())
			{
				std::getline(file, line);
				if (line[0] == 't') // triangles
				{
					char current = ',';
					int i = 2;
					while (current != ';')
					{
						current = line[i];
						if (current == ',' || current == ';')
						{
							trianglecount++;
						}
						i++;
					}

					std::cout << "Loading " << trianglecount << " triangles." << std::endl;




					__triangles = new int[trianglecount];

					std::string currentNumber = "";
					current = ',';
					i = 2;
					int j = 0;
					while (current != ';')
					{
						current = line[i];
						if (current != ',' || current != ';')
						{
							currentNumber += line[i];
						}
						if (current == ',' || current == ';')
						{
							__triangles[j++] = std::stoi(currentNumber);
							currentNumber = "";
						}
						i++;
					}
				}
				else if (line[0] == 'v')		   // verts
				{
					vertcount = 0;
					char current = ',';
					int i = 2;
					int j = 0;
					int ccounter = 0;
					while (current != ';')
					{
						current = line[i];
						if (current == ',' || current == ';')
						{
							ccounter++;
							if (ccounter > 2)
							{
								ccounter = 0;
								vertcount++;
							}
						}
						i++;
					}

					__verts = new Eigen::Vector3d[vertcount];
					std::cout << "Loading " << (vertcount) << " verticies." << std::endl;


					std::string currentNumber = "";
					current = ',';
					i = 2;
					j = 0;
					double xyz[3] = { 0,0,0 };
					int xyzCounter = 0;
					while (current != ';')
					{
						current = line[i];
						if (current != ',' || current != ';')
						{
							currentNumber += line[i];
						}
						if (current == ',' || current == ';')
						{
							xyz[xyzCounter] = std::stod(currentNumber);
							xyzCounter++;
							if (xyzCounter > 2)
							{
								xyzCounter = 0;
								__verts[j++] = Eigen::Vector3d(xyz[0], xyz[1], xyz[2]);
							}
							currentNumber = "";
						}
						i++;
					}
				}
			}
			std::cout << "Imported \"" << path << "\"." << std::endl;
			file.close();
		}
		else
		{
			std::cout << "[MESH IMPORT] ERROR: CANNOT IMPORT MESH: \"" << path << "\"." << std::endl;
		}

		return  Mesh(__verts, vertcount, __triangles, trianglecount, _transform, _c);
	}

	static Mesh importFromRTMSH(std::string path, _Transform _transform, Material m)
	{
		std::ifstream file;
		int* __triangles = 0;
		Eigen::Vector3d*  __verts = 0;

		std::string line;
		int trianglecount = 0;
		int vertcount = 0;
		file.open(path, std::ios::in);	// open in input mode
		std::cout << "Importing \"" << path << "\"." << std::endl;

		if (file.is_open()) {
			while (!file.eof())
			{
				std::getline(file, line);
				if (line[0] == 't') // triangles
				{
					char current = ',';
					int i = 2;
					while (current != ';')
					{
						current = line[i];
						if (current == ',' || current == ';')
						{
							trianglecount++;
						}
						i++;
					}

					std::cout << "Loading " << trianglecount << " triangles." << std::endl;




					__triangles = new int[trianglecount];

					std::string currentNumber = "";
					current = ',';
					i = 2;
					int j = 0;
					while (current != ';')
					{
						current = line[i];
						if (current != ',' || current != ';')
						{
							currentNumber += line[i];
						}
						if (current == ',' || current == ';')
						{
							__triangles[j++] = std::stoi(currentNumber);
							currentNumber = "";
						}
						i++;
					}
				}
				else if (line[0] == 'v')		   // verts
				{

					vertcount = 0;
					char current = ',';
					int i = 2;
					int j = 0;
					int ccounter = 0;
					while (current != ';')
					{
						current = line[i];
						if (current == ',' || current == ';')
						{
							ccounter++;
							if (ccounter > 2)
							{
								ccounter = 0;
								vertcount++;
							}
						}
						i++;
					}

					__verts = new Eigen::Vector3d[vertcount];
					std::cout << "Loading " << (vertcount) << " verticies." << std::endl;


					std::string currentNumber = "";
					current = ',';
					i = 2;
					j = 0;
					double xyz[3] = { 0,0,0 };
					int xyzCounter = 0;
					while (current != ';')
					{
						current = line[i];
						if (current != ',' || current != ';')
						{
							currentNumber += line[i];
						}
						if (current == ',' || current == ';')
						{
							xyz[xyzCounter] = std::stod(currentNumber);
							xyzCounter++;
							if (xyzCounter > 2)
							{
								xyzCounter = 0;
								__verts[j++] = Eigen::Vector3d(xyz[0], xyz[1], xyz[2]);
							}
							currentNumber = "";
						}
						i++;
					}
				}
			}
			std::cout << "Imported \"" << path << "\"." << std::endl;
			file.close();
		}
		else
		{
			std::cout << "[MESH IMPORT] ERROR: CANNOT IMPORT MESH: \"" << path << "\"." << std::endl;
		}

		return  Mesh(__verts,vertcount, __triangles, trianglecount, _transform, m);
	}
};
