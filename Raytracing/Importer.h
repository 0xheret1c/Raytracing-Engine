#pragma once

class Importer
{
private:
public:

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

		_Transform transform(position, rotation);

		
		Camera cam = Camera(200, 200, transform);
		scene.camera = cam;

		//READ LIGHTS
		int lightCount = 0;
		fstr.read(reinterpret_cast<char*>(&lightCount), sizeof(int));

		for (int i = 0; i < lightCount; i++) {
			fstr.read(reinterpret_cast<char*>(&x), sizeof(float));
			fstr.read(reinterpret_cast<char*>(&y), sizeof(float));
			fstr.read(reinterpret_cast<char*>(&z), sizeof(float));
			Eigen::Vector3d position(x, y, z);

			// READ ROTATION
			fstr.read(reinterpret_cast<char*>(&x), sizeof(float));
			fstr.read(reinterpret_cast<char*>(&y), sizeof(float));
			fstr.read(reinterpret_cast<char*>(&z), sizeof(float));
			Eigen::Vector3d rotation(x, y, z);

			_Transform transform(position, rotation);

			lights.push_back(Light(transform));
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

				std::cout << "After Position Read: " << fstr.tellg() << std::endl;
				std::cout << "Difference Position Read: " << (fstr.tellg() - diff) << std::endl;

				_Transform transform(position, rotation, scale);

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

				int r = 0;
				int g = 0;
				int b = 0;
				float gloss = 0;
				fstr.read(reinterpret_cast<char*>(&r), sizeof(int));
				fstr.read(reinterpret_cast<char*>(&g), sizeof(int));
				fstr.read(reinterpret_cast<char*>(&b), sizeof(int));
				fstr.read(reinterpret_cast<char*>(&gloss), sizeof(float));

				SDL_Color col = { r, g, b };
				Material m = Material(col, gloss);

				Mesh mesh(__verts, verticeCount, __triangles, triangleCount, transform, m);
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