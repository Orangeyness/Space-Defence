
#ifndef _STAGE_PAUSE_MENU
#define _STAGE_PAUSE_MENU

#include <allegro.h>
#include "stageInterface.h"

namespace stages {
	class stagePauseMenu : public StageInterface {
		private:
			StageInterface* rtnStage;
			BITMAP* rtnPreview;

		public:
			stagePauseMenu(StageInterface* parent, BITMAP* preview);
			~stagePauseMenu();
			virtual bool update();
			virtual void draw(BITMAP *graphicsBuffer);
			virtual void pause();
			virtual void resume();
	
		};	
	}

#endif
