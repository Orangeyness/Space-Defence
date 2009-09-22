#include <allegro.h>
#include "stagePauseMenu.h"
#include "stageInterface.h"
#include "inputExtension.h"
#include "global.h"

#define C_BLACK makecol(0, 0, 0)
#define C_GREEN makecol(0, 255, 0)
#define C_GRAY makecol(30, 30, 30)

using namespace stages;
using namespace inputExt;
using namespace global;

stagePauseMenu::stagePauseMenu(StageInterface* parent, BITMAP* preview) {
	rtnStage = parent;
	rtnPreview = preview;

	for (int x = 1; x < preview->w +2; x+= 3) {
		for (int y = 1; y < preview->w +2; y+= 3) {
			putpixel(rtnPreview, x, y, C_GRAY);
			}		
		}
	}

stagePauseMenu::~stagePauseMenu() {
	delete rtnPreview;	
	}

void stagePauseMenu::draw(BITMAP *graphicsBuffer) {
	blit(rtnPreview, graphicsBuffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	rectfill(graphicsBuffer, SCREEN_W/2 - 80, SCREEN_H/2 - 40, SCREEN_W/2 + 80, SCREEN_H/2 + 40, C_BLACK);
	rect(graphicsBuffer, SCREEN_W/2 - 80, SCREEN_H/2 - 40, SCREEN_W/2 + 80, SCREEN_H/2 + 40, C_GREEN);
	textprintf_centre_ex(graphicsBuffer, font, SCREEN_W/2, SCREEN_H/2, C_GREEN, -1, "PAUSED");
	}

bool stagePauseMenu::update() {
	if (keyboard::isKeyPressed(KEY_P) || keyboard::isKeyPressed(KEY_ESC)) {
		rtnStage->resume();
				
		globalData::gameCurrentStage = rtnStage;
		return STAGE_OVER;		
		}
	
	return STAGE_RUNNING;	
	}

void stagePauseMenu::pause() { }
void stagePauseMenu::resume() { }
