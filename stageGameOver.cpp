#include <allegro.h>
#include <string>
#include <fstream>
#include <sstream>

#include "stageInterface.h"
#include "stageHighScores.h"
#include "stageOpeningMenu.h"
#include "stageGameOver.h"
#include "stageInGame.h"

#include "objectInterface.h"
#include "objectAsteroid.h"
#include "objectParticle.h"

#include "menuButton.h"
#include "global.h"
#include "inputExtension.h"
#include "linkedLists.h"

#define C_WHITE makecol(255, 255, 255)
#define C_BLACK makecol(0, 0, 0)
#define C_GREEN makecol(0, 255, 0)

#define BASE_Y_COORDINATE SCREEN_H - 60
#define TURRET_X 60
#define TURRET_Y SCREEN_H - 30

using namespace menu;
using namespace objects;
using namespace stages;
using namespace global;
using namespace inputExt;
using namespace linkedLists;

stageGameOver::stageGameOver(LinkedList<ObjectInterface*>* Asteroids, LinkedList<ObjectInterface*>* Particles, int S) {

	score = S;
	bntSubmit = new Button(50, SCREEN_H - 80, 200, 40, "Back to Menu");
	bntSubmit->Selected = true;
	userInput = "";	
	
	highScore = false;

	objListAsteroid = Asteroids;
	objListParticle = Particles;

	int ExplosionCount = 10 + rand() % 50;
	for (int i = 0; i <ExplosionCount; i++) {
		spawnExplosion(Particles, rand() % SCREEN_W, BASE_Y_COORDINATE + rand() % (SCREEN_H - BASE_Y_COORDINATE));
		}
	spawnExplosion(Particles, TURRET_X, TURRET_Y);

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

	if (score > highScores[HIGH_SCORE_COUNT-1]) {
		highScore = true;		
		bntSubmit->Value = "Submit High Score!";
		}
	}

stageGameOver::~stageGameOver() {
	delete bntSubmit;

	while(objListAsteroid->nodeCount > 0) {
		delete objListAsteroid->getFirstValue();	
		objListAsteroid->getFirst()->remove();
		}

	while(objListParticle->nodeCount > 0) {
		delete objListParticle->getFirstValue();	
		objListParticle->getFirst()->remove();
		}

	delete objListAsteroid;
	delete objListParticle;
	}

bool stageGameOver::update() {

	userInput = updateUserInput(userInput);

	bntSubmit->update();

	if (rand() % 100 == 50) {
		objListAsteroid->addLast(new objAsteroid(40 + rand() % SCREEN_W - 80, -100, 10 + rand() % 40, 40, (20-rand()%40)/10, 1 + (rand() % 20)/10));
		}

	updateObjectList(objListAsteroid->getFirst());
	updateObjectList(objListParticle->getFirst());

	if (((keyboard::isKeyPressed(KEY_ENTER) || keyboard::isKeyPressed(KEY_ENTER_PAD)) && bntSubmit->Selected) || keyboard::isKeyPressed(KEY_ESC)) {
		if (highScore) {
			bool found = false;
			int tmp = 0;
			string tmp2 = "";
			for (int i = 0; i < HIGH_SCORE_COUNT; i++) {
				if (!found) {				
					if (score > highScores[i]) {
						found = true;
						tmp = highScores[i];
						tmp2 = highScoreNames[i];
						highScoreNames[i] = userInput;
						highScores[i] = score;						
						}	
					}
						else
					{
					int temper = highScores[i];
					string evenWorstNamingTechnique = highScoreNames[i];
					highScores[i] = tmp;
					highScoreNames[i] = tmp2;
					
					tmp = temper;
					tmp2 = evenWorstNamingTechnique;
					}			
				}
	
			fstream highScoreData (HIGH_SCORE_FILE, ios::out);
			for (int i = 0; i < HIGH_SCORE_COUNT; i++) {
				highScoreData << highScoreNames[i] << endl << highScores[i] << endl;
				}
			highScoreData.close();

			globalData::gameCurrentStage = new stageHighScores();			
			}
				else
			{
			globalData::gameCurrentStage = new stageOpeningMenu();
			}
				
		return STAGE_OVER;		
		}

	return STAGE_RUNNING;	
	}

void stageGameOver::draw(BITMAP *graphicsBuffer) {
	clear_to_color(graphicsBuffer, C_BLACK);

	drawObjectList(objListAsteroid->getFirst(), graphicsBuffer);
	drawObjectList(objListParticle->getFirst(), graphicsBuffer);

	if (globalData::gameResolutionX > 1000) { 
		int txtHeight = text_height(font);
		int txtWidth = text_length(font, "                                                                                                           ");
		int xx = SCREEN_W/2 - txtWidth/2;
		int yy = 100;
		textout_ex(graphicsBuffer, font, "  _______      ___      .___  ___.  _______      ______   ____    ____  _______ .______      ", xx, yy + txtHeight * 0, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, " /  _____|    /   \\     |   \\/   | |   ____|    /  __  \\  \\   \\  /   / |   ____||   _  \\     ", xx, yy + txtHeight * 1, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "|  |  __     /  ^  \\    |  \\  /  | |  |__      |  |  |  |  \\   \\/   /  |  |__   |  |_)  |    ", xx, yy + txtHeight * 2, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "|  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|     |  |  |  |   \\      /   |   __|  |      /     ", xx, yy + txtHeight * 3, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "|  |__| |  /  _____  \\  |  |  |  | |  |____    |  `--'  |    \\    /    |  |____ |  |\\  \\----.", xx, yy + txtHeight * 4, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, " \\______| /__/     \\__\\ |__|  |__| |_______|    \\______/      \\__/     |_______|| _| `._____|", xx, yy + txtHeight * 5, C_GREEN, -1);
		}
			else
		{
		int txtHeight = text_height(font);
		int txtWidth = text_length(font, "                                                     ");
		int xx = SCREEN_W/2 - txtWidth/2;
		int yy = 80;
		textout_ex(graphicsBuffer, font, "  _____                         ____                 ", xx, yy + txtHeight * 0, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, " / ____|                       / __ \\                ", xx, yy + txtHeight * 1, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "| |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ ", xx, yy + txtHeight * 2, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "| | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__|", xx, yy + txtHeight * 3, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, "| |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |   ", xx, yy + txtHeight * 4, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, " \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|   ", xx, yy + txtHeight * 5, C_GREEN, -1);
		}

	if (highScore) {
		textout_centre_ex(graphicsBuffer, font, "You got a high score!", SCREEN_W/2, SCREEN_H/2-40, C_GREEN, -1);
		textout_right_ex(graphicsBuffer, font, "Enter your name:  ", SCREEN_W/2, SCREEN_H/2, C_GREEN, -1);
		textout_ex(graphicsBuffer, font, userInput.c_str(), SCREEN_W/2, SCREEN_H/2, C_GREEN, -1);
		}	
			else
		{
		textprintf_centre_ex(graphicsBuffer, font, SCREEN_W/2, SCREEN_H/2-40, C_GREEN, -1, "You scored: %d", score);
		}

	bntSubmit->draw(graphicsBuffer);
	}

void stageGameOver::resume() {}
void stageGameOver::pause() {}

string stageGameOver::updateUserInput(string Input) {
	for (int i = 0; i < 37; i++) {
		if (keyboard::isKeyPressed(i)) {
			int asciiNumStart = 96;
			if (key[KEY_LSHIFT] || key[KEY_RSHIFT]) asciiNumStart = 64;
			if (i > 26) asciiNumStart = 21;
			Input += (char)(i + asciiNumStart);	
			i = 37;		
			}
		}

	if (	keyboard::isKeyPressed(KEY_DEL) 			|| 
			keyboard::isKeyPressed(KEY_BACKSPACE) 	|| 
			keyboard::isKeyPressed(KEY_MINUS_PAD) 	||
			keyboard::isKeyPressed(KEY_DEL_PAD)
		) {
		if (Input.length() > 0) {
			Input = Input.substr(0, Input.length()-1);
			}
		}

	return Input;
	}

void stageGameOver::drawObjectList(LinkedListNode<ObjectInterface*>* Node, BITMAP* graphicsBuffer) {
	while(Node != NULL) {
		Node->getValue()->draw(graphicsBuffer);
		Node = Node->getNext();
		}
	}

void stageGameOver::updateObjectList(LinkedListNode<ObjectInterface*>* Node) {
	while(Node != NULL) {
		ObjectInterface* obj = Node->getValue();
		LinkedListNode<ObjectInterface*>* toDelete = NULL;

		if (obj != NULL) {
			bool keep = obj->update(objListAsteroid, NULL);
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

void stageGameOver::spawnExplosion(LinkedList<ObjectInterface*>* Particles, int X, int Y) {
	spawnFire(Particles, X, Y);
	spawnSmoke(Particles, X, Y);
	}

void stageGameOver::spawnSmoke(LinkedList<ObjectInterface*>* Particles, int X, int Y) {
	int cloudCount = 20 + rand() % 20;
	for (int i = 0; i < cloudCount; i++) {
		double xSpeed = (-(rand() % 30) + rand() % 30)/10;
		double ySpeed = (-(rand() % 30) + rand() % 30)/10;				
		int startColor = makecol(200 + (rand() %10), 100 + (rand() %10), 100 + (rand() %10));
		int endColor = makecol(50 - (rand() %5), 50 - (rand() %5), 50 - (rand() %5));
		int startSize = 1 + rand() % 10;
		int endSize = 1 + rand() % 20;
		double lifeSpan = 0.7 + (rand() % 40)/100;
		
		Particles->addFirst(new objParticle(X + rand()%5 - rand()%5, Y + rand()%5 - rand()%5, xSpeed, ySpeed, startSize, endSize, startColor, endColor, lifeSpan));
		}
	}

void stageGameOver::spawnFire(LinkedList<ObjectInterface*>* Particles, int X, int Y) {
	int fireCount = rand() % 100;
	for (int i = 0; i < fireCount; i++) {
		int xSpeed = 1 + rand()%11;
		int ySpeed = 1 + rand()%11;
		
		if (rand() % 2 == 1) xSpeed =- xSpeed;
		if (rand() % 2 == 1) ySpeed =- ySpeed;
		
		int startColor = makecol(255 - rand()%100, rand()%60, rand()%60);
		int endColor = makecol(10, 10, 10);
		int startSize = 2 + rand()%3;
		int endSize = 1;
		double lifeSpan = 1 + (rand()%70)/100;

		Particles->addLast(new objParticle(X, Y, xSpeed, ySpeed, startSize, endSize, startColor, endColor, lifeSpan));
		}
	}
