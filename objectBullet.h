
#ifndef _OBJ_BULLET_
#define _OBJ_BULLET_

#include "linkedLists.h"
#include "objectInterface.h"

using namespace linkedLists;

namespace objects {
	#define BULLET_COLOR makecol(255, 255, 0)
	#define PI 3.14159265
	class objBullet {
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

		public:
			objBullet(int startX, int startY, int destinationX, int destinationY, double dir, int speed);
			~objBullet();
			bool update(LinkedList<ObjectInterface*>* Asteroids, LinkedList<ObjectInterface*>* Particles); //updates the object.
			void draw(BITMAP *graphicsBuffer); //draws the object onto the given bitmap.
		};
	
	}

#endif
