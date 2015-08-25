#include "Controls.h"
#include "game.h"
#include "MusicFiles.h"

extern bool keyPressed[K_COUNT];
extern int MeterBar;
extern bool DialogueIsRunning;
extern int chat;
extern std::string Answer[5];

extern double MazePoints;
extern double TotalPoints;
extern double TotalBattlePoints;
extern double battlePoints;
extern Levels level;

void menuKeypress() // keys for the menu
{
	if (keyPressed[K_ONE])
	{
		MusicWillPlay(1);
		state = InMaze;
		openMap(0);
		DialogueIsRunning = true;
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
		if (level == lvl3)
		{
			MusicWillPlay(3);
		}

		else if (level == lvl61)
		{
			MusicWillPlay(4);
		}

		else if(level == lvl62)
		{
			MusicWillPlay(5);
		}

		else
		{
			MusicWillPlay(1);
		}

		MinusHealthMeter();
	}
}

void BattleKeypress()
{
	if (keyPressed[K_UP])
	{
		if (Answer[1] == Answer[4]) // Answer[4] is used as a checker for the correct answer
		{
			MusicWillPlay(9);
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
		if (Answer[2] == Answer[4])
		{
			MusicWillPlay(9);
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
		if (Answer[3] == Answer[4])
		{
			MusicWillPlay(9);
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
		MusicWillPlay(0);
		restart();
		state = Menu;
	}
}

void CorrectKeypress()
{
	if (keyPressed[K_SPACE])
	{
		if (level == lvl3)
		{
			MusicWillPlay(3);
		}

		else if (level == lvl61)
		{
			MusicWillPlay(4);
		}

		else if(level == lvl62)
		{
			MusicWillPlay(5);
		}

		else
		{
			MusicWillPlay(1);
		}
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
			if (level == lvl3)
			{
				MusicWillPlay(3);
			}

			else if (level == lvl61)
			{
				MusicWillPlay(4);
			}

			else if(level == lvl62)
			{
				MusicWillPlay(5);
			}

			else
			{
				MusicWillPlay(1);
			}

			state = InMaze;
		}
	}
}

void ClearStageKeypress()
{
	if (keyPressed[K_SPACE])
	{
		if (level == lvl3)
		{
			MusicWillPlay(3);
		}

		else if (level == lvl61)
		{
			MusicWillPlay(4);
		}

		else if(level == lvl62)
		{
			MusicWillPlay(5);
		}

		else
		{
			MusicWillPlay(1);
		}

		state = InMaze;
		MazePoints = 0;
		TotalBattlePoints = 0;
	}
}
