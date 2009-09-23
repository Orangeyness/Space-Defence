#include <allegro.h>
#include "stageOpeningMenu.h"
#include "stageInGameMenu.h"
#include "stageOptionsMenu.h"
#include "stageInGame.h"
#include "stageInterface.h"
#include "inputExtension.h"
#include "global.h"
#include "menuButton.h"

#define C_BLACK makecol(0, 0, 0)
#define C_GREEN makecol(0, 255, 0)
#define C_GRAY makecol(30, 30, 30)

using namespace stages;
using namespace inputExt;
using namespace global;
using namespace menu;

stageInGameMenu::stageInGameMenu(StageInterface* parent, BITMAP* preview) {
	rtnStage = parent;
	rtnPreview = preview;

	for (int x = 1; x < preview->w +2; x+= 3) {
		for (int y = 1; y < preview->w +2; y+= 3) {
			putpixel(rtnPreview, x, y, C_GRAY);
			}		
		}

	bntResume = new Button(SCREEN_W/2 - 80, SCREEN_H/2 - 70, 160, 40, "Resume Game");
	bntOptions = new Button(SCREEN_W/2 - 80, SCREEN_H/2 - 20, 160, 40, "Options");
	bntExit = new Button(SCREEN_W/2 - 80, SCREEN_H/2 + 30, 160, 40, "Exit");

	bntResume->Selected = true;
	bntResume->Next = bntOptions;
	bntResume->Prev = bntExit;
	
	bntOptions->Next = bntExit;
	bntOptions->Prev = bntResume;

	bntExit->Next = bntResume;
	bntExit->Prev = bntOptions;
	}

stageInGameMenu::~stageInGameMenu() {
	delete rtnPreview;

	delete bntResume;
	delete bntOptions;
	delete bntExit;	
	}

void stageInGameMenu::draw(BITMAP *graphicsBuffer) {
	blit(rtnPreview, graphicsBuffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);	

	bntResume->draw(graphicsBuffer);
	bntOptions->draw(graphicsBuffer);
	bntExit->draw(graphicsBuffer);
	}

bool stageInGameMenu::update() {
	bntResume->update();
	bntOptions->update();
	bntExit->update();
	
	if (((keyboard::isKeyPressed(KEY_ENTER) || keyboard::isKeyPressed(KEY_ENTER_PAD)) && bntResume->Selected) || keyboard::isKeyPressed(KEY_ESC)) {
		if (bntExit->Selected) ((stageInGame*)rtnStage)->gameLife += 100;		
		rtnStage->resume();
				
		globalData::gameCurrentStage = rtnStage;
		return STAGE_OVER;		
		}

	if ((keyboard::isKeyPressed(KEY_ENTER) || keyboard::isKeyPressed(KEY_ENTER_PAD)) && bntOptions->Selected) {
		BITMAP *nextBg = create_bitmap(SCREEN_W, SCREEN_H);
		blit(rtnPreview, nextBg, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						
		globalData::gameCurrentStage = new stageOptionsMenu(this, nextBg);
		return STAGE_RUNNING;		
		}

	if ((keyboard::isKeyPressed(KEY_ENTER) || keyboard::isKeyPressed(KEY_ENTER_PAD)) && bntExit->Selected) {
		delete rtnStage;
		globalData::gameCurrentStage = new stageOpeningMenu();
		return STAGE_OVER;		
		}
	
	return STAGE_RUNNING;	
	}

void stageInGameMenu::pause() { }
void stageInGameMenu::resume() { 
	delete bntResume;
	delete bntOptions;
	delete bntExit;	
	delete rtnPreview;
	
	rtnPreview = create_bitmap(SCREEN_W, SCREEN_H);
	rtnStage->draw(rtnPreview);

	for (int x = 1; x < rtnPreview->w +2; x+= 3) {
		for (int y = 1; y < rtnPreview->w +2; y+= 3) {
			putpixel(rtnPreview, x, y, C_GRAY);
			}		
		}

	bntResume = new Button(SCREEN_W/2 - 80, SCREEN_H/2 - 70, 160, 40, "Resume Game");
	bntOptions = new Button(SCREEN_W/2 - 80, SCREEN_H/2 - 20, 160, 40, "Options");
	bntExit = new Button(SCREEN_W/2 - 80, SCREEN_H/2 + 30, 160, 40, "Exit");

	bntResume->Selected = true;
	bntResume->Next = bntOptions;
	bntResume->Prev = bntExit;
	
	bntOptions->Next = bntExit;
	bntOptions->Prev = bntResume;

	bntExit->Next = bntResume;
	bntExit->Prev = bntOptions;
	}
