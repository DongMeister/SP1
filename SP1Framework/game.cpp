// This is the main file for the game logic and function
//
//
#include "game.h"
#include "MainMenu.h"
#include "Framework\console.h"
#include "MonsterEncounter.h"
#include "MonsterBattle.h"
#include "HealthBar.h"
#include "OpenMap.h"
#include "OpenMobs.h"
#include "screenAnimate.h"
#include "Dialogue.h"
#include "Titles.h"
#include "Controls.h"
#include "MusicFiles.h"
#include "IndicationOfNearbyMonsterThruColour.h"

#include <sstream>
#include <fstream>
#include <string>


// Console object
Console console(80, 30, "SP1 Framework");

int chat = 0;

double elapsedTime;
double deltaTime;
double battlePoints = 15; // Countdown timer when answering question
double MazePoints = 0; // Timer in-maze
double TotalPoints = 0; // Displayed after completing a level
double TotalBattlePoints = 0; // Total Points achieved throughout
double Dialogtime = 0; // countdown for dialog time
bool   keyPressed[K_COUNT];
char   g_cWallPosition[80][30];
bool   DialogueIsRunning = false;
Levels level = lvl1;
Screen state;
std::string Maps[] = {"Map/Map1.txt","Map/Map2.txt","Map/Map3.txt", "Map/Map4.1_Nostalgia.txt", "Map/Map4.2_Frustration.txt", "Map/Map5.1_Reminiscence.txt", "Map/Map5.2_Static.txt", "Map/Map6.1_Euphoria.txt", "Map/Map6.2_Forgotten.txt"};
std::string Monsters[] = {"Mobs/battleBAT.txt","Mobs/battleGOAT.txt","Mobs/battleGOBLIN.txt","Mobs/battleJESTER.txt","Mobs/battleSCORPION.txt","Mobs/battleSHADOW.txt","Mobs/battleSPIDER.txt","Mobs/battleSPIRIT.txt"};

extern std::string Answer[5];
extern int MeterBar;
extern int Encounter;
extern double AnimateTimer;
extern unsigned int randomAnimate;


// Game specific variables here
COORD charLocation;
COORD starting;
// Initialize variables, allocate memory, load data from file, etc. 
// This is called once before entering into your main loop
void init()
{
    // Set precision for floating point output
	OpenMenu();
	state = Menu;
	srand(time(0));
    elapsedTime = 0.0;
	charLocation.X = 0;
	charLocation.Y = 15;
	starting = charLocation;
    // sets the width, height and the font name to use in the console
    console.setConsoleFont(0,16 , L"Asa");
	MusicWillPlay(0);
	LoadDialogue();
	LoadQn();

}

// Do your clean up of memory here
// This is called once just before the game exits
void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    console.clearBuffer();
}
/*
	This function checks if any key had been pressed since the last time we checked
	If a key is pressed, the value for that particular key will be true
	
	Add more keys to the enum in game.h if you need to detect more keys
	To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
	For Alphanumeric keys, the values are their ascii values (uppercase).
*/
void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
    keyPressed[K_ONE] = isKeyPressed(0x31);
	keyPressed[K_TWO] = isKeyPressed(0x32);
    keyPressed[K_THREE] = isKeyPressed(0x33);
	keyPressed[K_FOUR] = isKeyPressed(0x34);
	keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	keyPressed[K_ENTER] = isKeyPressed(0x0D);
}

/*
	This is the update function
	double dt - This is the amount of time in seconds since the previous call was made

	Game logic should be done here.
	Such as collision checks, determining the position of your game characters, status updates, etc
	If there are any calls to write to the console here, then you are doing it wrong.

    If your game has multiple states, you should determine the current state, and call the relevant function here.
*/
void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

	switch(state) //What state the game is in
	{
		case 0:
			ChooseBattleMenu();
			break;
		case 1:
			moveCharacter();
			MazePoints += dt; // update timer in-maze
			if (DialogueIsRunning == true)
			{
				Dialogtime += dt;
			}
			break;
		case 2:
			ChooseBattleKeypress();
			break;
		case 3:
			BattleKeypress();
			battlePoints -= dt; // update timer in-battle
			break;
		case 4:
			break;
		case 5:
			GameOverKeypress();
			break;
		case 6:
			CorrectKeypress();
			break;
		case 7:
			WrongKeypress();
			break;
		case 8:
			ClearStageKeypress();
			break;
		case 9:
			AnimateTimer += dt;
			break;
	}

    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    // moves the character, collision detection, physics, etc
    // sound can be played here too.
}

/*
    This is the render loop
    At this point, you should know exactly what to draw onto the screen.
    Just draw it!
    To get an idea of the values for colours, look at console.h and the URL listed there
*/
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 

	switch(state) // renders the game for each different state
	{
		case 0:
			renderMenu();
			break;
		case 1:
			renderGame();
			break;
		case 2:
			displayBattleMenu();
			break;
		case 3:
			displayBattle();
			break;
		case 4:
			break;
		case 5:
			GameLost();
			break;
		case 6:
			DisplayCorrect();
			break;
		case 7:
			DisplayFail();
			break;
		case 8:
			StageClear();
			break;
		case 9:
			AnimateOne();
			break;

	}
    //renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}


void moveCharacter()
{
    // Updating the location of the character based on the key press
	if (state == InMaze) // Controls in-maze
	{
		if (keyPressed[K_UP] && charLocation.Y > 0)
		{
			if (g_cWallPosition[charLocation.X][charLocation.Y - 1] != char(177))
			{
				charLocation.Y--;
				ChanceEncounter();
				checkAdvance();
			}
		}

		if (keyPressed[K_LEFT] && charLocation.X > 0)
		{
			if (g_cWallPosition[charLocation.X-1][charLocation.Y] != char(177))
			{
				charLocation.X--; 
				ChanceEncounter();
				checkAdvance();
			}
		}
		if (keyPressed[K_DOWN] && charLocation.Y < console.getConsoleSize().Y - 1)
		{
			if (g_cWallPosition[charLocation.X][charLocation.Y+1] != char(177))
			{
				charLocation.Y++; 
				ChanceEncounter();
				checkAdvance();
			}
		}
			
		if (keyPressed[K_RIGHT] && charLocation.X < console.getConsoleSize().X - 1)
		{
			if (g_cWallPosition[charLocation.X+1][charLocation.Y] != char(177))
			{
				charLocation.X++;
				ChanceEncounter();
				checkAdvance();
			}
		}
		if (keyPressed[K_SPACE] && DialogueIsRunning == true)
		{
				DialogueIsRunning = false;
		}

	}
	

}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    console.clearBuffer(0x0F);
}

void renderMap()
{
	for (int y = 0;y < 30;++y)
	{
		for (int x = 0;x < 80;++x)
		{
			console.writeToBuffer( x, y, g_cWallPosition[x][y] , 0x06);
		}
	}	
}

void renderCharacter()
{
    // Draw the location of the character
	DisplayifMonsterIsNearOrFarAwayFromPlayer();

	displayHealth(); // displaying health bar
	
}

void renderGame()
{
	renderMap();
	renderCharacter();
	renderDialogue();
	renderMazeTimer();
}

void renderDialogue()
{
	if (DialogueIsRunning == true)
	{
		WriteDialogue(choosedialog(chat));
		if (Dialogtime > 3)
		{
			Dialogtime = 0;
			DialogueIsRunning = false;
		}
	}
}

void renderMazeTimer()
{
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(0);
	ss << MazePoints << "secs has passed"; // maze timer
	console.writeToBuffer(0,0,ss.str(),0x0A);
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / deltaTime << "fps";
    c.X = console.getConsoleSize().X - 9;
    c.Y = 0;
    console.writeToBuffer(c, ss.str());



    // displays the elapsed time
    ss.str("");
    ss << elapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    console.writeToBuffer(c, ss.str(), 0x59);
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    console.flushBufferToConsole();
}
