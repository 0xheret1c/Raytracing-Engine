#pragma once
#include "SDL.h"
#include "Utils.h"
#include "e_colors.h"

class Material
{
private:

public:
	double reflectiveness = 0.05;
	double diffuse = 0;
	size_t amount = 0;
	SDL_Color color;

	Material(SDL_Color _color, double _reflectiveness, double _diffuse, size_t _amount)
	{
		color = _color;
		reflectiveness = _reflectiveness;
		diffuse = _diffuse;
		amount = _amount;
	}
	Material(SDL_Color _color, double _reflectiveness)
	{
		color = _color;
		reflectiveness = _reflectiveness;
	}
	Material()
	{
		color = Utils::getColor(e_Colors::magenta);
	}

	static Material importFromRTMAT();
};