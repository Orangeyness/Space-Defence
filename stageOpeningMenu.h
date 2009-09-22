
#ifndef _STAGE_OPENING_MENU
#define _STAGE_OPENING_MENU

#include <allegro.h>
#include "stageInterface.h"
#include "menuButton.h"
#include "objectInterface.h"
#include "linkedLists.h"

using namespace menu;
using namespace objects;
using namespace linkedLists;

namespace stages {
	class stageOpeningMenu : public StageInterface {
		private:
			Button* bntNewGame;
			Button* bntHighScores;
			Button* bntAbout;
			Button* bntOptions;
			Button* bntExit;
			LinkedList<ObjectInterface*> objListAsteroid;

			void updateObjectList(LinkedListNode<ObjectInterface*>* Objects);
			void drawObjectList(LinkedListNode<ObjectInterface*>* Objects, BITMAP *Graphics);
		public:
			stageOpeningMenu();
			~stageOpeningMenu();
			virtual bool update();
			virtual void draw(BITMAP *graphicsBuffer);
			virtual void pause();
			virtual void resume();
	
		};	
	}

#endif
