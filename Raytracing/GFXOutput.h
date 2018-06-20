#pragma once
#include "Utils.h"
#include "Math.h"
#include "SDL.h"
#include <iostream>

class GFXOutput
{
private:
	size_t screenHeight;
	size_t screenWidth;
	SDL_Color** screen;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;



	void allocScreen()
	{
		this->screen = new SDL_Color*[this->screenWidth];
		for (size_t i = 0; i < this->screenWidth; i++)
		{
			this->screen[i] = new SDL_Color[this->screenHeight];
		}
		this->setPixels();
	}

	void initSDL()
	{
		Utils::LOG("Initializing SDL...");
		SDL_Init(SDL_INIT_VIDEO);
		Utils::LOG("Done!");
		Utils::LOG("Creating window and renderer...");
		SDL_CreateWindowAndRenderer(this->screenWidth, this->screenHeight, 0, &this->window, &this->renderer);
		Utils::LOG("Done!");
	}


public:
	GFXOutput(unsigned int screenWidth, unsigned int screenHeight)
	{
		/**/
		this->screenHeight = screenHeight;
		this->screenWidth = screenWidth;
		this->initSDL();
		this->allocScreen();
		/**/
	}
	~GFXOutput()
	{
		//Cleanup
		SDL_DestroyTexture(this->texture);
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		SDL_Quit();
		delete[] this->screen;
	}
	void setPixels(SDL_Color** pixels)
	{
		for (size_t y = 0; y < this->screenHeight; y++)
		{
			for (size_t x = 0; x < this->screenWidth; x++)
			{
				this->screen[x][y] = pixels[x][y];
			}
		}
	}
	void setPixels()
	{

		for (size_t y = 0; y < this->screenHeight; y++)
		{
			for (size_t x = 0; x < this->screenWidth; x++)
			{
				this->screen[x][y].a = 255;
				this->screen[x][y].r = 155;
				this->screen[x][y].g = 66;
				this->screen[x][y].b = 244;
			}
		}
	}
	void printScreen()
	{
		for (size_t y = 0; y < this->screenHeight; y++)
		{
			for (size_t x = 0; x < this->screenWidth; x++)
			{

				SDL_Color c = this->screen[x][y];
				SDL_SetRenderDrawColor(this->renderer, c.r, c.g, c.b, c.a);
				SDL_RenderDrawPoint(this->renderer, x, y);
			}
		}
		SDL_RenderPresent(this->renderer);
	}
};



