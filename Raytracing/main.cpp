
#include <stdio.h>
#include <iostream>
#include "./Core.h"


int main(int argc, char* argv[])
{

	GFXOutput out = GFXOutput(640, 480);
	while (true)
	{
		out.setPixels();
		out.printScreen();
	}

	system("pause");
	return 0;
}