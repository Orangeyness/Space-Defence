//REUBEN BELL
//stageTest.h
//20/11/09

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
