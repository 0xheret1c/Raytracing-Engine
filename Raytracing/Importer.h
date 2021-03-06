#pragma once
#include <string>
#include <Windows.h>
#include <vector>

class Importer
{
private:
public:

	static std::vector<std::string> getFileNames(std::string folder)
	{	
		std::vector<std::string> names;
		std::string search_path = folder + "/*.*";
		WIN32_FIND_DATA fd;
		HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				// read all (real) files in current folder
				// , delete '!' read other 2 default folder . and ..
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					names.push_back(fd.cFileName);
				}
			} while (::FindNextFile(hFind, &fd));
			::FindClose(hFind);
		}
		return names;
	}

	static Scene importRTSC(std::string path) {
		std::vector<Mesh> meshes;
		std::vector<Light> lights;

		Scene scene = Scene();

		float x = 0;
		float y = 0;
		float z = 0;

		//OPEN STREAM
		std::ifstream fstr;
		char buffer[4];
		fstr.open(path, std::ios::binary);


		//SET CAMERA POSITION

		int frameCount = 0;
		fstr.read(reinterpret_cast<char*>(&frameCount), sizeof(int));
		Animator camAnimations;

		for (int i = 0; i < frameCount; i++) {
			// READ POSITION
			fstr.read(reinterpret_cast<char*>(&x), sizeof(float));
			fstr.read(reinterpret_cast<char*>(&y), sizeof(float));
			fstr.read(reinterpret_cast<char*>(&z), sizeof(float));
			Eigen::Vector3d position(x, y, z);

			// READ ROTATION
			fstr.read(reinterpret_cast<char*>(&x), sizeof(float));
			fstr.read(reinterpret_cast<char*>(&y), sizeof(float));
			fstr.read(reinterpret_cast<char*>(&z), sizeof(float));
			Eigen::Vector3d rotation(x, y, z);

			camAnimations.addFrame(position, rotation, Eigen::Vector3d(1, 1, 1));
		}
		
		Camera cam = Camera(200, 200, camAnimations);
		scene.camera = cam;

		//READ LIGHTS
		int lightCount = 0;
		fstr.read(reinterpret_cast<char*>(&lightCount), sizeof(int));

		for (int i = 0; i < lightCount; i++) {

			fstr.read(reinterpret_cast<char*>(&frameCount), sizeof(int));
			Animator lightAnimations;

			for (int i = 0; i < frameCount; i++) {
				// READ POSITION
				fstr.read(reinterpret_cast<char*>(&x), sizeof(float));
				fstr.read(reinterpret_cast<char*>(&y), sizeof(float));
				fstr.read(reinterpret_cast<char*>(&z), sizeof(float));
				Eigen::Vector3d position(x, y, z);

				// READ ROTATION
				fstr.read(reinterpret_cast<char*>(&x), sizeof(float));
				fstr.read(reinterpret_cast<char*>(&y), sizeof(float));
				fstr.read(reinterpret_cast<char*>(&z), sizeof(float));
				Eigen::Vector3d rotation(x, y, z);

				lightAnimations.addFrame(position, rotation, Eigen::Vector3d(1, 1, 1));
			}

			//_Transform transform(position, rotation);

			lights.push_back(Light(lightAnimations));
		}

		//READ GAMEOBJECTS
		int gameObjectsCount = 0;
		fstr.read(reinterpret_cast<char*>(&gameObjectsCount), sizeof(int));
		std::cout << "GameObjects: " << gameObjectsCount << std::endl;
		//CREATE READ BUFFER


		//Material metallicWhite = Material(Utils::getColor(0xFF0000), 0.10);

		if (gameObjectsCount > 0) {
			for (int i = 0; i < gameObjectsCount; i++) {

				std::streampos diff = fstr.tellg();
				std::cout << "Before Position Read: " << fstr.tellg() << std::endl;

				fstr.read(reinterpret_cast<char*>(&frameCount), sizeof(int));
				Animator animator;

				for (int i = 0; i < frameCount; i++) {
					// READ POSITION
					fstr.read(reinterpret_cast<char*>(&x), 4);
					fstr.read(reinterpret_cast<char*>(&y), 4);
					fstr.read(reinterpret_cast<char*>(&z), 4);
					Eigen::Vector3d position(x, y, z);

					// READ ROTATION
					fstr.read(reinterpret_cast<char*>(&x), 4);
					fstr.read(reinterpret_cast<char*>(&y), 4);
					fstr.read(reinterpret_cast<char*>(&z), 4);
					Eigen::Vector3d rotation(x, y, z);

					// READ SCALE
					fstr.read(reinterpret_cast<char*>(&x), 4);
					fstr.read(reinterpret_cast<char*>(&y), 4);
					fstr.read(reinterpret_cast<char*>(&z), 4);
					Eigen::Vector3d scale(x, y, z);

					animator.addFrame(position, rotation, scale);

					//std::cout << "After Position Read: " << fstr.tellg() << std::endl;
					//std::cout << "Difference Position Read: " << (fstr.tellg() - diff) << std::endl;
				}

				

				//_Transform transform(position, rotation, scale);

				int triangleCount = 0;
				fstr.read(reinterpret_cast<char*>(&triangleCount), sizeof(int));
				int* __triangles = new int[triangleCount];
				std::cout << "Triangles: " << triangleCount << std::endl;
				for (int tri = 0; tri < triangleCount; tri++)
				{
					int value = 0;
					fstr.read(reinterpret_cast<char*>(&value), sizeof(int));

					__triangles[tri] = value;
					//std::cout << __triangles[tri] << std::endl;
				}

				//std::cout << "Pos: " << fstr.tellg() << std::endl;
				int verticeCount = 0;
				fstr.read(reinterpret_cast<char*>(&verticeCount), sizeof(int));
				Eigen::Vector3d* __verts = new Eigen::Vector3d[verticeCount];
				std::cout << "Vertices: " << verticeCount << std::endl;

				for (int vert = 0; vert < verticeCount; vert++)
				{
					fstr.read(reinterpret_cast<char*>(&x), sizeof(float));
					fstr.read(reinterpret_cast<char*>(&y), sizeof(float));
					fstr.read(reinterpret_cast<char*>(&z), sizeof(float));
					__verts[vert] = Eigen::Vector3d(x, y, z);
					//std::cout << __verts[vert].x() << ", " << __verts[vert].y() << ", " << __verts[vert].z() << std::endl;
				}
				
				//Get Normals
				int normalCount = 0;
				fstr.read(reinterpret_cast<char*>(&normalCount), sizeof(int));
				Eigen::Vector3d* __normals = new Eigen::Vector3d[normalCount];
				std::cout << "Vertices: " << normalCount << std::endl;

				for (int norm = 0; norm < normalCount; norm++)
				{
					fstr.read(reinterpret_cast<char*>(&x), sizeof(float));
					fstr.read(reinterpret_cast<char*>(&y), sizeof(float));
					fstr.read(reinterpret_cast<char*>(&z), sizeof(float));
					__normals[norm] = Eigen::Vector3d(x, y, z);
					//std::cout << __verts[vert].x() << ", " << __verts[vert].y() << ", " << __verts[vert].z() << std::endl;
				}

				int uvCount = 0;
				fstr.read(reinterpret_cast<char*>(&uvCount), sizeof(int));
				Eigen::Vector2d* __uv = new Eigen::Vector2d[uvCount];
				std::cout << "Uv: " << uvCount << std::endl;
				
				for (int uv = 0; uv < uvCount; uv++) {
					fstr.read(reinterpret_cast<char*>(&x), sizeof(float));
					fstr.read(reinterpret_cast<char*>(&y), sizeof(float));
					__uv[uv] = Eigen::Vector2d(x, y);
				}

				float r = 0;
				float g = 0;
				float b = 0;
				float metallic = 0;
				float gloss = 0;
				fstr.read(reinterpret_cast<char*>(&r), sizeof(float));
				fstr.read(reinterpret_cast<char*>(&g), sizeof(float));
				fstr.read(reinterpret_cast<char*>(&b), sizeof(float));
				fstr.read(reinterpret_cast<char*>(&metallic), sizeof(float));
				fstr.read(reinterpret_cast<char*>(&gloss), sizeof(float));

				std::cout << "Gloss: " << gloss << std::endl;

				int texWidth = 0;
				int texHeight = 0;
				fstr.read(reinterpret_cast<char*>(&texWidth), sizeof(int));
				fstr.read(reinterpret_cast<char*>(&texHeight), sizeof(int));

				std::cout << "Texture Width: " << texWidth << std::endl;
				std::cout << "Texture Height: " << texHeight << std::endl;

				Eigen::Vector3f** texture_color_map = new Eigen::Vector3f*[texWidth];
				for (int w = 0; w < texWidth; w++) {
					texture_color_map[w] = new Eigen::Vector3f[texHeight];
					for (int h = 0; h < texHeight; h++) {
						fstr.read(reinterpret_cast<char*>(&x), sizeof(float));
						fstr.read(reinterpret_cast<char*>(&y), sizeof(float));
						fstr.read(reinterpret_cast<char*>(&z), sizeof(float));
						texture_color_map[w][h] = Eigen::Vector3f(x, y, z);
					}
				}
				Texture tex = Texture(texWidth, texHeight, texture_color_map);

				Eigen::Vector3f col = Eigen::Vector3f(r, g, b);
				std::cout << "color: {" << r << ", " << g << ", " << b << "}" << std::endl;
				Material m = Material(col, metallic, gloss);

				Mesh mesh(__verts, verticeCount, __normals, normalCount, __uv, uvCount, __triangles, triangleCount, animator, m, tex);
				//meshes[i] = mesh;
				meshes.push_back(mesh);

				std::cout << "Difference Total Read: " << (fstr.tellg() - diff) << std::endl;
			}
		}

		fstr.close();

		scene.setLights(lights, lightCount);
		scene.setMeshes(meshes, gameObjectsCount);

		return scene;
	}

	static Scene importScene(std::string path, unsigned int _width, unsigned int _height) {
		Scene scene = Importer::importRTSC(path);
		scene.camera.setSize(_width, _height);
		return scene;
	}

	static Scene importScene(std::string path, unsigned int _width, unsigned int _height, size_t _density) {
		Scene scene = Importer::importRTSC(path);
		scene.camera.setSize(_width, _height);
		scene.camera.setDensity(_density);
		return scene;
	}

	static Scene importScene(std::string path, unsigned int _width, unsigned int _height, size_t _density, size_t _bounces) {
		Scene scene = Importer::importRTSC(path);
		scene.camera.setSize(_width, _height);
		scene.camera.setDensity(_density);
		scene.camera.setMaxBounces(_bounces);
		return scene;
	}
};