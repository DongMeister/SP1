#ifndef _DIALOGUE_H
#define _DIALOGUE_H

#include <fstream>
#include <string>
#include "Framework\console.h"

void dialoge(std::string Stuff);
void opendialog();
std::string choosedialog(int i);

extern Console console;

#endif