#ifndef _CONTROLS_H
#define _CONTROLS_H

#include <string>
#include "game.h"
#include "HealthBar.h"
#include "MainMenu.h"
#include "OpenMap.h"
#include "Dialogue.h"
#include "Cutscene.h"



void ChooseBattleMenu();
void ChooseBattleKeypress();
void BattleKeypress();
void GameOverKeypress();
void CorrectKeypress();
void WrongKeypress();
void ClearStageKeypress();
void SkipCutsceneIfSpaceIsPressed();

#endif