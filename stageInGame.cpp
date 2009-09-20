#include <allegro.h>
#include "stageInGame.h"
#include "objectAsteroid.h"

using namespace stages;
using namespace objects;

stageInGame::stageInGame() {
	hudTargetX = SCREEN_W/2;
	hudTargetY = SCREEN_H/2;

	hudTargetXSpeed = 0;
	hudTargetYSpeed = 0;
	hudTargetFriction = 0.3;
	hudTargetAcceleration = 0.6;
	hudTargetMaxSpeed = 10;

	hudTargetLocked = false;

	Asteroid = new objAsteroid(SCREEN_W/2, SCREEN_H/2, 50, 20);
	}

stageInGame::~stageInGame() {
	delete Asteroid;
	}

bool stageInGame::update() {
	if (key[KEY_ESC]) return false;

	Asteroid->update();

	updateHud();

	return true;
	}

void stageInGame::draw(BITMAP *graphicsBuffer) {
	clear_to_color(graphicsBuffer, C_BLACK);	

	Asteroid->draw(graphicsBuffer);

	drawHud(graphicsBuffer);
	}

void stageInGame::updateHud() {
	if (!hudTargetLocked) {
		if ((key[KEY_LEFT] || key[KEY_A]) && hudTargetXSpeed > -hudTargetMaxSpeed) hudTargetXSpeed -= hudTargetAcceleration;
		if ((key[KEY_RIGHT] || key[KEY_D]) && hudTargetXSpeed < hudTargetMaxSpeed) hudTargetXSpeed += hudTargetAcceleration;
		if ((key[KEY_UP] || key[KEY_W]) && hudTargetYSpeed > -hudTargetMaxSpeed) hudTargetYSpeed -= hudTargetAcceleration;
		if ((key[KEY_DOWN] || key[KEY_S]) && hudTargetYSpeed < hudTargetMaxSpeed) hudTargetYSpeed += hudTargetAcceleration;
		
		if (hudTargetXSpeed < 0) {
			if (hudTargetXSpeed > -hudTargetFriction) 
					hudTargetXSpeed = 0;
				else
					hudTargetXSpeed += hudTargetFriction;			
			}

		if (hudTargetXSpeed > 0) {
			if (hudTargetXSpeed < hudTargetFriction) 
					hudTargetXSpeed = 0;
				else
					hudTargetXSpeed -= hudTargetFriction;			
			}

		if (hudTargetYSpeed < 0) {
			if (hudTargetYSpeed > -hudTargetFriction) 
					hudTargetYSpeed = 0;
				else
					hudTargetYSpeed += hudTargetFriction;			
			}

		if (hudTargetYSpeed > 0) {
			if (hudTargetYSpeed < hudTargetFriction) 
					hudTargetYSpeed = 0;
				else
					hudTargetYSpeed -= hudTargetFriction;			
			}
		}
			else
		{
		hudTargetXSpeed = 0;
		hudTargetYSpeed = 0;
		}

	if (key[KEY_SPACE]) hudTargetLocked =!hudTargetLocked;

	hudTargetX = (int)(hudTargetX + hudTargetXSpeed);
	hudTargetY = (int)(hudTargetY + hudTargetYSpeed);
	}

void stageInGame::drawHud(BITMAP *graphicsBuffer) {
	int Col = C_GREEN;
	if (hudTargetLocked == true) Col = C_RED;

	line(graphicsBuffer, hudTargetX, 0, hudTargetX, hudTargetY - TARGET_SIZE, Col);	
	line(graphicsBuffer, hudTargetX, hudTargetY + TARGET_SIZE, hudTargetX, SCREEN_H, Col);	
	line(graphicsBuffer, 0, hudTargetY, hudTargetX - TARGET_SIZE, hudTargetY, Col);	
	line(graphicsBuffer, hudTargetX + TARGET_SIZE, hudTargetY, SCREEN_W, hudTargetY, Col);	

	line(graphicsBuffer, hudTargetX-TARGET_SIZE, hudTargetY - TARGET_SIZE/2, hudTargetX-TARGET_SIZE, hudTargetY + TARGET_SIZE/2, Col);
	line(graphicsBuffer, hudTargetX+TARGET_SIZE, hudTargetY - TARGET_SIZE/2, hudTargetX+TARGET_SIZE, hudTargetY + TARGET_SIZE/2, Col);
	line(graphicsBuffer, hudTargetX - TARGET_SIZE/2, hudTargetY-TARGET_SIZE, hudTargetX + TARGET_SIZE/2, hudTargetY-TARGET_SIZE, Col);
	line(graphicsBuffer, hudTargetX - TARGET_SIZE/2, hudTargetY+TARGET_SIZE, hudTargetX + TARGET_SIZE/2, hudTargetY+TARGET_SIZE, Col);

	}
