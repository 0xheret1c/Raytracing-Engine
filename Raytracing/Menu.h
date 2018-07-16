#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>

class Menu
{
private:

	static void printLogo()
	{
		Utils::setConsoleColor(15);
		std::cout << "  **************************************************\r\n";
		std::cout << "                   `-/osyso/-`                 \r\n";
		std::cout << "                `-+hmMMMNNNMMMmh+-`            \r\n";
		std::cout << "             `:sdMMMMd+:::::+dMMMMds-`         \r\n";
		std::cout << "         `-+ymMMMMMN/`/";
		Utils::setConsoleColor(12);
		std::cout << "syyys";
		Utils::setConsoleColor(15);
		std::cout << " / `/NMMMMMmy / .`     \r\n";
		std::cout << "    `.:+ydNMMMMMMMMs ";
		Utils::setConsoleColor(12);
		std::cout << "oyyyyyyyo";
		Utils::setConsoleColor(15);
		std::cout << " sMMMMMMMMNdy+:.`\r\n";
		std::cout << "    `.:+ydNMMMMMMMMs ";
		Utils::setConsoleColor(12);
		std::cout << "oyyyyyyyo";
		Utils::setConsoleColor(15);
		std::cout << " sMMMMMMMMMNds/.`\r\n";
		std::cout << "         `-+hmMMMMMN/";
		Utils::setConsoleColor(12);
		std::cout << "`+syyys+`";
		Utils::setConsoleColor(15);
		std::cout << "/NMMMMMMmy/.`    \r\n";
		std::cout << "             .:smMMMMh/::";
		Utils::setConsoleColor(12);
		std::cout << "-";
		Utils::setConsoleColor(15);
		std::cout << "::/hMMMMNho-`        \r\n";
		std::cout << "                `-ohmMMNNmNNMMNds/.            \r\n";
		std::cout << "                    `-/osyso/-.`               \r\n";
		std::cout << "                      VIS";
		Utils::setConsoleColor(12);
		std::cout << "I";
		Utils::setConsoleColor(15);
		std::cout << "ON                   \r\n";
		std::cout << "  **************************************************\r\n";
	}


	static void setCursorPos(int x, int y)
	{
		COORD p = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
	}
	static void drawMenu(std::string message, std::string* elements,size_t elementsc, size_t selectionPos)
	{
		setCursorPos(0, 0);
		std::string cursor   = ">> ";
		std::string noCursor = "   ";
		std::string afterCursor   = " <<";
		std::string afterNoCursor = "   ";
		std::string offset = "";
		printLogo();
		std::cout << message << std::endl;
		for (size_t i = 0; i < elementsc; i++)
		{
			if (selectionPos == i)
			{
				Utils::setConsoleColor(12);
				std::cout << offset << cursor << elements[i] << afterCursor << std::endl;
				Utils::setConsoleColor(15);
			}

			else
				std::cout << offset << noCursor << elements[i]<< afterNoCursor << std::endl;
		}
	}
	static size_t keyPressed()
	{
		while (true)
		{
			if (GetKeyState(VK_UP) & 0x8000)
			{
				return VK_UP;
			}
			else if(GetKeyState(VK_DOWN) & 0x8000)
			{
				return VK_DOWN;
			}
			else if(GetKeyState(VK_RETURN) & 0x8000)
			{
				return VK_RETURN;
			}
		}
	}
	static void showConsoleCursor(bool showFlag)
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = showFlag; 
		SetConsoleCursorInfo(out, &cursorInfo);
	}
public:
	static int menu(std::string message,std::string* elements, size_t elementsc,size_t delayMS)
	{
		showConsoleCursor(false);
		system("cls");
		bool end = false;
		int selectionPos = 0;

		
		while (!end)
		{
			drawMenu(message, elements, elementsc, selectionPos);
			std::this_thread::sleep_for(std::chrono::milliseconds(delayMS));
			switch (keyPressed())
			{
			case VK_UP:
				selectionPos = (selectionPos - 1) % elementsc;
					break;
			case VK_DOWN:
				selectionPos = (selectionPos + 1) % elementsc;
				break;
			case VK_RETURN:
				end = true;
				break;
			}
		}
		return selectionPos;
	}

	static std::string inputPrompt(std::string message,std::string label)
	{
		system("cls");
		showConsoleCursor(true);
		std::cout << "\r\n";

		printLogo();
		std::cout << message << std::endl;
		std::cout << label;
		std::string ret = "";
		std::cin >> ret;
		if (ret == "")
		{
			ret == "0";
		}
		return ret;
	}

	static bool yesOrNo(std::string message, size_t delayMS)
	{
		showConsoleCursor(false);
		std::string elements[] = { "Yes","No " };
		size_t elementsc = 2;
		return !menu(message, elements, elementsc, delayMS);
	}

};