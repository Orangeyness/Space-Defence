#include <allegro.h>
#include <math.h>
#include <time.h>
#include <string>
#include <sstream>


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
#define TURRET_Y SCREEN_H - 30
#define TURRET_BASE_RADIUS 30
#define TURRET_BARREL_RADIUS 60
#define BASE_Y_COORDINATE SCREEN_H - 60

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

	currentQuestionDifficuilty = 0;
	currentQuestion = "";
	currentAnswer = 0;
	currentUserInput = "";
	currentQuestionFlickerOn = true;
	currentQuestionFlickerNextChange = 0;
	currentQuestionFlickerChangeDuration = 0.2;

	inputSpawnFile.open (INPUT_FILE);
	inputSpawnSpeed = 2;
	inputSpawnNext = clock() + inputSpawnSpeed * CLOCKS_PER_SEC;
	moveSpeed = 1;

	gameLife = 100;
	gameLevel = 0;
	drawLevel = false;
	drawLevelEndTime = 0;
	drawLevelLength = 2;
	gamelevelStartTime = time(NULL);
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
	
	///This here should be put somewhere, integrate into asteroid update or somthing,
	///looping through the asteroids again is quite ineffecient.
	LinkedListNode<ObjectInterface*>* Node = objListAsteroid.getFirst();
	while(Node != NULL) {
		objAsteroid* obj = (objAsteroid*)Node->getValue();

		if (obj->Y > BASE_Y_COORDINATE) {
			gameLife -= obj->Life/2;
			obj->Life = -1;
			} 

		Node = Node->getNext();
		}
	///---

	if (!hudTargetLocked) {
		currentUserInput = "";		
		}
			else
		{
		currentUserInput = updateUserInput(currentUserInput);
		}

	if ((keyboard::isKeyPressed(KEY_ENTER) || keyboard::isKeyPressed(KEY_ENTER_PAD)) && hudTargetLocked && myBullet == NULL) {
		int numericUserInput = 0;		
		istringstream stringConvertion (currentUserInput, istringstream::in);
		stringConvertion >> numericUserInput;

		if (numericUserInput == currentAnswer) {
			myBullet = new objBullet(TURRET_X, TURRET_Y, hudTargetX, hudTargetY, hudTurretDirection, 50);
			hudTargetLocked = false;
			}
				else
			{
			generateQuestion(); 
			}
		currentUserInput = "";
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
	textprintf_ex(graphicsBuffer, font, 10, 90, C_WHITE, -1, "Life: %d!", gameLife);
	textprintf_ex(graphicsBuffer, font, 10, 120, C_WHITE, -1, "Score: %ld!", time(NULL) - gamelevelStartTime);

	drawHud(graphicsBuffer);
	drawTurret(graphicsBuffer);

	if (drawLevel) {
		if (drawLevelEndTime < clock()) drawLevel = false;
		textprintf_centre_ex(graphicsBuffer, font, SCREEN_W/2, SCREEN_H/2, C_GREEN, -1, "LEVEL: %d!", gameLevel);
		}
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
				objListAsteroid.addFirst(new objAsteroid(i * (SCREEN_W / spawnLine.length()), -10, 15 + rand() % 15, 20, ((20-rand()%40)/100)/10, moveSpeed));
				}break;
			case '2': {
				objListAsteroid.addFirst(new objAsteroid(i * (SCREEN_W / spawnLine.length()), -10, 30 + rand() % 15, 20, (20-rand()%40)/10, moveSpeed));
				}break;
			case '3': {
				objListAsteroid.addFirst(new objAsteroid(i * (SCREEN_W / spawnLine.length()), -10, 45 + rand() % 15, 20, (20-rand()%40)/10, moveSpeed));
				}break;
			case '4': {
				objListAsteroid.addFirst(new objAsteroid(i * (SCREEN_W / spawnLine.length()), -10, 60 + rand() % 15, 20, (20-rand()%40)/10, moveSpeed));
				}break;
			case '5': {
				objListAsteroid.addFirst(new objAsteroid(i * (SCREEN_W / spawnLine.length()), -10, 75 + rand() % 15, 20, (20-rand()%40)/10, moveSpeed));
				}break;
			case '6': {
				objListAsteroid.addFirst(new objAsteroid(i * (SCREEN_W / spawnLine.length()), -10, 90 + rand() % 15, 20, (20-rand()%40)/10, moveSpeed));
				}break;
			case '7': {
				objListAsteroid.addFirst(new objAsteroid(i * (SCREEN_W / spawnLine.length()), -10, 105 + rand() % 15, 20, (20-rand()%40)/10, moveSpeed));
				}break;
			case '8': {
				objListAsteroid.addFirst(new objAsteroid(i * (SCREEN_W / spawnLine.length()), -10, 120 + rand() % 15, 20, (20-rand()%40)/10, moveSpeed));
				}break;
			case '9': {
				objListAsteroid.addFirst(new objAsteroid(i * (SCREEN_W / spawnLine.length()), -10, 135 + rand() % 15, 20, (20-rand()%40)/10, moveSpeed));
				}break;


			case 'S': {
				if (i == 0 && spawnLine[i+1] == '-') inputSpawnSpeed += 0.2;
				if (i == 0 && spawnLine[i+1] == '+') inputSpawnSpeed -= 0.2;
				delayNextSpawn = false;
				i = spawnLine.length();
				}break;

			case 'M': {
				if (i == 0 && spawnLine[i+1] == '+') moveSpeed += 0.2;
				if (i == 0 && spawnLine[i+1] == '-') moveSpeed -= 0.2;
				delayNextSpawn = false;
				i = spawnLine.length();
				}break;


			case 'D': {
				if (i == 0 && spawnLine[i+1] == '-') currentQuestionDifficuilty --;
				if (i == 0 && spawnLine[i+1] == '+') currentQuestionDifficuilty ++;
				delayNextSpawn = false;
				i = spawnLine.length();
				}break;

			case 'L': {
				gameLevel ++;
				drawLevel = true;
				drawLevelEndTime = clock() + drawLevelLength * CLOCKS_PER_SEC;
				i = spawnLine.length();
				delayNextSpawn = false;
				}break;
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

	if (keyboard::isKeyPressed(KEY_SPACE)) { 
		hudTargetLocked =!hudTargetLocked; 
		if (hudTargetLocked) generateQuestion(); 
		}

	hudTargetX = (int)(hudTargetX + hudTargetXSpeed);
	hudTargetY = (int)(hudTargetY + hudTargetYSpeed);

	if (hudTargetX < TARGET_SIZE) { hudTargetX = TARGET_SIZE; hudTargetXSpeed = 0; }
	if (hudTargetY < TARGET_SIZE) { hudTargetY = TARGET_SIZE; hudTargetYSpeed = 0; }
	if (hudTargetX > SCREEN_W - TARGET_SIZE) { hudTargetX = SCREEN_W - TARGET_SIZE; hudTargetXSpeed = 0; }
	if (hudTargetY > SCREEN_H - TARGET_SIZE) { hudTargetY = SCREEN_H - TARGET_SIZE; hudTargetYSpeed = 0; }

	hudTurretDirection = atan2(hudTargetX - TURRET_X, -(TURRET_Y - hudTargetY));
	}

string stageInGame::updateUserInput(string Input) {
	int lowerBounds = 27;
	int upperBounds = 37;
	int keypadOffset = 10;
	int asciiNumStart = 48;
	
	for (int i = lowerBounds; i < upperBounds; i++) {
		if (keyboard::isKeyPressed(i) || keyboard::isKeyPressed(i+keypadOffset)) {
			Input += (char)(i - lowerBounds + asciiNumStart);	
			i = upperBounds;		
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

void stageInGame::generateQuestion() {
	int additionChance = 70;
	int subtractionChance = 30;
	int multiplicationChance = 0;
	int divisionChance = 0;
	
	if (currentQuestionDifficuilty == 1) {
		additionChance = 60;
		subtractionChance = 35;
		multiplicationChance = 5;
		}

	if (currentQuestionDifficuilty == 2) {
		additionChance = 55;
		subtractionChance = 40;
		multiplicationChance = 5;
		}

	if (currentQuestionDifficuilty == 3) {
		additionChance = 45;
		subtractionChance = 45;
		multiplicationChance = 10;
		}

	if (currentQuestionDifficuilty == 4) {
		additionChance = 40;
		subtractionChance = 40;
		multiplicationChance = 20;
		}

	if (currentQuestionDifficuilty == 5) {
		additionChance = 40;
		subtractionChance = 40;
		multiplicationChance = 20;
		}

	if (currentQuestionDifficuilty == 6) {
		additionChance = 30;
		subtractionChance = 30;
		multiplicationChance = 30;
		divisionChance = 10;
		}

	if (currentQuestionDifficuilty == 7) {
		additionChance = 25;
		subtractionChance = 30;
		multiplicationChance = 30;
		divisionChance = 15;
		}

	if (currentQuestionDifficuilty == 8) {
		additionChance = 20;
		subtractionChance = 25;
		multiplicationChance = 35;
		divisionChance = 20;
		}

	if (currentQuestionDifficuilty == 9) {
		additionChance = 15;
		subtractionChance = 20;
		multiplicationChance = 40;
		divisionChance = 25;
		}

	if (currentQuestionDifficuilty == 10) {
		additionChance = 10;
		subtractionChance = 10;
		multiplicationChance = 50;
		divisionChance = 30;
		}

	if (currentQuestionDifficuilty == 11) {
		additionChance = 0;
		subtractionChance = 10;
		multiplicationChance = 50;
		divisionChance = 40;
		}

	if (currentQuestionDifficuilty >= 12) {
		additionChance = 0;
		subtractionChance = 0;
		multiplicationChance = 50;
		divisionChance = 50;
		}

	int number = rand()%100;
	if (number < additionChance) {
		//generate addition question.	
		ostringstream strBuilder;
		int numberRange = 10 + 5 * currentQuestionDifficuilty;
		int numberA = 1 + rand()%numberRange;
		int numberB = 1 + rand()%numberRange;

		strBuilder << numberA << " + " << numberB << " = ";		

		currentAnswer = numberA + numberB;	
		currentQuestion = strBuilder.str();
		return;
		}
			else
		{
		number -= additionChance;
		}

	if (number < subtractionChance) {
		//generate subtraction question.
		ostringstream strBuilder;
		int numberRange = 10 + 5 * currentQuestionDifficuilty;
		int numberA = 3 + rand()%numberRange;
		int numberB = 1 + rand()%(numberA-1);

		strBuilder << numberA << " - " << numberB << " = ";		

		currentAnswer = numberA - numberB;	
		currentQuestion = strBuilder.str();
		return;
		}
			else
		{
		number -= subtractionChance;
		}

	if (number < multiplicationChance) {
		//generate multiplication question.		
		ostringstream strBuilder;
		int numberRange = 4 + currentQuestionDifficuilty;
		int numberA = 1 + rand()%numberRange;
		int numberB = 1 + rand()%numberRange;

		strBuilder << numberA << " x " << numberB << " = ";		

		currentAnswer = numberA * numberB;	
		currentQuestion = strBuilder.str();
		return;
		}
			else
		{
		number -= multiplicationChance;
		}

	//Generate devision question.
	ostringstream strBuilder;
	int numberRange = 4 + currentQuestionDifficuilty;
	int numberA = 1 + rand()%numberRange;
	int numberB = 1 + rand()%numberRange;

	strBuilder << numberA * numberB << " / " << numberB << " = ";		

	currentAnswer = numberA;	
	currentQuestion = strBuilder.str();
	return;
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

	line(graphicsBuffer, 0, BASE_Y_COORDINATE, SCREEN_W, BASE_Y_COORDINATE, Col);

	int XX = hudTargetX + TARGET_SIZE * 1.5;
	if (XX > SCREEN_W - TARGET_SIZE) XX = hudTargetX - TARGET_SIZE * 5;
	if (hudTargetLocked) {
		textout_ex(graphicsBuffer, font, currentQuestion.c_str(), XX, hudTargetY + 10, Col, -1);
		if (currentUserInput != "") {
			textout_ex(graphicsBuffer, font, currentUserInput.c_str(), XX + text_length(font,(currentQuestion).c_str()), hudTargetY + 10, Col, -1);		
			}
				else
			{
			if (currentQuestionFlickerOn) {
				textout_ex(graphicsBuffer, font, "?", XX + text_length(font, (currentQuestion).c_str()), hudTargetY + 10, Col, -1);				
				}
			if (clock() > currentQuestionFlickerNextChange) {
				currentQuestionFlickerNextChange = clock() + currentQuestionFlickerChangeDuration * CLOCKS_PER_SEC;
				currentQuestionFlickerOn = ! currentQuestionFlickerOn;				
				}
			}
		}
			else
		{
		textprintf_ex(graphicsBuffer, font, XX, hudTargetY + 10, Col, C_BLACK, "(%d, %d)", hudTargetX, hudTargetY);
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
