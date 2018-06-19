#include "GFXOutput.h"
#include "Utils.h"
#include "Math.h"
#include <iostream>


#define DEBUG 1;
/*Public*/
GFXOutput::GFXOutput(unsigned int screenWidth, unsigned int screenHeight) 
{	
	/**/
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;
	this->initSDL();
	this->allocScreen();
	/**/
}
GFXOutput::~GFXOutput()
{
	//Cleanup
	SDL_DestroyTexture(this->texture);
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
	delete[] this->screen;
}

void GFXOutput::setPixels(SDL_Color** pixels)
{
	for (size_t y = 0; y < this->screenHeight; y++)
	{
		for (size_t x = 0; x < this->screenWidth; x++)
		{
			this->screen[x][y] = pixels[x][y];
		}
	}
}

void GFXOutput::setPixels()
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

void GFXOutput::printScreen() 
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

/*Private*/

void GFXOutput::LOG(const char* message)
{
#ifdef DEBUG
	std::cout << message << std::endl;
#endif // DEBUG
}

void GFXOutput::allocScreen()
{
	this->screen = new SDL_Color*[this->screenWidth];
	for (size_t i = 0; i < this->screenWidth; i++)
	{
		this->screen[i] = new SDL_Color[this->screenHeight];
	}
	this->setPixels();
}

void GFXOutput::initSDL()
{
	this->LOG("Initializing SDL...");
	SDL_Init(SDL_INIT_VIDEO);
	this->LOG("Done!");
	this->LOG("Creating window and renderer...");
	SDL_CreateWindowAndRenderer(this->screenWidth, this->screenHeight,0, &this->window, &this->renderer);
	this->LOG("Done!");
}


