
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

			LinkedList<ObjectInterface*> objListAsteroid;

			string updateUserInput(string Orig);
			void updateObjectList(LinkedListNode<ObjectInterface*>* Objects);
			void drawObjectList(LinkedListNode<ObjectInterface*>* Objects, BITMAP *Graphics);
		public:
			stageGameOver(int Score);
			~stageGameOver();
			virtual bool update();
			virtual void draw(BITMAP *graphicsBuffer);
			virtual void pause();
			virtual void resume();
	
		};	
	}

#endif
