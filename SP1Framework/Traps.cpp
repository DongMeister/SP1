#include "Traps.h"
#include "game.h"

extern int MeterBar;
extern Console console;
extern char g_cWallPosition[80][30];
extern Screen state;
extern Levels level;
extern COORD charLocation;
int currentlevel;
COORD currentposition;

void checkIfThereAreTraps()
{
	if (g_cWallPosition[charLocation.X][charLocation.Y] == '^')
	{
		if (MeterBar > 1)
		{
			--MeterBar;
		}
		
		else
		{
			state = GameOver;
		}
	}

	if (g_cWallPosition[charLocation.X][charLocation.Y] == 'O')
	{
		currentlevel = level;
		currentposition = charLocation;
		level = TrapLevel;
		openMap(9);
		charLocation.X = 5;
		charLocation.Y = 15;
	}
}
void openTraps()
{
		switch(level)
		{
			case 0:
				break;
			case 1:
				break;
			case 2:
				if (charLocation.X == 40 && charLocation.Y == 18)
				{
					g_cWallPosition[39][15] = char(79);
				}
				break;
			case 3:
				if (charLocation.X == 63 && charLocation.Y == 28)
				{
					g_cWallPosition[68][27] = char(79);
				}
				if (charLocation.X == 50 && charLocation.Y == 14)
				{
					g_cWallPosition[50][16] = char(79);
				}
				
				break;
			case 4:
				if (g_cWallPosition[charLocation.X][charLocation.Y] == '*')
				{
					g_cWallPosition[28][28] = char(79);
				}
				if (charLocation.X == 27 && charLocation.Y == 26)
				{
					g_cWallPosition[25][25] = char(177);
					g_cWallPosition[21][25] = char(177);
				}
				break;
			case 5:
				if (charLocation.X == 37 && charLocation.Y == 11 || charLocation.X == 38 && charLocation.Y == 11 || charLocation.X == 39 && charLocation.Y == 11 )
				{
					g_cWallPosition[39][13] = char(177);
					g_cWallPosition[40][13] = char(177);
				}
				if (charLocation.X == 22 && charLocation.Y == 14)
				{
					g_cWallPosition[20][16] = char(177);
					if (charLocation.X == 73 && charLocation.Y == 5)
					{
						g_cWallPosition[20][16] = ' ';
					}
				}
				if (charLocation.X == 48 && charLocation.Y == 18)
				{
					g_cWallPosition[48][19] = char(177);
					g_cWallPosition[48][20] = char(177);
					for (int x = 49;x <= 57;++x)
					{
						g_cWallPosition[x][18] = ' ';
					}
					g_cWallPosition[57][19] = ' ';
				}
				if (charLocation.X == 57 && charLocation.Y == 21)
				{
					g_cWallPosition[57][22] = char(177);
					g_cWallPosition[57][23] = char(177);
					for (int x = 58;x <= 64;++x)
					{
						g_cWallPosition[x][21] = ' ';
					}
				}
				if (charLocation.X == 14 && charLocation.Y == 19)
				{
					g_cWallPosition[13][19] = ' ';
					g_cWallPosition[12][19] = ' '; 
					g_cWallPosition[11][19] = ' ';
					g_cWallPosition[10][19] = ' ';
				}
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				if (charLocation.X == 38 && charLocation.Y == 6)
				{
					g_cWallPosition[38][5] = char(177);
					for ( int X = 38; X <= 57; X++)
					{
						g_cWallPosition[X][4] = char(177);
					}
					for ( int X = 41; X <= 76; X++ )
					{
						g_cWallPosition[X][3] = char(177);
					}
					for ( int X = 41; X <= 76; X++ )
					{
						g_cWallPosition[X][2] = char(177);
					}
					for ( int X = 66; X <= 76; X++)
					{
						g_cWallPosition[X][4] = ' ';
					}

				}
				break;
		}
	
}
void closeTraps()
{
		switch(level)
		{
			case 0:
				break;
			case 1:
				if (g_cWallPosition[charLocation.X][charLocation.Y] == '*')
				{
					g_cWallPosition[15][13] = ' ';
					g_cWallPosition[15][17] = ' ';
				}
				break;
			case 2:
				break;
			case 3:
				if (charLocation.X == 5 && charLocation.Y == 4)
				{
					g_cWallPosition[6][3] = ' ';
				}
				break;
			case 4:
				if (charLocation.X == 65 && charLocation.Y == 5)
				{
					g_cWallPosition[28][28] = ' ';
					g_cWallPosition[29][28] = ' ';	
				}
				if (charLocation.X == 34 && charLocation.Y == 28)
				{
					g_cWallPosition[25][25] = ' ';
					g_cWallPosition[21][25] = ' ';
				}
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
		}
}
void openPath()
{
	switch(level)
		{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				if (charLocation.X == 78 && charLocation.Y == 10)
				{
					g_cWallPosition[78][11] = ' ';
					g_cWallPosition[78][12] = ' ';
					g_cWallPosition[78][13] = ' ';
					g_cWallPosition[79][14] = ' ';
				}
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				if (charLocation.X == 15 && charLocation.Y == 5)
				{
					g_cWallPosition[15][6] = ' ';
				}
				if (charLocation.X == 14 && charLocation.Y == 28)
				{
					g_cWallPosition[15][28] = ' ';
					g_cWallPosition[16][28] = ' ';
					g_cWallPosition[17][28] = ' ';
				}
				if (charLocation.X == 14 && charLocation.Y == 18)
				{
					g_cWallPosition[14][19] = ' ';
				}
				if (charLocation.X == 52 && charLocation.Y == 5)
				{
					for ( int X = 53; X <= 61; X++)
					{
						g_cWallPosition[X][5] = char(177);
					}
					g_cWallPosition[61][4] = ' ';
				}
				if (charLocation.X == 60 && charLocation.Y == 7)
				{
					g_cWallPosition[61][7] = ' ';
					g_cWallPosition[62][7] = ' ';
				}
				break;
			case 7:
				break;
			case 8:
				if (charLocation.X == 56 && charLocation.Y == 6)
				{
					for ( int Y = 6; Y <= 12; Y++)
					{
						g_cWallPosition[57][Y] = ' ';
					}
				}	
				break;
		}
}