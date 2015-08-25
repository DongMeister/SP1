#include "HealthBar.h"
#include "Framework\console.h"	

int MeterBar = 5;
extern Console console;


void MinusHealthMeter() // determine whether health is reduced when running
{
	int ifLose = rand() % 10;
	
	if (ifLose <= 4)
	{
		--MeterBar;
	}
	if (MeterBar < 1)
	{
		state = GameOver;
	}
	else
	{
		state = InMaze;
	}
}

void PlusHealthMeter() // chance to increase health after completing a question
{
	int ifWin = rand() % 10;

	if (ifWin <= 1 && MeterBar < 5)
	{
		++MeterBar;
	}
}

void displayHealth() // display current health
{
	for (int i = 0;i < MeterBar;++i)
	{
		console.writeToBuffer(console.getConsoleSize().X - 5 + i, 0, (char)3 , 0x0C);
	}
}
