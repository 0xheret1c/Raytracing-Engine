#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>

class Menu
{
private:
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
		std::cout << message << std::endl;
		for (size_t i = 0; i < elementsc; i++)
		{
			if (selectionPos == i)
				std::cout << offset << cursor << elements[i] << afterCursor << std::endl;
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
		system("clear");
		bool end = false;
		int selectionPos = 0;
		showConsoleCursor(false);
		
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

	static bool yesOrNo(std::string message, size_t delayMS)
	{
		std::string elements[] = { "Yes","No " };
		size_t elementsc = 2;
		return !menu(message, elements, elementsc, delayMS);
	}

};