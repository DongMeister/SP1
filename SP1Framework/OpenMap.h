#ifndef _OPENMAP_H
#define _OPENMAP_H

#include "Framework\console.h"

#include <sstream>
#include <fstream>
#include <string>
#include "HealthBar.h"


void openMap(int i);
void restart();
void openDoor();
void checkAdvance();
void checkIfThereAreTraps();
bool checkArray();
void closeTraps();
void shortcut();
void openTraps();

#endif