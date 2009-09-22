#include <allegro.h>

#include "stageInterface.h"
#include "stageOpeningMenu.h"
#include "stageOptionsMenu.h"
#include "stageInGame.h"

#include "objectInterface.h"
#include "objectAsteroid.h"

#include "menuButton.h"
#include "global.h"
#include "inputExtension.h"
#include "linkedLists.h"

#define C_WHITE makecol(255, 255, 255)
#define C_BLACK makecol(0, 0, 0)
#define C_GREEN makecol(0, 255, 0)

using namespace menu;
using namespace objects;
using namespace stages;
using namespace global;
using namespace inputExt;
using namespace linkedLists;

stageOpeningMenu::stageOpeningMenu() {
	int xx = SCREEN_W/2 - SCREEN_W/6;
	int width = SCREEN_W/3;
	int yy = SCREEN_H/2 - 40;
	int height = 35;
	int yborder = 10;

	bntNewGame = new Button(xx, yy, width, height, "Start Game");
	bntHighScores = new Button(xx, yy + (height + yborder) * 1, width, height, "View Highscores");
	bntAbout = new Button(xx, yy + (height + yborder) * 2, width, height, "About The Game");
	bntOptions = new Button(xx, yy + (height + yborder) * 3, width, height, "Game Options");
	bntExit = new Button(xx, yy + (height + yborder) * 4, width, height, "Exit");
	
	bntNewGame->Selected = true;
	bntNewGame->Next = bntHighScores;
	bntNewGame->Prev = bntExit;
	
	bntHighScores->Next = bntAbout;
	bntHighScores->Prev = bntNewGame;
	
	bntAbout->Next = bntOptions;
	bntAbout->Prev = bntHighScores;

	bntOptions->Next = bntExit;
	bntOptions->Prev = bntAbout;

	bntExit->Next = bntNewGame;
	bntExit->Prev = bntOptions;
		
	}

stageOpeningMenu::~stageOpeningMenu() {
	delete bntNewGame;
	delete bntHighScores;
	delete bntAbout;
	delete bntOptions;
	delete bntExit;

	while(objListAsteroid.nodeCount > 0) {
		delete objListAsteroid.getFirstValue();	
		objListAsteroid.getFirst()->remove();
		}
	}

bool stageOpeningMenu::update() {
	bntNewGame->update();
	bntHighScores->update();
	bntAbout->update();
	bntOptions->update();
	bntExit->update();

	if (rand() % 100 == 50) {
		objListAsteroid.addLast(new objAsteroid(40 + rand() % SCREEN_W - 80, -100, 10 + rand() % 40, 40, (20-rand()%40)/10, 1 + (rand() % 20)/10));
		}

	updateObjectList(objListAsteroid.getFirst());

	if (((keyboard::isKeyPressed(KEY_ENTER) || keyboard::isKeyPressed(KEY_ENTER_PAD)) && bntNewGame->Selected)) {
		globalData::gameCurrentStage = new stageInGame();
		return STAGE_OVER;		
		}

	if (((keyboard::isKeyPressed(KEY_ENTER) || keyboard::isKeyPressed(KEY_ENTER_PAD)) && bntOptions->Selected)) {
		BITMAP *Preview = create_bitmap(SCREEN_W, SCREEN_H);
		draw(Preview);
		
		globalData::gameCurrentStage = new stageOptionsMenu(this, Preview);
		return STAGE_RUNNING;		
		}

	if (((keyboard::isKeyPressed(KEY_ENTER) || keyboard::isKeyPressed(KEY_ENTER_PAD)) && bntExit->Selected) || keyboard::isKeyPressed(KEY_ESC)) {
		return STAGE_OVER;		
		}

	return STAGE_RUNNING;	
	}

void stageOpeningMenu::draw(BITMAP *graphicsBuffer) {
	clear_to_color(graphicsBuffer, C_BLACK);

	drawObjectList(objListAsteroid.getFirst(), graphicsBuffer);

	if (globalData::gameResolutionX > 1000) { 
		int txtHeight = text_height(font);
		int txtWidth = text_length(font, "                                                                                                                        ");
		int xx = SCREEN_W/2 - txtWidth/2;
		int yy = SCREEN_H/2 - 140;
		textout_ex(graphicsBuffer, font, "     _______..______      ___       ______  _______     _______   _______  _______  _______ .__   __.   ______  _______ ", xx, yy + txtHeight * 0, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "    /       ||   _  \\    /   \\     /      ||   ____|   |       \\ |   ____||   ____||   ____||  \\ |  |  /      ||   ____|", xx, yy + txtHeight * 1, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "   |   (----`|  |_)  |  /  ^  \\   |  ,----'|  |__      |  .--.  ||  |__   |  |__   |  |__   |   \\|  | |  ,----'|  |__   ", xx, yy + txtHeight * 2, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "    \\   \\    |   ___/  /  /_\\  \\  |  |     |   __|     |  |  |  ||   __|  |   __|  |   __|  |  . `  | |  |     |   __|  ", xx, yy + txtHeight * 3, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, ".----)   |   |  |     /  _____  \\ |  `----.|  |____    |  '--'  ||  |____ |  |     |  |____ |  |\\   | |  `----.|  |____ ", xx, yy + txtHeight * 4, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "|_______/    | _|    /__/     \\__\\ \\______||_______|   |_______/ |_______||__|     |_______||__| \\__|  \\______||_______|", xx, yy + txtHeight * 5, C_GREEN, -1);
		}
			else
		{
		int txtHeight = text_height(font);
		int txtWidth = text_length(font, "                                                                  ");
		int xx = SCREEN_W/2 - txtWidth/2;
		int yy = SCREEN_H/2 - 140;
		textout_ex(graphicsBuffer, font, "  _____                        _____        __                    ", xx, yy + txtHeight * 0, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, " / ____|                      |  __ \\      / _|                   ", xx, yy + txtHeight * 1, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "| (___  _ __   __ _  ___ ___  | |  | | ___| |_ ___ _ __   ___ ___ ", xx, yy + txtHeight * 2, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, " \\___ \\| '_ \\ / _` |/ __/ _ \\ | |  | |/ _ \\  _/ _ \\ '_ \\ / __/ _ \\", xx, yy + txtHeight * 3, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, " ____) | |_) | (_| | (_|  __/ | |__| |  __/ ||  __/ | | | (_|  __/", xx, yy + txtHeight * 4, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "|_____/| .__/ \\__,_|\\___\\___| |_____/ \\___|_| \\___|_| |_|\\___\\___|", xx, yy + txtHeight * 5, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "       | |                                                        ", xx, yy + txtHeight * 6, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "       |_|                                                        ", xx, yy + txtHeight * 7, C_GREEN, -1);
		}

	bntNewGame->draw(graphicsBuffer);
	bntHighScores->draw(graphicsBuffer);
	bntAbout->draw(graphicsBuffer);
	bntOptions->draw(graphicsBuffer);
	bntExit->draw(graphicsBuffer);
	}

void stageOpeningMenu::resume() {
	delete bntNewGame;
	delete bntHighScores;
	delete bntAbout;
	delete bntOptions;
	delete bntExit;

	int xx = SCREEN_W/2 - SCREEN_W/6;
	int width = SCREEN_W/3;
	int yy = SCREEN_H/2 - 40;
	int height = 35;
	int yborder = 10;

	bntNewGame = new Button(xx, yy, width, height, "Start Game");
	bntHighScores = new Button(xx, yy + (height + yborder) * 1, width, height, "View Highscores");
	bntAbout = new Button(xx, yy + (height + yborder) * 2, width, height, "About The Game");
	bntOptions = new Button(xx, yy + (height + yborder) * 3, width, height, "Game Options");
	bntExit = new Button(xx, yy + (height + yborder) * 4, width, height, "Exit");
	
	bntNewGame->Selected = true;
	bntNewGame->Next = bntHighScores;
	bntNewGame->Prev = bntExit;
	
	bntHighScores->Next = bntAbout;
	bntHighScores->Prev = bntNewGame;
	
	bntAbout->Next = bntOptions;
	bntAbout->Prev = bntHighScores;

	bntOptions->Next = bntExit;
	bntOptions->Prev = bntAbout;

	bntExit->Next = bntNewGame;
	bntExit->Prev = bntOptions;	
	}
void stageOpeningMenu::pause() {}

void stageOpeningMenu::drawObjectList(LinkedListNode<ObjectInterface*>* Node, BITMAP* graphicsBuffer) {
	while(Node != NULL) {
		Node->getValue()->draw(graphicsBuffer);
		Node = Node->getNext();
		}
	}

void stageOpeningMenu::updateObjectList(LinkedListNode<ObjectInterface*>* Node) {
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
