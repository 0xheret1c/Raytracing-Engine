#pragma once

//Forward declarations
class RaycastHit;

//Includes
#include <iostream>
#include <fstream>	// Importing meshs from filesystem.
#include "_Transform.h"
#include "Triangle.h"
#include "Ray.h"



class Mesh
{
private:
	size_t triangleCount = 0;
	void calculateTriangels(size_t * _triangles, size_t _triangleCount)
	{
		size_t sizeTriangles = _triangleCount;
		triangleCount = sizeTriangles / 3;
		triangles = new Triangle[triangleCount];
		size_t c = 0;
		for (size_t i = 0; i < sizeTriangles; i += 3)
		{
			//TODO: scale einbauen
			Eigen::Vector3d v1((transform.rotationMatrix * verts[_triangles[i + 0]].cwiseProduct(transform.scale)) + transform.position);
			Eigen::Vector3d v2((transform.rotationMatrix * verts[_triangles[i + 1]].cwiseProduct(transform.scale)) + transform.position);
			Eigen::Vector3d v3((transform.rotationMatrix * verts[_triangles[i + 2]].cwiseProduct(transform.scale)) + transform.position);
			triangles[c] = Triangle(v1,v2,v3);
			c++;
		}

	}

public:
	//EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
	_Transform transform;
	Eigen::Vector3d* verts;
	Triangle* triangles;
	SDL_Color color;

	bool intersects(Ray ray, RaycastHit* hit,Triangle* ignore = nullptr)
	{
		size_t length = triangleCount;

		bool intersected = false;
		double closest = INFINITY;
		Triangle* closestTriangle = nullptr;
		Eigen::Vector3d closestPoint;
		for (size_t i = 0; i < length; i++)
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

	}
	Mesh(Eigen::Vector3d* _verts,size_t * _triangles, size_t _triangleCount ,_Transform _transform, SDL_Color c)
	{
		color = c;
		verts = _verts;
		transform = _transform;
		calculateTriangels(_triangles, _triangleCount);
	}
	~Mesh()
	{
		//TODO: VERTS CLEAR FIXEN!!!!
		delete[] verts;
		delete[] triangles;
	}
	
	static Mesh importFromRTMSH(std::string path, _Transform _transform, SDL_Color _c)
	{
		std::ifstream file;
		size_t* __triangles = 0;
		Eigen::Vector3d*  __verts = 0;

		std::string line;
		int trianglecount = 0;

		file.open(path,std::ios::in);	// open in input mode
		std::cout << "Importing \"" << path << "\"." << std::endl;

		if (file.is_open()) {
			while (!file.eof())
			{
				std::getline(file, line);
				if(line[0] == 't') // triangles
				{
					char current = ',';
					size_t i = 2;
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
					



					__triangles = new size_t[trianglecount];

					std::string currentNumber = "";
					current = ',';
					i = 2;
					size_t j = 0;
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
				else if(line[0] == 'v')		   // verts
				{

					size_t vertcount = 0;
					char current = ',';
					size_t i = 2;
					size_t j = 0;
					size_t ccounter = 0;
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
					double xyz[3] = {0,0,0};
					size_t xyzCounter = 0;
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
								__verts[j++] = Eigen::Vector3d(xyz[0],xyz[1],xyz[2]);
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
		
		return  Mesh(__verts, __triangles, trianglecount, _transform, _c);
	}
};
