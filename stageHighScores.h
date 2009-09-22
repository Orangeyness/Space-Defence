
#ifndef _STAGE_HIGH_SCORES_
#define _STAGE_HIGH_SCORES_

#include <allegro.h>
#include <string>

#include "stageInterface.h"
#include "menuButton.h"
#include "objectInterface.h"
#include "linkedLists.h"

using namespace std;
using namespace menu;
using namespace objects;
using namespace linkedLists;

namespace stages {
	#define HIGH_SCORE_COUNT 9
	#define HIGH_SCORE_FILE "highScores"
	class stageHighScores : public StageInterface {
		private:
			Button* bntBack;
			LinkedList<ObjectInterface*> objListAsteroid;

			string highScoreNames[HIGH_SCORE_COUNT];
			int highScores[HIGH_SCORE_COUNT];

			void updateObjectList(LinkedListNode<ObjectInterface*>* Objects);
			void drawObjectList(LinkedListNode<ObjectInterface*>* Objects, BITMAP *Graphics);
		public:
			stageHighScores();
			~stageHighScores();
			virtual bool update();
			virtual void draw(BITMAP *graphicsBuffer);
			virtual void pause();
			virtual void resume();
	
		};	
	}

#endif
