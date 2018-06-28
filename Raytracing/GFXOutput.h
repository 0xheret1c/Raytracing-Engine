#pragma once
#include "Utils.h"
#include "Math.h"
#include "SDL.h"
#include <fstream>
#include <string>
#include <iostream>



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
		Utils::LOG("Initializing SDL...");
		SDL_Init(SDL_INIT_VIDEO);
		Utils::LOG("Creating window and renderer...");
		SDL_CreateWindowAndRenderer((int)this->screenWidth, (int)this->screenHeight, 0, &this->window, &this->renderer);
		this->printScreen();
		this->screenshotBMP(".\\LastTraces\\lastTrace.bmp");
		/*while (!quit)
		{

			SDL_WaitEvent(&event);
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			}
		}*/
		/*SDL_DestroyTexture(this->texture);
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		SDL_Quit();
		for (size_t i = 0; i < this->screenWidth; i++)
		{
			delete[] this->screen[i];
		}
		delete[] this->screen;*/
	}

	GFXOutput(unsigned int screenWidth, unsigned int screenHeight)
	{
		
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



	void screenshotBMP(std::string fileName)
	{

		SDL_Surface *sshot = SDL_CreateRGBSurface(0, screenWidth, screenHeight, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
		
		size_t lastIndex = fileName.length() - 1;
		std::string extention = fileName.substr(fileName.length() - 4, 4);
		if (extention == ".bpm")
		{
			fileName += ".bpm";
		}
		size_t i = 1;
		std::string toCheck = fileName;
		std::string temp = fileName;
		while (Utils::fileExists(toCheck.c_str()))
		{

			toCheck = temp.insert(temp.length() - 4,std::to_string(i));
			temp = fileName;
			i++;
		}
		fileName = toCheck;
		SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
		SDL_SaveBMP(sshot, fileName.c_str());
		SDL_FreeSurface(sshot);
	}

	static void screenshotBMP(char* fileName, SDL_Color** screen, size_t screenW, size_t screenH)
	{

		
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