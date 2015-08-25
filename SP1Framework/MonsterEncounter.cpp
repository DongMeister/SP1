#include <iostream>
#include <iomanip>
#include <string>
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
#include "MusicFiles.h"



std::string Question; 
std::string Answer[40];

int monsterAppear = 0;
int Encounter = 0;
const int MeetMonster = 200;

extern Console console;
extern double battlePoints;
extern double TotalPoints;
extern double MazePoints;
extern double TotalBattlePoints;
extern std::string Maps[];
extern Levels level;
extern int MeterBar;


void ChanceEncounter()
{
	//Chance to Encounter Monsters

	monsterAppear = rand() % 8; //Chance of meeting different type of monsters
	Encounter = Encounter + rand() % 5 + 1; //Steps taken to encounter a monster
	
	if (Encounter >= MeetMonster)
	{
		MusicWillPlay(2);
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
	int x = console.getConsoleSize().X/2 - 8;
	console.writeToBuffer(x, console.getConsoleSize().Y/2 + 3, "An enemy appeared!" , 0x06);
	console.writeToBuffer(x, console.getConsoleSize().Y/2 + 4, "Will you:" , 0x06);
	console.writeToBuffer(x, console.getConsoleSize().Y/2 + 5, "Fight? (1)" , 0x06);
	console.writeToBuffer(x, console.getConsoleSize().Y/2 + 6, "Run? (2)" , 0x06);
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
			std::string added;
			if (A == 1)
			{
				added = "(Up arrow)";
			}
			else if (A == 2)
			{
				added = "(Left arrow)";
			}
			else if (A == 3)
			{
				added = "(Right arrow)";
			}

			console.writeToBuffer(console.getConsoleSize().X/2 - 33,console.getConsoleSize().Y/2+4+A, Answer[A] + added, 0x06); // showing the answer in order
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
	if (MeterBar > 0)
	{
		console.writeToBuffer(console.getConsoleSize().X/2 - 12, console.getConsoleSize().Y/2, "WRONG! You lost 1 health" , 0x0C);
		console.writeToBuffer(console.getConsoleSize().X/2 - 12, console.getConsoleSize().Y/2 + 1, "(Press Space to continue)" , 0x0C);
	}
	else
	{
		MusicWillPlay(10);
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
	
	for (int i = 0;i < 3;++i) // randomly shuffles the questions 3 times
	{
		int a = rand() %3 + 1;
		std::string Holder = Answer[1];
		Answer[1] = Answer[a];
		Answer[a] = Holder;
	}
}