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

namespace stages {

	class StageInterface {
		public:
			virtual bool update() = 0; //updates the stage returning whether or not the game has finished. (true = playing, false = finished).
			virtual void draw(BITMAP *graphicsBuffer) = 0; //draws the stage onto the given bitmap.
		};
	
	}

#endif
