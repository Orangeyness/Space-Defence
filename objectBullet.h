#ifndef _OBJ_BULLET_
#define _OBJ_BULLET_

#include <time.h>
#include "linkedLists.h"
#include "objectInterface.h"

using namespace linkedLists;

namespace objects {
	#define BULLET_COLOR makecol(255, 255, 0)
	#define BULLET_DAMAGE_RADIUS 70
	#define BULLET_DAMAGE_MIN 40
	#define BULLET_DAMAGE_MAX 100
	#define BULLET_VARIBLE_DAMAGE BULLET_DAMAGE_MAX - BULLET_DAMAGE_MIN
	#define PI 3.14159265
	class objBullet : public ObjectInterface {
		private:
			int X;
			int Y;
			double direction;
			int speed;
			int dX;
			int dY;
			int lX;
			int lY;
			int stage;
			clock_t stageAdvanceTime;

			void updatePosition();
			void dealDamage(LinkedList<ObjectInterface*>* Asteroids);
			void spawnShockWave(LinkedList<ObjectInterface*>* Particles);
			void spawnFire(LinkedList<ObjectInterface*>* Particles);
			void spawnSmoke(LinkedList<ObjectInterface*>* Particles);			
		
		public:
			objBullet(int startX, int startY, int destinationX, int destinationY, double dir, int speed);
			~objBullet();
			virtual bool update(LinkedList<ObjectInterface*>* Asteroids, LinkedList<ObjectInterface*>* Particles); //updates the object.
			virtual void draw(BITMAP *graphicsBuffer); //draws the object onto the given bitmap.
		};
	
	}

#endif
