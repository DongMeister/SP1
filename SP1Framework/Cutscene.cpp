#include "Cutscene.h"


char CutsceneWalls[80][30];
std::string Cutscenedialog[10];

extern bool keyPressed[K_COUNT];
extern Console console;
extern double CutsceneTimer;
extern double CutsceneCharTimer;
extern double CutsceneDialogTimer;
extern std::string Cutscenes[];
extern Levels level;
extern bool DialogueIsRunning;
extern int chat;


std::string CutDialog[15];

double charWait = 22; //duration of pause

double Ctime = 38;
int x = 0;
int CutscenePoint = 0;

void renderCutscene()
{
	if (CutsceneTimer < Ctime + charWait) //Total time of cutscene
	{
		
		for (int y = 0;y < 30;++y)
			{
				for (int x = 0;x < 80;++x)
				{
					console.writeToBuffer( x, y, CutsceneWalls[x][y] , 0x08);
				}
			}
		if (CutsceneDialogTimer > (Ctime + charWait)/24)
		{
			CutsceneDialogTimer = 0;
			CutscenePoint++;
			renderCutscenedialog(CutDialog[CutscenePoint]);
		}
		else
		{
			renderCutscenedialog(CutDialog[CutscenePoint]);
		}
		renderCutsceneCharacter();
	}
	else
	{
		MusicWillPlay(1);
		CutsceneTimer = 0;
		CutsceneCharTimer = 0;
		state = InMaze;
		openMap(level);
		DialogueIsRunning = true;
		x = 0;
	}
}

void loadCutscene()
{
	std::string line;
	std::ifstream myfile ("Map/Map_Cutscene1.txt");

	if (myfile.is_open())
	{
		int y= 0;
		while ( getline (myfile,line) )
		 {
			for (unsigned int i = 0;i < line.length();++i)
			{
				if (line[i] == '#') // changes all # in the text file to char(177) which is a block
				{
					line[i] = 177;
				}
			}
			for (int x = 0;x<80;++x)
			{
				CutsceneWalls[x][y] = line[x]; //inserting the characters from the txt file into a 2d array to detect collision
			}
			++y;
		}
	}
	myfile.close();
}

void renderCutsceneCharacter() //renders character
{
	console.writeToBuffer( x, 8, (char)2, 0x0C);
	if (CutsceneCharTimer >= Ctime/99) //speed of character movement
	{
		if (x != 40) 
		{
			++x;
			CutsceneCharTimer = 0;	
		}
		else
		{
			if (CutsceneCharTimer >= charWait) //Pausing character for duration
			{
				++x;
				CutsceneCharTimer = 0;
			}
		}			
	}
}

void CutsceneDialog() //reading the lines in dialog
{
	std::string line;
	std::ifstream myfile (Cutscenes[int(level)]);

	if (myfile.is_open())
	{
		int y= 0;
		 while (getline (myfile,line))
		 {
			if (y < 24)
			{
				CutDialog[y] = line;
				++y;
			}
		 }
	}
	myfile.close();
}

void renderCutscenedialog(std::string Stuff)
{
	for (int i = 0;i < 10;++i)
	{
		console.writeToBuffer(0,21+i,Cutscenedialog[i],0x08);
	}
	console.writeToBuffer(40-Stuff.length()/2,24,Stuff,0x08);

}

void LoadCutsceneDialogue()
{
	std::string line;
	std::ifstream myfile ("Map/cutsceneDialogbox.txt");
	
	if (myfile.is_open())
	{
		int y= 0;
		 while ( getline (myfile,line) )
		 {
			if (y < 10)
			{
				Cutscenedialog[y] = line;
				++y;
			}
		 }
	}
	myfile.close();
}
