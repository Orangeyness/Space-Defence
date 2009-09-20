#include <allegro.h>
#include <math.h>
#include <time.h>


#include "stageInGame.h"
#include "objectAsteroid.h"
#include "objectParticle.h"
#include "objectBullet.h"
#include "inputExtension.h"
#include "stageInterface.h"
#include "linkedLists.h"

using namespace stages;
using namespace objects;
using namespace inputExt;
using namespace linkedLists;

stageInGame::stageInGame() {
	hudTargetX = SCREEN_W/2;
	hudTargetY = SCREEN_H/2;

	hudTargetXSpeed = 0;
	hudTargetYSpeed = 0;
	hudTargetFriction = 0.3;
	hudTargetAcceleration = 0.6;
	hudTargetMaxSpeed = 10;

	hudTargetLocked = false;

	hudTurretDirection = 0;

	myBullet = NULL;
	objListAsteroid.addFirst(new objAsteroid(100, 100, 50, 20, 0, 1));
	objListAsteroid.addFirst(new objAsteroid(100, 200, 40, 20, 0, 1));

	objListParticle.addFirst(new objParticle(100, 100, 1.0, 1.0, 10, 0, makecol(255, 10, 0), makecol(0, 0, 0), 0.5));

	currentQuestion = "2 + 2 = ?";
	currentAnswer = 5;
	}

stageInGame::~stageInGame() {
	if (myBullet != NULL) delete myBullet;
	
	while(objListAsteroid.nodeCount > 0) {
		delete objListAsteroid.getFirstValue();	
		objListAsteroid.getFirst()->remove();
		}

	while(objListParticle.nodeCount > 0) {
		delete objListParticle.getFirstValue();	
		objListParticle.getFirst()->remove();
		}
	}

bool stageInGame::update() {
	if (keyboard::isKeyPressed(KEY_ESC)) return false;

	if (myBullet != NULL) {
		bool K = myBullet->update(&objListAsteroid, &objListParticle);
		if (!K) {
			delete myBullet;
			myBullet = NULL;
			}		
		}

	updateObjectList(objListAsteroid.getFirst());
	updateObjectList(objListParticle.getFirst());

	updateHud();

	if ((keyboard::isKeyPressed(KEY_ENTER) || keyboard::isKeyPressed(KEY_ENTER_PAD)) && hudTargetLocked && myBullet == NULL) {
		myBullet = new objBullet(TURRET_X, TURRET_Y, hudTargetX, hudTargetY, hudTurretDirection, 30);
		}

	return true;
	}

void stageInGame::draw(BITMAP *graphicsBuffer) {
	clear_to_color(graphicsBuffer, C_BLACK);	

	if (myBullet != NULL) myBullet->draw(graphicsBuffer);

	drawObjectList(objListAsteroid.getFirst(), graphicsBuffer);
	drawObjectList(objListParticle.getFirst(), graphicsBuffer);

	drawHud(graphicsBuffer);
	drawTurret(graphicsBuffer);
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

	if (keyboard::isKeyPressed(KEY_SPACE)) hudTargetLocked =!hudTargetLocked;

	hudTargetX = (int)(hudTargetX + hudTargetXSpeed);
	hudTargetY = (int)(hudTargetY + hudTargetYSpeed);

	hudTurretDirection = atan2(hudTargetX - TURRET_X, -(TURRET_Y - hudTargetY));
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

	if (hudTargetLocked) {
		textout_ex(graphicsBuffer, font, currentQuestion.c_str(), hudTargetX + TARGET_SIZE * 1.5, hudTargetY + 10, Col, -1);
		}
			else
		{
		textprintf_ex(graphicsBuffer, font, hudTargetX + TARGET_SIZE * 1.5, hudTargetY + 10, Col, C_BLACK, "(%d, %d)", hudTargetX, hudTargetY);
		}

	putpixel(graphicsBuffer, hudTargetX, hudTargetY, Col);
	}

void stageInGame::drawTurret(BITMAP *graphicsBuffer) {
	circle(graphicsBuffer, TURRET_X, TURRET_Y, TURRET_BASE_RADIUS, C_GREEN);
	int Dx = TURRET_X + (int)(TURRET_BARREL_RADIUS * sin(hudTurretDirection));
	int Dy = TURRET_Y + (int)(TURRET_BARREL_RADIUS * cos(hudTurretDirection));

	line(graphicsBuffer, TURRET_X, TURRET_Y, Dx, Dy, C_GREEN);
	
	}

void stageInGame::updateObjectList(LinkedListNode<ObjectInterface*>* Node) {
	while(Node != NULL) {
		ObjectInterface* obj = Node->getValue();
		LinkedListNode<ObjectInterface*>* toDelete = NULL;

		if (obj != NULL) {
			bool keep = obj->update();
			if (!keep) {
				delete obj;
				toDelete = Node;				
				}
			}
				else
			{
			toDelete = Node;	
			}
		Node = Node->getNext();
		
		if (toDelete != NULL) {
			toDelete->remove();			
			}
		}
	}

void stageInGame::drawObjectList(LinkedListNode<ObjectInterface*>* Node, BITMAP* graphicsBuffer) {
	while(Node != NULL) {
		Node->getValue()->draw(graphicsBuffer);
		Node = Node->getNext();
		}
	}
