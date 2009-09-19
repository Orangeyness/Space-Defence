//REUBEN BELL
//stageInterface.h
//20/11/09
/*
	Interface for stage class.
	--	stages represent a specific point in a 
		game, e.g. the menu, the ingame play.
*/

#include <allegro.h>

namespace stages {

	class StageInterface {
		public:
			virtual bool update(); //updates the stage returning whether or not the game has finished. (true = playing, false = finished).
			virtual void draw(BITMAP *graphicsBuffer); //draws the stage onto the given bitmap.
		};
	
	}
