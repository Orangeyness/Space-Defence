#include <allegro.h>
#include <time.h>

#include "global.h"
#include "stageInterface.h"

using namespace stages;
using namespace global;

clock_t globalData::gameStartTime;
StageInterface* globalData::gameCurrentStage;
BITMAP* globalData::gameGraphicsBuffer;

int globalData::gameResolutionX;
int globalData::gameResolutionY;
bool globalData::gameFullScreen;

bool globalData::isGameRunning() {
	return (globalData::gameCurrentStage != NULL);	
	}
