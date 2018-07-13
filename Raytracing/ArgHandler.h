#pragma once
#include <iostream>
#include <string>
class argHandler
{
private:
	static void loadSceneFromPath(const char* path){}
	static void setBounces(unsigned int value) {}
	static void setFov(unsigned int value) {}
	static void setDensity(unsigned int value){}
	static void setGlobalIllumination(unsigned int value){}
	static void printHelp()
	{
		std::cout << "-p or --path                 <path>. Loads and renders a scene from the given path." << std::endl;
		std::cout << "-f or --fov                 <value>. Sets the fov to the given value." << std::endl;
		std::cout << "-d or --density             <value>. Sets the density to the given value." << std::endl;
		std::cout << "-b or --bounces             <value>. Sets the bounces to the given value." << std::endl;
		std::cout << "-g or --global-illumination <value>. Sets the global-illumination to the given value." << std::endl;
		std::cout << "-h or --help Shows this help screen." << std::endl;
	}
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
			if (argv[i] == "-p" || argv[i] == "--path") // Render scene from path.
			{
				std::cout << "Rendering scene from \"" << argv[++i] << "\"." << std::endl;
				loadSceneFromPath(argv[i]);
			}
			else if(argv[i] == "-b"  || argv[i] == "--bounces")
			{
				std::cout << "Set bounces to " << argv[++i] << "."<< std::endl;
				setBounces(std::stoi(argv[i]));
			}
			else if (argv[i] == "-f" || argv[i] == "--fov")
			{
				std::cout << "Set fov to " << argv[++i] << "." << std::endl;
				setFov(std::stoi(argv[i]));
			}
			else if (argv[i] == "-d" || argv[i] == "--density") 
			{
				std::cout << "Set density to " << argv[++i] << "." << std::endl;
				setDensity(std::stoi(argv[i]));
			}
			else if (argv[i] == "-g" || argv[i] == "--global-illumination")
			{
				std::cout << "Set global-illumination to " << argv[++i] << "." << std::endl;
				setGlobalIllumination(std::stoi(argv[i]));
			}
			else if (argv[i] == "-h" || argv[i] == "--help")
			{
				printHelp();
				return -1;
			}
			else
			{
				std::cout << "Unknown argument \"" << argv[i];
				std::cout << "\". Type -h or --help for help." << std::endl;
				std::cout << "Exiting." << std::endl;
				return -1;
			}
		}	
		return 1;
	}
};
