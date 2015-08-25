#include "Framework\console.h"
#include "game.h"
#include "MainMenu.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

extern Console console;
extern Screen state;
extern Levels level;

void menuLayout()
{
	std::string line;
	std::ifstream myfile ("MainMenuLayout/mainMenu.txt"); // displays main menu

	if (myfile.is_open())
	{
		int y= 0;
		while ( getline (myfile,line) )
		{
			console.writeToBuffer(0,y,line,0x06);
			y++;
		}
	}

	myfile.close();
}