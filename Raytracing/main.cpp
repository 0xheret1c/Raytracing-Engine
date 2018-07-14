#define __DEBUG 1 // Debug mode

#include <stdio.h>
#include <vector>
#include <iostream>
#include "./Core.h"
#include "Light.h"
#include "Primitive.h"
#include "Material.h"
#include "e_colors.h"
#include "Renderer.h"
#include "Importer.h"
#include "Menu.h"

//Prototype
unsigned int WIDTH =  1000;
unsigned int HEIGHT = 750;
size_t density = 1;
size_t bounces = 2;
size_t animationStartFrame = 1;
size_t animationEndFrame = 1;
std::string sceneToRender;

using namespace Eigen;

void menu()
{
	std::string icon = "  **************************************************\r\n                   `-/osyso/-`                 \r\n                `-+hmMMMNNNMMMmh+-`            \r\n             `:sdMMMMd+:::::+dMMMMds-`         \r\n         `-+ymMMMMMN/`/syyys/`/NMMMMMmy/.`     \r\n    `.:+ydNMMMMMMMMs oyyyyyyyo sMMMMMMMMNdy+:.`\r\n    `.:+ydNMMMMMMMMs oyyyyyyyo sMMMMMMMMMNds/.`\r\n         `-+hmMMMMMN/`+syyys+`/NMMMMMMmy/.`    \r\n             .:smMMMMh/::-::/hMMMMNho-`        \r\n                `-ohmMMNNmNNMMNds/.            \r\n                    `-/osyso/-.`               \r\n\r\n  ************************************************** ";
	std::string header = icon + "\r\n";
	std::string message;
	std::vector<std::string> fileNames = Importer::getFileNames(".\\Scenes");
	std::string* elements = &fileNames[0];
	size_t elementsc = fileNames.size();
	int areYouSure = 0;
	int selection = 0;
	do
	{
		message = header + "  Select the scene you want to render.\r\n  Press arrow up and down to navigate and enter to confirm.\r\n  ";
		selection = Menu::menu(message, elements, elementsc, 200);
		message = header + "  Do you want to render \"" + elements[selection] + "\"?\r\n";
		areYouSure = Menu::yesOrNo(message,200);
	}
	while(areYouSure != 1);
	sceneToRender = ".\\Scenes\\" + fileNames[selection];
	
	areYouSure = 0;
	do
	{
		message = header + "  Set window-width:";
		WIDTH = std::stoi(Menu::inputPrompt(message, "  WIDTH: "));
		message = header + "  Set window-height:";
		HEIGHT = std::stoi(Menu::inputPrompt(message, "  HEIGHT: "));
		message = header + "  Set density: (Will greatly increase rendering time. Recommended: 1-2)";
		density = std::stoi(Menu::inputPrompt(message, "  DENSITY: "));
		message = header + "  Set bounces: (Will greatly increase rendering time. Recommended: 0-3)";
		bounces = std::stoi(Menu::inputPrompt(message, "  BOUNCES: "));
		message = header + "  Set animation-start-frame: (Set to 0 for no animation.)";
		animationStartFrame = std::stoi(Menu::inputPrompt(message, "  ANIMATION-START-FRAME: "));
		message = header + "  Set animation-end-frame: (Set to 1 for no animation.)";
		animationEndFrame = std::stoi(Menu::inputPrompt(message, "  ANIMATION-END-FRAME: "));

		message = header + "  Are the following correct? If you continue, the render sequence will start,\r\n  this might take some time."+ 
		  "\r\n\r\n  SCENE:................... " + sceneToRender
			+ "\r\n  WIDTH:................... " + std::to_string(WIDTH)
			+ "\r\n  HEIGHT:.................. " + std::to_string(HEIGHT)
			+ "\r\n  DENSITY:................. " + std::to_string(density)
			+ "\r\n  BOUNCES:................. " + std::to_string(bounces) 
			+ "\r\n  ANIMATION-START-FRAME:... " + std::to_string(animationStartFrame)
			+ "\r\n  ANIMATION-END-FRAME:..... " + std::to_string(animationEndFrame)
			+ "\r\n";
		areYouSure = Menu::yesOrNo(message, 200);
	} while (areYouSure != 1);
	system("cls");

}

int main(int argc, char* argv[])
{
	
	menu();
	GFXOutput out = GFXOutput(WIDTH, HEIGHT);
	Scene scene = Importer::importScene(sceneToRender, WIDTH, HEIGHT, density, bounces);
	int rendered = animationStartFrame;

	scene.setFrame(animationStartFrame);

	while (rendered < animationEndFrame) {
		SDL_Color** screen = Renderer::render(&scene);
		out.setPixels(screen);
		out.initSDL();

		rendered++;
		std::string frameNumber = "";
		std::string renderedNumber = std::to_string(rendered);
		int renderedLength = renderedNumber.length();
		int zeroes = 5;
		for (size_t i = 0; i < (zeroes - renderedLength); i++)
		{
			frameNumber += "0";
		}
		frameNumber += renderedNumber;
		out.screenshotBMP(".\\LastTraces\\lastTraceFrame " + frameNumber+".bmp");
		scene.update();
		out.destroy();
	}

	

	return 0;
}