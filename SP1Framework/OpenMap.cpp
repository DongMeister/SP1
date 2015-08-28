#include "game.h"
#include "OpenMap.h"
#include "Framework\console.h"
#include "MusicFiles.h"
#include "HealthBar.h"
#include "Traps.h"

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
extern double TotalPoints;
extern double MazePoints;
extern double TotalBattlePoints;
extern std::string Maps[];
extern bool DialogueIsRunning;
extern int chat;

extern int currentlevel;
extern COORD currentposition;


bool Open[4] = {false,false,false,false};


void openMap(int i) // opens the map and overrides the 2d array WallPosition
{
	std::string line;
	std::ifstream myfile (Maps[i]);

	if (myfile.is_open())
	{
		int y= 0;
		 while ( getline (myfile,line) )
		 {
			 for (unsigned int i = 0;i < line.length();++i)
			 {
				 if (line[i] == '#') // changes all # in the text file to char(177) which is a block
				 {
					 line[i] = char(177);
				 }
			 }
			for (int x = 0;x<80;++x)
			{
				g_cWallPosition[x][y] = line[x]; //inserting the characters from the txt file into a 2d array to detect collision
			}
			++y;
		}
	}
	myfile.close();
}
void openDoor() // checks for a switch (*) and opens a path corresponding to level
{
	if (g_cWallPosition[charLocation.X][charLocation.Y] == '*')
	{
		Beep(1500,50);
		switch(level)
		{
			case 0:
				break;
			case 1:
				g_cWallPosition[39][15] = ' ';
				chat = 1;
				DialogueIsRunning = true;
				break;
			case 2:
				g_cWallPosition[78][3] = ' ';
				chat = 1;
				DialogueIsRunning = true;
				break;
			case 3:
				if (charLocation.X == 20 && charLocation.Y == 7 && Open[0] == false)
				{
					Open[0] = true;
					chat++;
					DialogueIsRunning = true;
				}

				else if (charLocation.X == 43 && charLocation.Y == 7 && Open[1] == false)
				{
					Open[1] = true;
					chat++;
					DialogueIsRunning = true;
				}

				else if (charLocation.X == 48 && charLocation.Y == 16 && Open[2] == false)
				{
					Open[2] = true;
					chat++;
					DialogueIsRunning = true;
				}

				else if (charLocation.X == 19 && charLocation.Y == 14 && Open[3] == false)
				{
					Open[3] = true;
					chat++;
					DialogueIsRunning = true;
				}

				if (checkArray() == true)
				{
					g_cWallPosition[79][14] = ' ';
				}
				break;
			case 4:
				g_cWallPosition[28][22] = char(177);
				g_cWallPosition[27][29] = ' '; 
				chat = 1;
				DialogueIsRunning = true;
				break;
			case 5:
				g_cWallPosition[0][16] = ' ';
				chat = 1;
				DialogueIsRunning = true;
				break;
			case 6:
				g_cWallPosition[39][0] = ' ';
				chat = 1;
				DialogueIsRunning = true;
				break;
			case 7:
				g_cWallPosition[79][1] = ' ';
				chat = 1;
				DialogueIsRunning = true;
				break;
			case 8:
				g_cWallPosition[79][7] = ' ';
				chat = 1;
				DialogueIsRunning = true;
				break;
		}
	}
}
bool checkArray()
{
	for (int i = 0;i < 4;++i)
	{
		if (Open[i] == false)
		{
			return false;
		}
	}
	return true;
}

void checkAdvance() // check whether to advance to the next level
{
	if (level == 0)
	{
		if (charLocation.X == 79 && charLocation.Y == 8)
			{
				int a = int(level) + 1;
				level = static_cast<Levels>(a);
				openMap(int(level)); // opens the next level's map
				state = ClearStage;
				MazePoints = 3000 - 10*MazePoints;
				if (MazePoints > 0)
				{
					TotalPoints = TotalPoints + MazePoints; // adds to the total points of the game
				}
				charLocation.X = 0;
				charLocation.Y = 15; // moving character to the new starting position
			}
	}
	else if (level == 1)
	{
		if (charLocation.X == 79 && charLocation.Y == 15)
			{
				int a = int(level) + 1;
				level = static_cast<Levels>(a);
				openMap(int(level));
				state = ClearStage;
				MazePoints = 3000 - 10*MazePoints;
				if (MazePoints > 0)
				{
					TotalPoints = TotalPoints + MazePoints;
				}
				charLocation.X = 1;
				charLocation.Y = 29;
			}
	}
	else if (level == 2)
	{
		if (charLocation.X == 78 && charLocation.Y == 0)
			{
				int a = int(level) + 1;
				level = static_cast<Levels>(a);
				openMap(int(level));
				state = ClearStage;
				MazePoints = 3000 - 10*MazePoints;
				if (MazePoints > 0)
				{
					TotalPoints = TotalPoints + MazePoints;
				}
				charLocation.X = 1;
				charLocation.Y = 29;
			}
		else if (charLocation.X == 73 && charLocation.Y == 0)
			{
				int a = int(level) + 2;	
				level = static_cast<Levels>(a);
				openMap(int(level));
				state = ClearStage;
				MazePoints = 3000 - 10*MazePoints;
				if (MazePoints > 0)
				{
					TotalPoints = TotalPoints + MazePoints;
				}

				charLocation.X = 39;
				charLocation.Y = 13;
			}
	}
	else if (level == 3)
	{
		if (charLocation.X == 79 && charLocation.Y == 14)
		{
			int a = int(level) + 2;
			level = static_cast<Levels>(a);
			openMap(int(level));
			state = ClearStage;
			MazePoints = 3000 - 10*MazePoints;
			if (MazePoints > 0)
			{
				TotalPoints = TotalPoints + MazePoints;
			}
			charLocation.X = 0;
			charLocation.Y = 8;
		}
	}
	else if (level == 4)
	{
		if (charLocation.X == 27 && charLocation.Y == 29)
		{
			int a = int(level) + 2;
			level = static_cast<Levels>(a);
			openMap(int(level));
			state = ClearStage;
			MazePoints = 3000 - 10*MazePoints;
			if (MazePoints > 0)
			{
				TotalPoints = TotalPoints + MazePoints;
			}
			charLocation.X = 0;
			charLocation.Y = 9;
		}
	}
	else if (level == 5)
	{
		if (charLocation.X == 0 && charLocation.Y == 16)
		{
			int a = int(level) + 2;
			level = static_cast<Levels>(a);
			openMap(int(level));
			state = ClearStage;
			MazePoints = 3000 - 10*MazePoints;
			if (MazePoints > 0)
			{
				TotalPoints = TotalPoints + MazePoints;
			}
			charLocation.X = 1;
			charLocation.Y = 29;
		}
	}
	else if (level == 6)
	{
		if (charLocation.X == 39 && charLocation.Y == 0)
		{
			int a = int(level) + 2;
			level = static_cast<Levels>(a);
			openMap(int(level));
			state = ClearStage;
			MazePoints = 3000 - 10*MazePoints;
			if (MazePoints > 0)
			{
				TotalPoints = TotalPoints + MazePoints;
			}
			charLocation.X = 0;
			charLocation.Y = 26;
		}
	}
	else if (level == 7)
	{
		if (charLocation.X == 79 && charLocation.Y == 1)
		{
			state = ClearStage;
			MazePoints = 3000 - 10*MazePoints;
			if (MazePoints > 0)
			{
				TotalPoints = TotalPoints + MazePoints;
			}
			charLocation.X = 1;
			charLocation.Y = 29;
		}
	}
	else if (level == 8)
	{
		if (charLocation.X == 79 && charLocation.Y == 7)
		{
			state = ClearStage;
			MazePoints = 3000 - 10*MazePoints;
			if (MazePoints > 0)
			{
				TotalPoints = TotalPoints + MazePoints;
			}
			charLocation.X = 0;
			charLocation.Y = 26;
		}
	}
	else if (level == 9)
	{
		if (charLocation.X == 79 && charLocation.Y == 15)
		{
				level = static_cast<Levels>(currentlevel);
				openMap(currentlevel);
				charLocation = currentposition;

		}
	}

	openDoor();
	openTraps();
	closeTraps();
	openPath();
	checkIfThereAreTraps();
}

void restart() // restart all variables for a fresh start
{
	level = lvl1;
	chat = 0;
	charLocation = starting;
	MeterBar = 5;
	MazePoints = 0;
	TotalPoints = 0;
	TotalBattlePoints = 0;
	for (int i = 0;i < 4;++i)
	{
		Open[i] = false;
	}
} 