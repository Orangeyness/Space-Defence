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

#define PI 3.14159265
#define TARGET_SIZE 32
#define TURRET_X 60
#define TURRET_Y SCREEN_H - 60
#define TURRET_BASE_RADIUS 30
#define TURRET_BARREL_RADIUS 60

#define INPUT_FILE "game.txt"

#define C_WHITE makecol(255, 255, 255)
#define C_BLACK makecol(0, 0, 0)
#define C_GREEN makecol(0, 255, 0)
#define C_RED makecol(255, 0, 0)

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

	currentQuestion = "2 + 2 = ?";
	currentAnswer = 5;

	inputSpawnFile.open (INPUT_FILE);
	inputSpawnSpeed = 2;
	inputSpawnNext = clock() + inputSpawnSpeed * CLOCKS_PER_SEC;

	gameLevel = 0;
	drawLevel = false;
	drawLevelEndTime = 0;
	drawLevelLength = 2;
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

	inputSpawnFile.close();
	}

bool stageInGame::update() {
	if (keyboard::isKeyPressed(KEY_ESC)) return false;

	if (clock() > inputSpawnNext) {
		bool success = loadObjects();
		if (!success) return false;		
		}

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
		myBullet = new objBullet(TURRET_X, TURRET_Y, hudTargetX, hudTargetY, hudTurretDirection, 50);
		hudTargetLocked = false;
		}

	return true;
	}

void stageInGame::draw(BITMAP *graphicsBuffer) {
	clear_to_color(graphicsBuffer, C_BLACK);	

	if (myBullet != NULL) myBullet->draw(graphicsBuffer);

	drawObjectList(objListAsteroid.getFirst(), graphicsBuffer);
	drawObjectList(objListParticle.getFirst(), graphicsBuffer);

	textprintf_ex(graphicsBuffer, font, 10, 10, C_WHITE, -1, "Objects: %d", objListAsteroid.nodeCount);
	textprintf_ex(graphicsBuffer, font, 10, 30, C_WHITE, -1, "Particles: %d", objListParticle.nodeCount);
	textprintf_ex(graphicsBuffer, font, 10, 70, C_WHITE, -1, "LEVEL: %d!", gameLevel);
	if (drawLevel) {
		if (drawLevelEndTime < clock()) drawLevel = false;
		textprintf_centre_ex(graphicsBuffer, font, SCREEN_W/2, SCREEN_H/2, C_GREEN, -1, "LEVEL: %d!", gameLevel);
		}

	drawHud(graphicsBuffer);
	drawTurret(graphicsBuffer);
	}

bool stageInGame::loadObjects() {
	if (inputSpawnFile.is_open() == false) {
		allegro_message("Error: could not read input file. You better not have deleted it, mmmkay?");		
		return false;		
		}

	if (inputSpawnFile.eof()) {
		inputSpawnFile.close();
		inputSpawnFile.open (INPUT_FILE);
		}

	string spawnLine;
	getline(inputSpawnFile, spawnLine);
	
	bool delayNextSpawn = true;

	for (unsigned int i = 0; i < spawnLine.length(); i++) {
		switch(spawnLine[i]) {
			case '1': {
				objListAsteroid.addFirst(new objAsteroid(i * (SCREEN_W / spawnLine.length()), -10, 15 + rand() % 15, 20, 1-rand()%2, 1+rand()%1));
				}break;
			case '2': {
				objListAsteroid.addFirst(new objAsteroid(i * (SCREEN_W / spawnLine.length()), -10, 30 + rand() % 15, 20, 1-rand()%2, 1+rand()%1));
				}break;
			case '3': {
				objListAsteroid.addFirst(new objAsteroid(i * (SCREEN_W / spawnLine.length()), -10, 45 + rand() % 15, 20, 1-rand()%2, 1+rand()%1));
				}break;
			case '4': {
				objListAsteroid.addFirst(new objAsteroid(i * (SCREEN_W / spawnLine.length()), -10, 60 + rand() % 15, 20, 1-rand()%2, 1+rand()%1));
				}break;
			case '5': {
				objListAsteroid.addFirst(new objAsteroid(i * (SCREEN_W / spawnLine.length()), -10, 75 + rand() % 15, 20, 1-rand()%2, 1+rand()%1));
				}break;
			case '6': {
				objListAsteroid.addFirst(new objAsteroid(i * (SCREEN_W / spawnLine.length()), -10, 90 + rand() % 15, 20, 1-rand()%2, 1+rand()%1));
				}break;
			case '7': {
				objListAsteroid.addFirst(new objAsteroid(i * (SCREEN_W / spawnLine.length()), -10, 105 + rand() % 15, 20, 1-rand()%2, 1+rand()%1));
				}break;
			case '8': {
				objListAsteroid.addFirst(new objAsteroid(i * (SCREEN_W / spawnLine.length()), -10, 120 + rand() % 15, 20, 1-rand()%2, 1+rand()%1));
				}break;
			case '9': {
				objListAsteroid.addFirst(new objAsteroid(i * (SCREEN_W / spawnLine.length()), -10, 135 + rand() % 15, 20, 1-rand()%2, 1+rand()%1));
				}break;


			case 'S': {
				if (i == 0 && spawnLine[i+1] == '-') inputSpawnSpeed += 0.2;
				if (i == 0 && spawnLine[i+1] == '+') inputSpawnSpeed -= 0.2;
				delayNextSpawn = false;
				i = spawnLine.length();
				}

			case 'L': {
				gameLevel ++;
				drawLevel = true;
				drawLevelEndTime = clock() + drawLevelLength * CLOCKS_PER_SEC;
				i = spawnLine.length();
				}
			}		
		}
		

	if (delayNextSpawn) inputSpawnNext = clock() + inputSpawnSpeed * CLOCKS_PER_SEC;
	return true;
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

void stageInGame::updateObjectList(LinkedListNode<ObjectInterface*>* Node) {
	while(Node != NULL) {
		ObjectInterface* obj = Node->getValue();
		LinkedListNode<ObjectInterface*>* toDelete = NULL;

		if (obj != NULL) {
			bool keep = obj->update(&objListAsteroid, &objListParticle);
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

void stageInGame::drawObjectList(LinkedListNode<ObjectInterface*>* Node, BITMAP* graphicsBuffer) {
	while(Node != NULL) {
		Node->getValue()->draw(graphicsBuffer);
		Node = Node->getNext();
		}
	}
