#pragma once

class Renderer
{
private:
	static Eigen::Vector3f traceRay(Scene* scene, Ray ray, size_t bounces)
	{
		double epsilon = std::numeric_limits<double>::epsilon();
		Eigen::Vector3f color(0, 0, 0);
		double angle = (-(acos(ray.direction.dot(Eigen::Vector3d::UnitY())) / (M_PI / 2.0)));
		angle = abs(angle);
		angle = Our_math::clamp01(angle);
		color = Eigen::Vector3f(255, 255, 255) - angle * (Eigen::Vector3f(255, 255, 255) - Eigen::Vector3f(0x19, 0x2c, 0xb7));
		if (bounces > scene->camera.maxBounces) {
			return color;
		}

		RaycastHit hit;
		if (scene->intersects(ray, &hit))
		{
			double intensity = Our_math::clamp01(scene->getIllumination(hit.point, hit.n));
			color[0] = hit.mesh->color.r * intensity;
			color[1] = hit.mesh->color.g * intensity;
			color[2] = hit.mesh->color.b * intensity;

			if (bounces <= scene->camera.maxBounces) {
				Eigen::Vector3d reflection = ray.direction.normalized() - (2.0 * (ray.direction.normalized().dot(hit.n) * hit.n));
				/*Ray nRay = Ray(hit.point, reflection.normalized(), scene);
				color = color * (1.0 - hit.mesh->mat.reflectiveness);
				color += traceRay(scene, nRay, bounces + 1, hit.triangle) * hit.mesh->mat.reflectiveness;*/
				Ray nRay = Ray(hit.point + hit.n * (epsilon * 100), reflection.normalized(), scene);
				color = color * (1.0 - (hit.mesh->mat.reflectiveness * intensity));
				if (hit.mesh->mat.hasGloss) {
					color += calculateGloss(scene, nRay, bounces + 1, hit.mesh->mat) * hit.mesh->mat.reflectiveness * intensity;
				}
				else {
					color += traceRay(scene, nRay, bounces + 1) * hit.mesh->mat.reflectiveness * intensity;
				}
			}
		}

		return Utils::clampColor(color);
	}

	static Eigen::Vector3f calculateGloss(Scene* scene, Ray reflectionRay, size_t bounces, Material m) {
		Eigen::Vector3f color(0, 0, 0);
		
		Eigen::Vector3d u = Eigen::Vector3d::UnitY().cross(reflectionRay.direction).normalized();
		Eigen::Vector3d v = u.cross(reflectionRay.direction).normalized();

		unsigned int width = m.amount;
		unsigned int height = m.amount;
		double maxAngle = m.angle;

		for (int w = 0; w < width; w++) {
			for (int h = 0; h < height; h++) {
				double angleRadX = ((maxAngle / (width - 1.0)) * w) - (maxAngle / 2.0);
				angleRadX *= M_PI / 180.0;
				double angleRadY = ((maxAngle / (height - 1.0)) * h) - (maxAngle / 2.0);
				angleRadY *= M_PI / 180.0;
				double _x = tan(angleRadX);
				double _y = tan(angleRadY);
				
				Eigen::Vector3d direction = reflectionRay.direction;
				direction += u * angleRadX;
				direction += v * angleRadY;

				Ray nRay = Ray(reflectionRay.origin, direction.normalized(), scene);
				color += traceRay(scene, nRay, bounces);
			}
		}
		color /= (width * height);
		return color;
	}

	/*static Eigen::Vector3d getRandomRayInHemisphere(Eigen::Matrix3d n) {
		double _x = tan(rand() * 0.05 + 0.025);
		double _y = tan(rand() * 0.05 + 0.025);
		double _z = 1;
		Eigen::Vector3d direction = Eigen::Vector3d(_x, _y, _z);
		direction = n * direction;
		return direction;
	}*/

public:
	static SDL_Color** render(Scene* scene) {
		std::cout << "Camera Position: " << scene->camera.transform.position << std::endl;
		std::cout << "Get Width: " << scene->camera.width << std::endl;
		std::cout << "Get Height: " << scene->camera.height << std::endl;

		//Debug
		std::cout << "Started tracing... this might take a while!" << std::endl;
		const clock_t begin_time = clock();
		size_t pixelToTrace = scene->camera.height * scene->camera.width;
		size_t tracedPixel = 0;
		size_t lastPercent = 0;

		//--
		//Eigen::Matrix3d m = transform.rotation.toRotationMatrix(); // Funktioniert eventuell nicht
		double fovX = scene->camera.fov * ((double)scene->camera.width / (double)scene->camera.height);
		double fovY = scene->camera.fov;

		SDL_Color** returnArray;
		returnArray = new SDL_Color*[scene->camera.width];
		for (size_t x = 0; x < scene->camera.width; x++)
		{
			returnArray[x] = new SDL_Color[scene->camera.height];
			for (size_t y = 0; y < scene->camera.height; y++)
			{
				returnArray[x][scene->camera.height - y - 1] = SDL_Color();
				returnArray[x][scene->camera.height - y - 1].r = 0;
				returnArray[x][scene->camera.height - y - 1].g = 0;
				returnArray[x][scene->camera.height - y - 1].b = 120;
				returnArray[x][scene->camera.height - y - 1].a = 255;

				double r = 0;
				double g = 0;
				double b = 0;
				double a = 0;

				for (size_t z = 0; z < scene->camera.density * scene->camera.density; z++)
				{
					double angleRadX = (fovX / ((scene->camera.width - 1.0) * scene->camera.density)) * ((x*scene->camera.density) + (z%scene->camera.density)) - (fovX / 2.0);
					angleRadX *= M_PI / 180.0;
					double angleRadY = (fovY / ((scene->camera.height - 1.0) * scene->camera.density)) * ((y*scene->camera.density) + (z / scene->camera.density)) - (fovY / 2.0);
					angleRadY *= M_PI / 180.0;

					double _x = tan(angleRadX) * scene->camera.screenDistance;
					double _y = tan(angleRadY) * scene->camera.screenDistance;
					double _z = scene->camera.screenDistance;
					Eigen::Vector3d direction = Eigen::Vector3d(_x, _y, _z);



					direction = scene->camera.transform.rotationMatrix * direction;

					/*RaycastHit hit;

					if (traceRay(direction,&hit,0))
					{
					//Uint8 color = (Uint8)(Our_math::clamp01(hit.intensity) * 0xFF);
					r += Our_math::clamp01((hit.color.r / 0xFF) * hit.intensity);
					g += Our_math::clamp01((hit.color.g / 0xFF) * hit.intensity);
					b += Our_math::clamp01((hit.color.b / 0xFF)* hit.intensity);
					}*/

					Ray ray = Ray(scene->camera.transform.position, direction.normalized(), scene);

					Eigen::Vector3f col = traceRay(scene, ray, 0);
					r += col[0];
					g += col[1];
					b += col[2];
				}
				r /= (scene->camera.density * scene->camera.density);
				g /= (scene->camera.density * scene->camera.density);
				b /= (scene->camera.density * scene->camera.density);

				/*returnArray[x][height - y - 1].r = (Uint8)(Our_math::clamp01(r) * 0xFF);
				returnArray[x][height - y - 1].g = (Uint8)(Our_math::clamp01(g) * 0xFF);
				returnArray[x][height - y - 1].b = (Uint8)(Our_math::clamp01(b) * 0xFF);*/

				returnArray[x][scene->camera.height - y - 1].r = (Uint8)r;
				returnArray[x][scene->camera.height - y - 1].g = (Uint8)g;
				returnArray[x][scene->camera.height - y - 1].b = (Uint8)b;

				tracedPixel++;
			}

			//Debug
			size_t percent = (size_t)(((float)tracedPixel / (float)pixelToTrace) * 100);
			if (percent % 1 == 0 && percent != lastPercent)
			{
				float timePassedSecs = float(clock() - begin_time) / CLOCKS_PER_SEC;
				lastPercent = percent;
				float timeRemaining = (100 - percent) * (timePassedSecs / (percent));
				std::cout << "Traced " << percent << "% "
					<< tracedPixel << "/" << pixelToTrace << " pixels traced. "
					<< tracedPixel * (scene->camera.density * scene->camera.density) << "/" << pixelToTrace * (scene->camera.density * scene->camera.density) << " rays casted."
					<< " Est. Time Remaining: " << timeRemaining << " seconds."
					<< std::endl;
			}
		}
		float timePassedSecs = float(clock() - begin_time) / CLOCKS_PER_SEC;
		std::cout << "Trame finished in " << timePassedSecs << " seconds / " << 1 / timePassedSecs << " FPS." << std::endl;
		return returnArray;
	}
};