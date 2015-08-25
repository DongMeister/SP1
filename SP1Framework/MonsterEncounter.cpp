#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>


#include "Framework\console.h"	
#include "MonsterEncounter.h"
#include "MonsterBattle.h"
#include "HealthBar.h"
#include "game.h"
#include "OpenMobs.h"
#include "screenAnimate.h"
#include "Titles.h"



std::string Question; 
std::string Answer[40];

int monsterAppear = 0;
int Encounter = 0;
const int MeetMonster = 100;

extern Console console;
extern double battlePoints;
extern double TotalPoints;
extern double MazePoints;
extern double TotalBattlePoints;
extern std::string Maps[];
extern Levels level;
extern int MeterBar;


questions Quest;

void ChanceEncounter()
{
	//Chance to Encounter Monsters

	monsterAppear = rand() % 8; //Chance of meeting different type of monsters
	Encounter = Encounter + rand() % 5 + 1; //Steps taken to encounter a monster
	
	if (Encounter < 50)
	{
		Beep(1500, 50); // short low frequency beep per step
	}

	if (Encounter >= 50 && Encounter < 80)
	{
		Beep(2000, 50); // short higher frequency beep
	}

	else if (Encounter >= 80 && Encounter <= 99)
	{
		Beep(2500, 50); // short even higher frequency beep
	}
	else if (Encounter >= MeetMonster)
	{
		chooseQn(); // selects questions from text file
		RandomizeAnswers(); // shuffles up the answers for the question
		splashAnimate(level);
		state = Animation; // change state to choose battle
		Encounter = 0; // resets encounter chance to 0
	}
}



void displayBattleMenu()
{
	battleMONSTER(monsterAppear);
	console.writeToBuffer(console.getConsoleSize().X/2 - 8, console.getConsoleSize().Y/2 + 3, "An enemy appeared!" , 0x06);
	console.writeToBuffer(console.getConsoleSize().X/2 - 8, console.getConsoleSize().Y/2 + 4, "Will you:" , 0x06);
	console.writeToBuffer(console.getConsoleSize().X/2 - 8, console.getConsoleSize().Y/2 + 5, "Fight? (1)" , 0x06);
	console.writeToBuffer(console.getConsoleSize().X/2 - 8, console.getConsoleSize().Y/2 + 6, "Run? (2)" , 0x06);
}


void displayBattle() // displays the battle options
{
	battleMONSTER(monsterAppear);
	if (battlePoints > 0)
	{
		std::ostringstream ss;
		ss << std::fixed << std::setprecision(0);
		ss << battlePoints << "secs remaining";
		console.writeToBuffer(0,1,ss.str(),0x09);
		console.writeToBuffer(console.getConsoleSize().X/2 - Question.length()/2, console.getConsoleSize().Y/2 + 3, Question, 0x06); // displays the question

		for (int A = 1;A < 4;++A)
		{
			int slot;
			std::string added;
			if (A == 1)
			{
				added = "(Up arrow)";
				slot = Quest.up; // Quest.up is the integer holding the first answer
			}
			else if (A == 2)
			{
				added = "(Left arrow)";
				slot = Quest.left; // Holding the 2nd answer
			}
			else if (A == 3)
			{
				added = "(Right arrow)";
				slot = Quest.right; // lastly the third answer
			}

			console.writeToBuffer(console.getConsoleSize().X/2 - 33,console.getConsoleSize().Y/2+4+A, Answer[slot] + added, 0x06); // showing the answer in order
		}
	}
	else
	{
		state = Wrong;
		battlePoints = 15; // if battle points timer is 0 or less, you got the answer wrong and timer is reset back to 15s
	}
}


void GameLost() // WE LOST
{
	Died();
	console.writeToBuffer(console.getConsoleSize().X/2 - 5, console.getConsoleSize().Y/2 + 6, "Game Over" , 0x0C);
	console.writeToBuffer(console.getConsoleSize().X/2 - 13, console.getConsoleSize().Y/2 + 8, "(Press Space to restart)" , 0x0C);
	std::ostringstream ss;
    ss << std::fixed << std::setprecision(0);
    ss << "Your Score: " << TotalPoints;
    console.writeToBuffer(console.getConsoleSize().X/2 - 7,console.getConsoleSize().Y/2 + 7, ss.str(),0x0C);
}

void YouDidIt() // Question correctly answered display
{
	console.writeToBuffer(console.getConsoleSize().X/2 - 4, console.getConsoleSize().Y/2, "Correct!" , 0x0A);
	console.writeToBuffer(console.getConsoleSize().X/2 - 13, console.getConsoleSize().Y/2 + 1, "(Press Space to continue)" , 0x0A);
}

void YouFailed() // Question answered is wrong
{
	PlaySound(NULL, NULL, 0);
	if (MeterBar > 0)
	{
		console.writeToBuffer(console.getConsoleSize().X/2 - 12, console.getConsoleSize().Y/2, "WRONG! You lost 1 health" , 0x0C);
		console.writeToBuffer(console.getConsoleSize().X/2 - 12, console.getConsoleSize().Y/2 + 1, "(Press Space to continue)" , 0x0C);
	}
	else
	{
		state = GameOver;
	}
}


void chooseQn() // CHOOSE the question from the file
{
	std::ifstream myfile ("GE.txt");
	int n = (rand() % 40) * 5;
	int o = 0;
	int A = 1;
	bool checkQ = false; // check whether question has been retrieved
	std::string holder;
	if (myfile.is_open())
	{
		while ( getline (myfile, holder) )
		{
			if (checkQ == true && A < 5) // getting the next 4 lines as the answers
			{
				Answer[A] = holder;
				++A;
			}

			if (o == n && checkQ == false) // if question has been retrieved and o == n, question will be retrieved
			{
				Question = holder;
				checkQ = true;
			}
			else
			{
				++o;
			}

			

		}
	}
	myfile.close();
}

void StageClear() // displays the points achieved in the stage
{
	PlaySound(NULL, NULL, 0);
	console.writeToBuffer(console.getConsoleSize().X/2 - 8,console.getConsoleSize().Y/2 - 5, "Stage Clear!",0x0A);
	std::ostringstream ss;
    ss << std::fixed << std::setprecision(0);
    ss << "Points for clearing stage: " << MazePoints;
    console.writeToBuffer(console.getConsoleSize().X/2 - ss.str().length()/2 - 3,console.getConsoleSize().Y/2-4, ss.str(),0x0A);
	ss.str("");
	ss << "Points for battles won: " << TotalBattlePoints;
	console.writeToBuffer(console.getConsoleSize().X/2 - ss.str().length()/2 - 3,console.getConsoleSize().Y/2-3, ss.str(),0x0A);
	ss.str("");
	ss << "Total points: " << TotalPoints;
	console.writeToBuffer(console.getConsoleSize().X/2 - ss.str().length()/2 - 3,console.getConsoleSize().Y/2-2, ss.str(),0x0A);
	ss.str("");
	ss << "Title: " + TitleForGame(TotalPoints);
	console.writeToBuffer(console.getConsoleSize().X/2 - ss.str().length()/2 - 3,console.getConsoleSize().Y/2-1, ss.str(),0x0A);

	console.writeToBuffer(console.getConsoleSize().X/2 - 14,console.getConsoleSize().Y/2 + 1, "Press Space to Continue",0x0C);
}

void RandomizeAnswers()
{
	int ans1,ans2;
	Quest.up = rand() %3 + 1; // randomly choose the first answer
	ans1 = Quest.up;
	Quest.left = rand()%3 + 1; // randomly chooses the second answer
	ans2 = Quest.left;
	while (Quest.left == ans1) // checks whether the second answer is the same as the first answer, if so, random again until you get a different value
	{
		Quest.left = rand()%3 + 1;
		ans2 = Quest.left;
	}
	for (int i = 1;i < 4;i++) // Leaving one answer behind, just choose the last possible answer
	{
		if (i != ans1 && i != ans2)
		{
			Quest.right = i;
		}
	}
}