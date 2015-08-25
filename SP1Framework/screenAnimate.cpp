#include "screenAnimate.h"
#include "game.h"
#include "Framework\timer.h"
#include "Framework\console.h"
#include "MonsterEncounter.h"

#include <sstream>
#include <fstream>
#include <string>

extern std::string Maps[];
extern Console console;
double AnimateTimer = 0;
char g_cAnimatePosition[80][30];
extern char g_cWallPosition[80][30];
int a = 0;
int b = 0;

void splashAnimate(int i)
{		
	for (unsigned int y = 0;y < 30;++y)
	{
		for (unsigned int x = 0;x < 80;++x)
		{
			g_cAnimatePosition[x][y] = g_cWallPosition[x][y];
		}
	}

	AnimateTimer = 0;
}


void AnimateOne()
{
	for (unsigned int y = 0;y < 30;++y)
	{
		for (unsigned int x = 0;x < 80;++x)
		{
			console.writeToBuffer( x, y, g_cAnimatePosition[x][y] , 0x06);
		}
	}

	if (AnimateTimer > 0.000125)
	{
		AnimateTimer = 0;
		if (b < 30)
		{
			for (int i = 0;i < 80;i++)
			{
				g_cAnimatePosition[a + i][b] = ' ';
			}
			a += 80;
			if (a == 80)
			{
				a = 0;
				b++;
			}
			if (b == 29)
			{
				state = ChooseBattle;
				b = 0;
			}
		}
	}
}
