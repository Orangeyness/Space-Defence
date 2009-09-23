#include <allegro.h>
#include <time.h>
#include <fstream>

#include "global.h"
#include "stageInterface.h"

#define SETTINGS_FILE "settings"

using namespace std;
using namespace stages;
using namespace global;

clock_t globalData::gameStartTime;
StageInterface* globalData::gameCurrentStage;
BITMAP* globalData::gameGraphicsBuffer;

int globalData::gameResolutionX;
int globalData::gameResolutionY;
bool globalData::gameFullScreen;

void globalData::failSafe() {
	globalData::gameResolutionX = 640;
	globalData::gameResolutionY = 480;
	globalData::gameFullScreen = false;
	}

void globalData::read() {
	fstream settingsFile(SETTINGS_FILE);
	if (settingsFile.is_open()) {
		settingsFile >> globalData::gameResolutionX;
		settingsFile >> globalData::gameResolutionY;
		int chk;
		settingsFile >> chk;
		if (chk == 1) globalData::gameFullScreen = true;
				else globalData::gameFullScreen = false;
		}
			else
		{
		allegro_message("Settings file could not be found. Using fail safe settings.");
		failSafe();
		}
	settingsFile.close();
	}

void globalData::write() {
	fstream settingsFile(SETTINGS_FILE, ios::out);
	if (settingsFile.is_open()) {
		settingsFile << globalData::gameResolutionX << endl << globalData::gameResolutionY << endl << globalData::gameFullScreen << endl;
		}
			else
		{
		allegro_message("Settings file could not be opened.");
		}
	settingsFile.close();
	}

bool globalData::isGameRunning() {
	return (globalData::gameCurrentStage != NULL);	
	}
