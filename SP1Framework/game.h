#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

extern StopWatch g_timer;
extern bool g_quitGame;

enum Levels
{
	lvl1,
	lvl2,
	lvl3,
	lvl41,
	lvl42,
	lvl51,
	lvl52,
	lvl61,
	lvl62,
	end
};


enum Screen
{
	Menu,
	InMaze,
	ChooseBattle,
	Battle,
	Scene,
	GameOver,
	Correct,
	Wrong,
	ClearStage,
	Animation
};

extern Screen state;

enum Keys
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
	K_ONE,
	K_TWO,
	K_THREE,
	K_FOUR,
	K_SPACE,
	K_ENTER,
    K_COUNT
};


void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory

void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void renderGame();
void renderDialogue();
void renderMazeTimer();

#endif // _GAME_H