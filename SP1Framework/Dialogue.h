#ifndef _DIALOGUE_H
#define _DIALOGUE_H

#include <fstream>
#include <string>
#include "Framework\console.h"

void WriteDialogue(std::string Stuff);
void LoadDialogue();
std::string choosedialog(int i);

extern Console console;

#endif