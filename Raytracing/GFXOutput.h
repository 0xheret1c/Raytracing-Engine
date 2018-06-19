#include "SDL.h"
class GFXOutput
{
private:
	size_t screenHeight;
	size_t screenWidth;
	SDL_Color** screen;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	void allocScreen();
	void initSDL();
	void LOG(const char* message);


public:
	GFXOutput(unsigned int screenWidth, unsigned int screenHeight);
	~GFXOutput();
	void setPixels(SDL_Color** pixels);
	void setPixels();
	void printScreen();


};