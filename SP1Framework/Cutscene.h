#ifndef _CUTSCENE_H
#define _CUTSCENE_H

#include <string>
#include <fstream>
#include "game.h"
#include "Framework\console.h"
#include "OpenMap.h"
#include "game.h"
#include "MusicFiles.h"

void renderCutscene();
void loadCutscene();
void renderCutsceneCharacter();
void PauseCharacter();
void CutsceneDialog();
void renderCutscenedialog(std::string Stuff);
void LoadCutsceneDialogue();

#endif 