#include <allegro.h>
#include "stageTest.h"

using namespace stages;

stageTest::stageTest() {
	updateCount = 0;
	}

stageTest::~stageTest() {
	}

bool stageTest::update() {
	updateCount ++;

	return (!keypressed());
	}

void stageTest::draw(BITMAP *graphicsBuffer) {
	clear_to_color(graphicsBuffer, makecol(255, 255, 255));	
	textprintf_ex(graphicsBuffer, font, 20, 20, makecol(10, 10, 10), -1, "BLAM: %d", updateCount);
	}
