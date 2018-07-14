#pragma once
#include "SDL.h"
#include "Utils.h"
#include "e_colors.h"

class Material
{
private:

public:
	double reflectiveness = 0.05;
	double gloss = 0;
	double angle = 0;
	unsigned int amount = 0;
	bool hasGloss = false;
	SDL_Color color;

	Material(SDL_Color _color, double _reflectiveness, double _gloss)
	{
		color = _color;
		reflectiveness = _reflectiveness;
		gloss = _gloss;
		if (gloss <= 0) {
			hasGloss = false;
		}
		else {
			hasGloss = true;
			amount = gloss * 25;
			angle = gloss * 5;
		}
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