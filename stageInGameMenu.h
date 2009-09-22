
#ifndef _STAGE_INGAME_MENU
#define _STAGE_INGAME_MENU

#include <allegro.h>
#include "stageInterface.h"
#include "menuButton.h"

using namespace menu;

namespace stages {
	class stageInGameMenu : public StageInterface {
		private:
			StageInterface* rtnStage;
			BITMAP* rtnPreview;
			
			Button* bntResume;
			Button* bntOptions;
			Button* bntExit;

		public:
			stageInGameMenu(StageInterface* parent, BITMAP* preview);
			~stageInGameMenu();
			virtual bool update();
			virtual void draw(BITMAP *graphicsBuffer);
			virtual void pause();
			virtual void resume();
	
		};	
	}

#endif
