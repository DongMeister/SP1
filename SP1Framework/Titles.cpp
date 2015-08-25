#include "Titles.h"

extern Screen state;
extern Console console;

std::string TitleForGame(double TotalPoints)
{
	std::string title[6] = {"Beginner","Amateur","Veteran","Professional","Legendary","Godly"};

	if (TotalPoints == 0)
	{
		return title[0];
	}
		
	else if (TotalPoints > 0 && TotalPoints <= 5000)
	{
		return title[1];
	}

	else if (TotalPoints > 5000 && TotalPoints <= 10000)
	{
		return title[2];
	}

	else if (TotalPoints >10000 && TotalPoints <= 15000)
	{
		return title[3];
	}

	else if (TotalPoints > 15000 && TotalPoints <= 20000)
	{
		return title[4];
	}
	else if (TotalPoints > 20000)
	{
		return title[5];
	}
	else
	{
		return title[0];
	}
}