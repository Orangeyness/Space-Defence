//REUBEN BELL
//stageTest.h
//20/11/09

#include <allegro.h>
#include <string>

#include "stageInterface.h"
#include "objectInterface.h"
#include "objectBullet.h"
#include "linkedLists.h"

#define C_WHITE makecol(255, 255, 255)
#define C_BLACK makecol(0, 0, 0)
#define C_GREEN makecol(0, 255, 0)
#define C_RED makecol(255, 0, 0)

using namespace objects;
using namespace linkedLists;
using namespace std;

namespace stages {
	#define PI 3.14159265
	#define TARGET_SIZE 32
	#define TURRET_X 60
	#define TURRET_Y SCREEN_H - 60
	#define TURRET_BASE_RADIUS 30
	#define TURRET_BARREL_RADIUS 60

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

			double hudTurretDirection;
			double hudTurretTurnSpeed;

			string currentQuestion;
			int currentAnswer;

			objBullet* myBullet;
			LinkedList<ObjectInterface*> objListAsteroid;
			LinkedList<ObjectInterface*> objListParticle;

			void updateHud();
			void updateObjectList(LinkedListNode<ObjectInterface*>* Node);
			void drawHud(BITMAP *graphicsBuffer);
			void drawTurret(BITMAP *graphicsBuffer);
			void drawObjectList(LinkedListNode<ObjectInterface*>* Node, BITMAP *graphicsBuffer);

		public:
			stageInGame();
			~stageInGame();
			virtual bool update();
			virtual void draw(BITMAP *graphicsBuffer);
		};
	
	}
