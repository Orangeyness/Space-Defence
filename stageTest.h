//REUBEN BELL
//stageInterface.h
//20/11/09
/*
	Interface for stage class.
	--	stages represent a specific point in a 
		game, e.g. the menu, the ingame play.
*/

#include <allegro.h>
#include "stageInterface.h"

namespace stages {

	class stageTest : public StageInterface {
		private:
			int updateCount;

		public:
			stageTest();
			~stageTest();
			virtual bool update();
			virtual void draw(BITMAP *graphicsBuffer);
		};
	
	}