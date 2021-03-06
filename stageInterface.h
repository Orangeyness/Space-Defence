//REUBEN BELL
//stageInterface.h
//20/11/09
/*
	Interface for stage class.
	--	stages represent a specific point in a 
		game, e.g. the menu, the ingame play.
*/

#include <allegro.h>

#ifndef _STAGE_INTERFACE_
#define _STAGE_INTERFACE_

#define STAGE_RUNNING true
#define STAGE_OVER false

namespace stages {

	class StageInterface {
		public:
                        virtual ~StageInterface() { }
			virtual bool update() = 0; //updates the stage returning whether or not the game has finished. (true = playing, false = finished).
			virtual void draw(BITMAP *graphicsBuffer) = 0; //draws the stage onto the given bitmap.
			virtual void pause() = 0; //Prepares the stage to stopped and paused to a pausing stage.
			virtual void resume() = 0; //Prepares the stage to return to processing.
		};
	
	}

#endif
