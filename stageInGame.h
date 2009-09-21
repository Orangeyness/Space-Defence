//REUBEN BELL
//stageTest.h
//20/11/09

#include <allegro.h>
#include <string>
#include <fstream>

#include "stageInterface.h"
#include "objectInterface.h"
#include "objectBullet.h"
#include "linkedLists.h"

using namespace objects;
using namespace linkedLists;
using namespace std;

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

			double hudTurretDirection;

			ifstream inputSpawnFile;
			double inputSpawnSpeed;
			clock_t inputSpawnNext;
			double moveSpeed;
			
			int gameLife;
			int gameLevel;
			bool drawLevel;
			clock_t drawLevelEndTime;
			float drawLevelLength;
			clock_t gamelevelStartTime;

			int currentQuestionDifficuilty;
			string currentQuestion;
			string currentUserInput;
			int currentAnswer;
			bool currentQuestionFlickerOn;
			clock_t currentQuestionFlickerNextChange;
			double currentQuestionFlickerChangeDuration;

			objBullet* myBullet;
			LinkedList<ObjectInterface*> objListAsteroid;
			LinkedList<ObjectInterface*> objListParticle;

			bool loadObjects();
			string updateUserInput(string Input);
			void generateQuestion();
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
