#include "Framework\console.h"
#include "game.h"
#include "MainMenu.h"

#include <sstream>
#include <fstream>
#include <string>

extern Console console;
extern Screen state;
extern Levels level;
bool MenuPointer = true;
std::string MenuHolder[30];

void OpenMenu()
{
	std::string line;
	std::ifstream myfile ("MainMenuLayout/mainMenu.txt"); // displays main menu

	if (myfile.is_open())
	{
		int y= 0;
		while ( getline (myfile,line) )
		{
			MenuHolder[y] = line;
			y++;
		}
	}

	myfile.close();
}

void renderMenu()
{
	for (int i = 0;i < 30;++i)
	{
		console.writeToBuffer(0,i,MenuHolder[i],0X06);
	}
	renderMenuPointer();
}

void renderMenuPointer()
{
	if (MenuPointer == true)
	{
		console.writeToBuffer(42,16,"< ENTER",0x0F);
	}
	else
	{
		console.writeToBuffer(42,20,"< ENTER",0x0F);
	}
}