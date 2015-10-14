//REUBEN BELL
//12:47 AM 20/11/2009
//The entry point for the game, space defence.

#include <allegro.h>
#include <stdlib.h>
#include <time.h>

#include "global.h"
#include "stageInterface.h"
#include "stageOpeningMenu.h"
#include "inputExtension.h"

#define DEFUALT_GFX_FULLSCREEN false
#define DEFUALT_GFX_WIDTH 1024
#define DEFUALT_GFX_HEIGHT 768

#define FPS_TARGET 30



using namespace stages;
using namespace inputExt;
using namespace global;

volatile int frameTickCount;
void updateTicks();



int main(int argc, char * argv[]) {
	if (allegro_init() != 0) return EXIT_FAILURE;
	
	install_timer();
	install_keyboard();
	install_mouse();	

	LOCK_VARIABLE(frameTickCount);
	LOCK_FUNCTION(updateTicks);


	globalData::read();

	int success;
	if (globalData::gameFullScreen) 
		success = set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, globalData::gameResolutionX, globalData::gameResolutionY, 0, 0);
	else
		success = set_gfx_mode(GFX_AUTODETECT_WINDOWED, globalData::gameResolutionX, globalData::gameResolutionY, 0, 0);

	if (success < 0) {
		allegro_message("Current graphics settings failed. Attempting failsafe.");
		globalData::failSafe();

		if (globalData::gameFullScreen) 
			success = set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, globalData::gameResolutionX, globalData::gameResolutionY, 0, 0);
		else
			success = set_gfx_mode(GFX_AUTODETECT_WINDOWED, globalData::gameResolutionX, globalData::gameResolutionY, 0, 0);
		
		if (success < 0) {
			allegro_message("Failsafe... failed. Well game over.");
			return EXIT_FAILURE;			
			}
		}

	globalData::gameStartTime = time (NULL);
	globalData::gameGraphicsBuffer = create_bitmap(SCREEN_W, SCREEN_H);
	globalData::gameCurrentStage = new stageOpeningMenu();

	srand(time(NULL));



	int frameDesiredRate = FPS_TARGET;
	int frameDesiredLength = 1000/frameDesiredRate;
	int framePastThisSecond = 0;
	time_t frameSecondStartTime = globalData::gameStartTime;

	install_int(updateTicks, frameDesiredLength);

	while(globalData::isGameRunning() == true) {
		if (difftime(time(NULL), frameSecondStartTime) >= 1) {
			framePastThisSecond = 0;
			frameSecondStartTime = time(NULL);
			}

		while (frameTickCount > 0 && globalData::isGameRunning() == true) {
			frameTickCount --;
			
			keyboard::update();
			
			StageInterface *stage = globalData::gameCurrentStage;
			bool stageState = stage->update();
			if (stageState == STAGE_OVER) {
				if (globalData::gameCurrentStage == stage) globalData::gameCurrentStage = NULL;
				delete stage;
				}				
			framePastThisSecond ++;
			}
		
		if (globalData::isGameRunning() == true) {
			blit(globalData::gameGraphicsBuffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			globalData::gameCurrentStage->draw(globalData::gameGraphicsBuffer);
			}

		rest(1);
		}

	if (globalData::gameCurrentStage == NULL) delete globalData::gameCurrentStage;
	destroy_bitmap(globalData::gameGraphicsBuffer);
	

	return EXIT_SUCCESS;
	}
END_OF_MAIN();

void updateTicks() {
	frameTickCount ++;	
	}
END_OF_FUNCTION(timerUpdater);
