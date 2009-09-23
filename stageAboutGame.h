
#ifndef _STAGE_ABOUT_GAME_
#define _STAGE_ABOUT_GAME_

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
	#define PAGE_COUNT 3
	class stageAboutGame : public StageInterface {
		private:
			int page;
			Button* bntMenu;
			Button* bntNext;
			Button* bntPrev;
			
			LinkedList<ObjectInterface*> objListAsteroid;
	
			void updateObjectList(LinkedListNode<ObjectInterface*>* Objects);
			void drawObjectList(LinkedListNode<ObjectInterface*>* Objects, BITMAP *Graphics);
		public:
			stageAboutGame();
			~stageAboutGame();
			virtual bool update();
			virtual void draw(BITMAP *graphicsBuffer);
			virtual void pause();
			virtual void resume();
	
		};	
	}

#endif
