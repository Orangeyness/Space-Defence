#include <allegro.h>

#include "stageInterface.h"
#include "stageOpeningMenu.h"
#include "stageAboutGame.h"

#include "objectInterface.h"
#include "objectAsteroid.h"

#include "menuButton.h"
#include "inputExtension.h"
#include "linkedLists.h"
#include "global.h"

#define C_BLACK makecol(0, 0, 0)
#define C_GREEN makecol(0, 255, 0)


using namespace linkedLists;
using namespace menu;
using namespace stages;
using namespace objects;
using namespace inputExt;
using namespace global;

stageAboutGame::stageAboutGame() {
	page = 0;
	
	bntMenu = new Button(SCREEN_W/2 - 180, SCREEN_H/2 + 100, 90, 30, "Main Menu");
	bntNext = new Button(SCREEN_W/2 + 100, SCREEN_H/2 + 100, 90, 30, "Next");	
	bntPrev = new Button(SCREEN_W/2, SCREEN_H/2 + 100, 90, 30, "Previous");

	bntNext->Selected = true;
	bntNext->Next = bntMenu;
	bntNext->Prev = bntPrev;
	
	bntMenu->Next = bntPrev;
	bntMenu->Prev = bntNext;

	bntPrev->Next = bntNext;
	bntPrev->Prev = bntMenu;
	}

stageAboutGame::~stageAboutGame() {
	delete bntMenu;
	delete bntNext;
	delete bntPrev;	
	
	while(objListAsteroid.nodeCount > 0) {
		delete objListAsteroid.getFirstValue();	
		objListAsteroid.getFirst()->remove();
		}	
	}

bool stageAboutGame::update() {
	bntMenu->update();
	bntNext->update();
	bntPrev->update();	

	updateObjectList(objListAsteroid.getFirst());

	if (((keyboard::isKeyPressed(KEY_ENTER) || keyboard::isKeyPressed(KEY_ENTER_PAD)) && bntMenu->Selected) || keyboard::isKeyPressed(KEY_ESC)) {
		globalData::gameCurrentStage = new stageOpeningMenu();
		return STAGE_OVER;			
		}

	if ((keyboard::isKeyPressed(KEY_ENTER) || keyboard::isKeyPressed(KEY_ENTER_PAD)) && bntNext->Selected) {
		page ++;
		if (page == PAGE_COUNT) page = 0;
		}

	if ((keyboard::isKeyPressed(KEY_ENTER) || keyboard::isKeyPressed(KEY_ENTER_PAD)) && bntPrev->Selected) {
		page --;
		if (page < 0) page = PAGE_COUNT-1;
		}

	return STAGE_RUNNING;	
	}

void stageAboutGame::draw(BITMAP *graphicsBuffer) {
	clear_to_color(graphicsBuffer, C_BLACK);
	drawObjectList(objListAsteroid.getFirst(), graphicsBuffer);

	rectfill		(graphicsBuffer, SCREEN_W/2-200, SCREEN_H/2-150, SCREEN_W/2+200, SCREEN_H/2+150, C_BLACK);
	rect 			(graphicsBuffer, SCREEN_W/2-200, SCREEN_H/2-150, SCREEN_W/2+200, SCREEN_H/2+150, C_GREEN);
	textout_ex	(graphicsBuffer, font, "About The Game", SCREEN_W/2-180, SCREEN_H/2-140, C_GREEN, -1);
	line 			(graphicsBuffer, SCREEN_W/2-180, SCREEN_H/2-120, SCREEN_W/2+180, SCREEN_H/2-120, C_GREEN);
	textprintf_right_ex(graphicsBuffer, font, SCREEN_W/2+180, SCREEN_H/2-140, C_GREEN, -1, "Page: %d", (page+1));

	switch(page) {
		case 0: {
			textout_ex	(graphicsBuffer, font, "The Aim.", SCREEN_W/2-180, SCREEN_H/2-110, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "The aim of this game, 'Space Defence' is to", SCREEN_W/2-180, SCREEN_H/2-80, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "defend your base, the bottom of the screen ", SCREEN_W/2-180, SCREEN_H/2-65, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "from an onslaught of asteroids. An asteroid", SCREEN_W/2-180, SCREEN_H/2-50, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "shower you might say. You control a turret ", SCREEN_W/2-180, SCREEN_H/2-35, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "in the bottom left corner of the screen.   ", SCREEN_W/2-180, SCREEN_H/2-20, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "To destroy the asteroids you are required to", SCREEN_W/2-180, SCREEN_H/2-5, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "first solve a maths question.              ", SCREEN_W/2-180, SCREEN_H/2+10, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "Have, fun.", SCREEN_W/2-180, SCREEN_H/2+40, C_GREEN, -1);
			} break;
		case 1: {
			textout_ex	(graphicsBuffer, font, "The Controls.", SCREEN_W/2-180, SCREEN_H/2-110, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "Positioning the crosshair                    ", SCREEN_W/2-180, SCREEN_H/2-80, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "  -move left   = Left arror key or 'A'       ", SCREEN_W/2-180, SCREEN_H/2-65, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "  -move right  = Right arror key or 'D'      ", SCREEN_W/2-180, SCREEN_H/2-50, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "  -move up     = Up arror key or 'W'         ", SCREEN_W/2-180, SCREEN_H/2-35, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "  -move down   = Down arror key or 'S'       ", SCREEN_W/2-180, SCREEN_H/2-20, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "Locking crosshair position                   ", SCREEN_W/2-180, SCREEN_H/2-5, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "  -space bar.                                ", SCREEN_W/2-180, SCREEN_H/2+10, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "Entering maths answer                        ", SCREEN_W/2-180, SCREEN_H/2+25, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "  -Numpad/number keys to enter their         ", SCREEN_W/2-180, SCREEN_H/2+40, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "   respective digit                          ", SCREEN_W/2-180, SCREEN_H/2+55, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "  -Enter to submit answer and fire turret.   ", SCREEN_W/2-180, SCREEN_H/2+70, C_GREEN, -1);

			} break;
		case 2: {
			textout_ex	(graphicsBuffer, font, "Credits", SCREEN_W/2-180, SCREEN_H/2-110, C_GREEN, -1);
			textout_ex	(graphicsBuffer, font, "Madez by Reuben.", SCREEN_W/2-180, SCREEN_H/2-80, C_GREEN, -1);

			} break;		
		}

	bntMenu->draw(graphicsBuffer);
	bntNext->draw(graphicsBuffer);
	bntPrev->draw(graphicsBuffer);
	}

void stageAboutGame::pause() {} 
void stageAboutGame::resume() {}

void stageAboutGame::drawObjectList(LinkedListNode<ObjectInterface*>* Node, BITMAP* graphicsBuffer) {
	while(Node != NULL) {
		Node->getValue()->draw(graphicsBuffer);
		Node = Node->getNext();
		}
	}

void stageAboutGame::updateObjectList(LinkedListNode<ObjectInterface*>* Node) {
	while(Node != NULL) {
		ObjectInterface* obj = Node->getValue();
		LinkedListNode<ObjectInterface*>* toDelete = NULL;

		if (obj != NULL) {
			bool keep = obj->update(&objListAsteroid, NULL);
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
