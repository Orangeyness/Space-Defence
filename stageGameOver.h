
#ifndef _STAGE_GAME_OVER_
#define _STAGE_GAME_OVER_

#include <allegro.h>
#include <string>

#include "stageInterface.h"
#include "menuButton.h"
#include "objectInterface.h"
#include "linkedLists.h"

using namespace menu;
using namespace objects;
using namespace linkedLists;

namespace stages {
	#define HIGH_SCORE_COUNT 9
	#define HIGH_SCORE_FILE "highScores"
	class stageGameOver : public StageInterface {
		private:
			Button* bntSubmit;
			int score;
			bool highScore;
			string userInput;
			
			string highScoreNames[HIGH_SCORE_COUNT];
			int highScores[HIGH_SCORE_COUNT];

			LinkedList<ObjectInterface*>* objListAsteroid;
			LinkedList<ObjectInterface*>* objListParticle;

			string updateUserInput(string Orig);
			void updateObjectList(LinkedListNode<ObjectInterface*>* Objects);
			void drawObjectList(LinkedListNode<ObjectInterface*>* Objects, BITMAP *Graphics);
			void spawnExplosion(LinkedList<ObjectInterface*>* Particles, int x, int y);
			void spawnSmoke(LinkedList<ObjectInterface*>* Particles, int X, int Y);
			void spawnFire(LinkedList<ObjectInterface*>* Particles, int X, int Y);
		public:
			stageGameOver(LinkedList<ObjectInterface*>* Asteroids, LinkedList<ObjectInterface*>* Particles, int Score);
			~stageGameOver();
			virtual bool update();
			virtual void draw(BITMAP *graphicsBuffer);
			virtual void pause();
			virtual void resume();
	
		};	
	}

#endif
