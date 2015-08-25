#include "Framework\timer.h"
#include "Framework\console.h"	
#include "IndicationOfNearbyMonsterThruColour.h"
#include "game.h"
#include "MonsterEncounter.h"

extern int Encounter;
extern Console console;
const int MonsterVeryFarFromPlayer = 100;
const int MonsterSomewhatNearPlayer = 150;
const int MonsterNearPlayer = 180;
const int MonsterVeryNearPlayer = 199;
extern COORD charLocation;

void DisplayifMonsterIsNearOrFarAwayFromPlayer()
{
	if (Encounter <= MonsterVeryFarFromPlayer)
	{
		console.writeToBuffer(charLocation, (char)2, 0x0F);
	}

	else if (Encounter > MonsterVeryFarFromPlayer && Encounter <= MonsterSomewhatNearPlayer)
	{
		console.writeToBuffer(charLocation, (char)2, 0x0A);
	}

	else if (Encounter > MonsterSomewhatNearPlayer && Encounter <= MonsterNearPlayer)
	{
		console.writeToBuffer(charLocation, (char)2, 0x0E);
	}

	else if (Encounter > MonsterNearPlayer && Encounter <= MonsterVeryNearPlayer)
	{
		console.writeToBuffer(charLocation, (char)2, 0x0C);
	}
}