#pragma once
#include "Utils.h"
#include "Math.h"
#include "SDL.h"
#include <iostream>
#ifndef __GFXOUTPUT_H_INCLUDED__
#define __GFXOUTPUT_H_INCLUDED__

class GFXOutput
{
private:
	bool quit = false;
	SDL_Event event;

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

	


public:
	void initSDL()
	{
		Utils::LOG("|\tInitializing SDL...");
		SDL_Init(SDL_INIT_VIDEO);
		Utils::LOG("|\tCreating window and renderer...");
		SDL_CreateWindowAndRenderer((int)this->screenWidth, (int)this->screenHeight, 0, &this->window, &this->renderer);
		while (!quit)
		{
			this->printScreen();
			SDL_WaitEvent(&event);
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			}
		}
		SDL_DestroyTexture(this->texture);
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		SDL_Quit();
		for (size_t i = 0; i < this->screenWidth; i++)
		{
			delete[] this->screen[i];
		}
		delete[] this->screen;
	}

	GFXOutput(unsigned int screenWidth, unsigned int screenHeight)
	{
		Utils::LOG("|\tCreating GFXOutput-object.");
		/**/
		this->screenHeight = screenHeight;
		this->screenWidth = screenWidth;
		this->allocScreen();
		/*
		this->initSDL();
		while (!quit)
		{
			this->printScreen();
			SDL_WaitEvent(&event);
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			}
		}
		*/
	}
	~GFXOutput()
	{
		//Cleanup
		SDL_DestroyTexture(this->texture);
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		SDL_Quit();
		for (size_t i = 0; i < this->screenWidth; i++)
		{
			delete[] this->screen[i];
		}
		delete[] this->screen;
	}
	void setPixels(SDL_Color** pixels)
	{
		for (size_t y = 0; y < this->screenHeight; y++)
		{
			for (size_t x = 0; x < this->screenWidth; x++)
			{
				//std::cout << "Setting pixel X: " << x << " Y: " << y;
				//std::cout << " Color R: " << pixels[x][y].r << " G: " << pixels[x][y].g << " B: " << pixels[x][y].b << std::endl;
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
				SDL_RenderDrawPoint(this->renderer, (int)x, (int)y);
			}
		}
		SDL_RenderPresent(this->renderer);
	}

};
#endif