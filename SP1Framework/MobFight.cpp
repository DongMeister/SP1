#include "game.h"
#include "MonsterEncounter.h"
#include "OpenMobs.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

extern Console console;
extern char g_cWallPosition[80][30];
extern Screen state;
extern Levels level;
extern COORD charLocation;
extern COORD starting;
extern int MeterBar;
extern int MinChance;
extern double TotalPoints;
extern std::string Monsters[];

void battleMONSTER(int monsterAppear) // get the monster from text file
{
	std::string line;

		std::ifstream myfile (Monsters[monsterAppear]); // chooses from the array table (in game.cpp) the monster
		
		if (myfile.is_open())
		{
			int y= 0;
			while ( getline (myfile,line) )
			{
				console.writeToBuffer(0,y,line,0x06); // writetobuffer the txt file
				y++;
			}

		}
		myfile.close();
	

}

void Died() // you died
{
	std::string line;
	std::ifstream myfile ("tomb.txt"); // opens the tomb.txt file

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
