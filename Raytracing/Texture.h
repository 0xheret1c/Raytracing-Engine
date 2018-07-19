#pragma once

class Texture {
private:
	Eigen::Vector3f **color_map;
	int width = -1;
	int height = -1;
public:
	Texture() {

	}

	Texture(int _width, int _height, Eigen::Vector3f **_color_map) {
		width = _width;
		height = _height;
		color_map = _color_map;
	}

	/*Eigen::Vector3f getPixel(int x, int y) {
		if (width == 0 || height == 0 || x >= width || y >= height) {
			return Eigen::Vector3f(1, 1, 1);
		}
		return color_map[x][y];
	}*/

	Eigen::Vector3f getPixel(double x, double y) {
		if (width == 0 || height == 0) {
			return Eigen::Vector3f(1, 1, 1);
		}
		return color_map[(int)(x * (width-1.0))][(int)(y * (height-1.0))];
	}

	SDL_Color** output() {
		SDL_Color** returnArray = new SDL_Color*[width];
		for (int x = 0; x < width; x++) {
			returnArray[x] = new SDL_Color[height];
			for (int y = 0; y < height; y++) {
				returnArray[x][y].r = (Uint8)(color_map[x][y][0] * 255);
				returnArray[x][y].g = (Uint8)(color_map[x][y][1] * 255);
				returnArray[x][y].b = (Uint8)(color_map[x][y][2] * 255);
			}
		}
		return returnArray;
	}

	int getWidth() {
		return width;
	}

	int getHeight() {
		return height;
	}
};