//REUBEN BELL
//stageTest.h
//20/11/09

#include <allegro.h>
#include "stageInterface.h"

#define C_WHITE makecol(255, 255, 255)
#define C_BLACK makecol(0, 0, 0)
#define C_GREEN makecol(0, 255, 0)
#define C_RED makecol(255, 0, 0)

namespace stages {

	class stageInGame : public StageInterface {
		private:
			int hudTargetX;
			int hudTargetY;
			double hudTargetXSpeed;
			double hudTargetYSpeed;
			double hudTargetFriction; 
			double hudTargetAcceleration;
			double hudTargetMaxSpeed;
			bool hudTargetLocked;

			void updateHud();
			void drawHud(BITMAP *graphicsBuffer);

		public:
			stageInGame();
			~stageInGame();
			virtual bool update();
			virtual void draw(BITMAP *graphicsBuffer);
		};
	
	}
