#pragma once
#include <iostream>
class ArgHandler
{
private:
	static void loadSceneFromPath(const char* path){}
public:

	// 0 = Continue after argHandler
	// 1 = Quit after argHandler
	//-1 = Quit.
	static int handleArgs(int argc, char* argv[])
	{

		if (argc <= 0)
		{ 
			std::cout << "No args." << std::endl;
			return 0;
		}
		for (int i = 0; i < argc; i++)
		{
			if (argv[i] == "-p") // Render scene from path.
			{
				std::cout << "Rendering scene from \"" << argv[++i] << "\"." << std::endl;
				loadSceneFromPath(argv[i]);
			}
			else
			{
				std::cout << "Unknown argument \"" << argv[i] << std::endl;
				return -1;
			}
		}	
		return 1;
	}
};
