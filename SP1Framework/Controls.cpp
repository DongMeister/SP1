#include "Controls.h"

extern bool   keyPressed[K_COUNT];
extern questions Quest;
extern int MeterBar;
extern bool dialouge;
extern int chat;
extern std::string Answer[5];

extern double MazePoints;
extern double TotalPoints;
extern double TotalBattlePoints;
extern double battlePoints;

void menuKeypress() // keys for the menu
{
	if (keyPressed[K_ONE])
	{
		state = InMaze;
		openMap(0);
		dialouge = true;
		chat = 0;
	}
}

void ChooseBattleKeypress()
{
	if (keyPressed[K_ONE])
	{
		state = Battle;
	}
	if (keyPressed[K_TWO])
	{
		MinusHealthMeter();
	}
}

void BattleKeypress()
{
	if (keyPressed[K_UP])
	{
		if (Answer[Quest.up] == Answer[4]) // Answer[4] is used as a checker for the correct answer
		{
			state = Correct;
			PlusHealthMeter();
		}
		else
		{
			state = Wrong;
			MeterBar--;
		}
	}
	if (keyPressed[K_LEFT])
	{
		if (Answer[Quest.left] == Answer[4])
		{
			state = Correct;
			PlusHealthMeter();
		}
		else
		{
			state = Wrong;
			MeterBar--;
		}
	}
	if (keyPressed[K_RIGHT])
	{
		if (Answer[Quest.right] == Answer[4])
		{
			state = Correct;
			PlusHealthMeter();
		}
		else
		{
			state = Wrong;
			MeterBar--;
		}
	}
}

void GameOverKeypress()
{
	if (keyPressed[K_SPACE])
	{
		restart();
		state = Menu;
	}
}

void CorrectKeypress()
{
	if (keyPressed[K_SPACE])
	{
		state = InMaze;
		battlePoints *= 10;
		TotalBattlePoints += battlePoints;
		TotalPoints = TotalPoints + battlePoints;
		battlePoints = 15;
	}
}

void WrongKeypress()
{
	if (keyPressed[K_SPACE])
	{
		if (MeterBar == 0)
		{
			TotalPoints = TotalPoints + TotalBattlePoints;
			state = GameOver;
		}

		else
		{
			state = InMaze;
		}
	}
}

void ClearStageKeypress()
{
	if (keyPressed[K_SPACE])
	{
		state = InMaze;
		MazePoints = 0;
		TotalBattlePoints = 0;
	}
}
