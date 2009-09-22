#include <allegro.h>
#include <string>
#include <fstream>
#include <sstream>

#include "stageInterface.h"
#include "stageHighScores.h"
#include "stageOpeningMenu.h"
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

stageHighScores::stageHighScores() {

	bntBack = new Button(50, SCREEN_H - 80, 200, 40, "Back to Menu");
	bntBack->Selected = true;

	for (int i = 0; i < HIGH_SCORE_COUNT; i++) {
		highScoreNames[i] = "";
		highScores[i] = 0;		
		}

	fstream highScoreData;
	highScoreData.open(HIGH_SCORE_FILE);
	if (!highScoreData.is_open()) {
		allegro_message("High score file could not be found");
		return;		
		}


	for (int i = 0; i < HIGH_SCORE_COUNT && !highScoreData.eof(); i ++) {
		string tmp;
		
		getline(highScoreData, highScoreNames[i]);
		getline(highScoreData, tmp);

		istringstream intBuilder(tmp);
		intBuilder >> highScores[i];
		}
	
	highScoreData.close();
	}


stageHighScores::~stageHighScores() {
	delete bntBack;

	while(objListAsteroid.nodeCount > 0) {
		delete objListAsteroid.getFirstValue();	
		objListAsteroid.getFirst()->remove();
		}
	}

bool stageHighScores::update() {

	bntBack->update();

	if (rand() % 100 == 50) {
		objListAsteroid.addLast(new objAsteroid(40 + rand() % SCREEN_W - 80, -100, 10 + rand() % 40, 40, (20-rand()%40)/10, 1 + (rand() % 20)/10));
		}

	updateObjectList(objListAsteroid.getFirst());

	if (((keyboard::isKeyPressed(KEY_ENTER) || keyboard::isKeyPressed(KEY_ENTER_PAD)) && bntBack->Selected) || keyboard::isKeyPressed(KEY_ESC)) {
		globalData::gameCurrentStage = new stageOpeningMenu();
		return STAGE_OVER;		
		}

	return STAGE_RUNNING;	
	}

void stageHighScores::draw(BITMAP *graphicsBuffer) {
	clear_to_color(graphicsBuffer, C_BLACK);

	drawObjectList(objListAsteroid.getFirst(), graphicsBuffer);

	if (globalData::gameResolutionX > 1000) { 
		int txtHeight = text_height(font);
		int txtWidth = text_length(font, "                                                                                                           ");
		int xx = SCREEN_W/2 - txtWidth/2;
		int yy = 100;
		textout_ex(graphicsBuffer, font, " __    __   __    _______  __    __          _______.  ______   ______   .______       _______     _______.", xx, yy + txtHeight * 0, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "|  |  |  | |  |  /  _____||  |  |  |        /       | /      | /  __  \\  |   _  \\     |   ____|   /       |", xx, yy + txtHeight * 1, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "|  |__|  | |  | |  |  __  |  |__|  |       |   (----`|  ,----'|  |  |  | |  |_)  |    |  |__     |   (----`", xx, yy + txtHeight * 2, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "|   __   | |  | |  | |_ | |   __   |        \\   \\    |  |     |  |  |  | |      /     |   __|     \\   \\    ", xx, yy + txtHeight * 3, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "|  |  |  | |  | |  |__| | |  |  |  |    .----)   |   |  `----.|  `--'  | |  |\\  \\----.|  |____.----)   |   ", xx, yy + txtHeight * 4, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "|__|  |__| |__|  \\______| |__|  |__|    |_______/     \\______| \\______/  | _| `._____||_______|_______/    ", xx, yy + txtHeight * 5, C_GREEN, -1);
		}
			else
		{
		int txtHeight = text_height(font);
		int txtWidth = text_length(font, "                                                       ");
		int xx = SCREEN_W/2 - txtWidth/2;
		int yy = 80;
		textout_ex(graphicsBuffer, font, " _    _ _       _        _____                         ", xx, yy + txtHeight * 0, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "| |  | (_)     | |      / ____|                        ", xx, yy + txtHeight * 1, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "| |__| |_  __ _| |__   | (___   ___ ___  _ __ ___  ___ ", xx, yy + txtHeight * 2, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "|  __  | |/ _` | '_ \\   \\___ \\ / __/ _ \\| '__/ _ \\/ __|", xx, yy + txtHeight * 3, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "| |  | | | (_| | | | |  ____) | (_| (_) | | |  __/\\__ \\", xx, yy + txtHeight * 4, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "|_|  |_|_|\\__, |_| |_| |_____/ \\___\\___/|_|  \\___||___/", xx, yy + txtHeight * 5, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "		     __/ |                                        ", xx, yy + txtHeight * 6, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "		    |___/                                         ", xx, yy + txtHeight * 7, C_GREEN, -1);
		}

	int x1 = 100;
	int x2 = SCREEN_W - 100;
	int ys = 250;
	int yinc = 25;
	for(int i = 0; i < HIGH_SCORE_COUNT; i++) {
		textout_ex(graphicsBuffer, font, highScoreNames[i].c_str(), x1, ys + yinc*i, C_GREEN, -1);
		textprintf_right_ex(graphicsBuffer, font, x2, ys + yinc*i, C_GREEN, -1, "%d", highScores[i]);
		line(graphicsBuffer, x1, ys + yinc * (i + 1) - 15, x2, ys + yinc * (i + 1) - 15, C_GREEN);
		}

	bntBack->draw(graphicsBuffer);
	}

void stageHighScores::resume() {}
void stageHighScores::pause() {}

void stageHighScores::drawObjectList(LinkedListNode<ObjectInterface*>* Node, BITMAP* graphicsBuffer) {
	while(Node != NULL) {
		Node->getValue()->draw(graphicsBuffer);
		Node = Node->getNext();
		}
	}

void stageHighScores::updateObjectList(LinkedListNode<ObjectInterface*>* Node) {
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
