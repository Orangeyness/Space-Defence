
#ifndef _GLOBAL_
#define _GLOBAL_

#include <allegro.h>
#include <time.h>
#include "stageInterface.h"

using namespace stages;

namespace global {
	class globalData {
		public:
			static clock_t gameStartTime;
			static StageInterface* gameCurrentStage;
			static BITMAP* gameGraphicsBuffer;
			static int gameResolutionX;
			static int gameResolutionY;
			static bool gameFullScreen;

			static bool isGameRunning();
		};	
	}

#endif
