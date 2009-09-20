//REUBEN BELL
//12:47 AM 20/11/2009
//The entry point for the game, space defence.

#include <allegro.h>
#include <stdlib.h>
#include <time.h>

#include "stageInterface.h"
#include "stageInGame.h"
#include "inputExtension.h"

#define GFX_TYPE GFX_AUTODETECT_WINDOWED
#define GFX_WIDTH 1024
#define GFX_HEIGHT 768

#define FPS_TARGET 30



using namespace stages;
using namespace inputExt;

volatile int frameTickCount;
void updateTicks();

int main(int argc, char * argv[]) {
	if (allegro_init() != 0) return EXIT_FAILURE;
	
	install_timer();
	install_keyboard();
	install_mouse();	

	LOCK_VARIABLE(frameTickCount);
	LOCK_FUNCTION(updateTicks);

	set_gfx_mode(GFX_TYPE, GFX_WIDTH, GFX_HEIGHT, 0, 0);

	srand(time(NULL));

	bool gameRunning = true;
	time_t gameStartTime = time (NULL);
	BITMAP *gameGraphicsBuffer = create_bitmap(SCREEN_W, SCREEN_H);
	StageInterface *gameCurrentStage = new stageInGame();

	int frameDesiredRate = FPS_TARGET;
	int frameDesiredLength = 1000/frameDesiredRate;
	int frameLastRate = frameDesiredRate;
	int framePastThisSecond = 0;
	time_t frameSecondStartTime = gameStartTime;

	install_int(updateTicks, frameDesiredLength);

	while(gameRunning) {
		if (difftime(time(NULL), frameSecondStartTime) >= 1) {
			frameLastRate = framePastThisSecond;
			framePastThisSecond = 0;
			frameSecondStartTime = time(NULL);
			}

		while (frameTickCount > 0 && gameRunning) {
			frameTickCount --;
			
			keyboard::update();

			gameRunning = gameCurrentStage->update();

			framePastThisSecond ++;
			}
		
		blit(gameGraphicsBuffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		gameCurrentStage->draw(gameGraphicsBuffer);

		rest(1);
		}

	delete gameCurrentStage;
	destroy_bitmap(gameGraphicsBuffer);
	

	return EXIT_SUCCESS;
	}
END_OF_MAIN();

void updateTicks() {
	frameTickCount ++;	
	}
END_OF_FUNCTION(timerUpdater);
