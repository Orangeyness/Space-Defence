
#ifndef _STAGE_OPTIONS_MENU
#define _STAGE_OPTIONS_MENU

#include <allegro.h>
#include "stageInterface.h"
#include "menuButton.h"

#define RESOLUTION_COUNT 4

using namespace menu;

namespace stages {
	class stageOptionsMenu : public StageInterface {
		private:
			StageInterface* rtnStage;
			BITMAP* rtnPreview;
			
			Button* bntApply;
			Button* bntCancel;
			Button* bntReset;
			Button* bntResolution;
			Button* bntFullScreen;

			int resolutions[RESOLUTION_COUNT][2];
			int resolution;
			bool fullScreen;
			
			int currentResolution;
			int currentFullScreen;

		public:
			stageOptionsMenu(StageInterface* parent, BITMAP* preview);
			~stageOptionsMenu();
			virtual bool update();
			virtual void draw(BITMAP *graphicsBuffer);
			virtual void pause();
			virtual void resume();
	
		};	
	}

#endif
