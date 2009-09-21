//REUBEN BELL
//objAsteroid.h
//20/11/09

#include "objectInterface.h"

#define MAX_POINT_COUNT 30
#define MIN_POINT_COUNT 5

#define ASTEROID_COLOR makecol(255, 10, 10)

namespace objects {
	#define PI 3.14159265
	class objAsteroid : public ObjectInterface {
		private:
			int pointCount;
			int *pointListX;
			int *pointListY;
			double Xspeed;
			double Yspeed;

			void spawnSmoke(int x, int y, LinkedList<ObjectInterface*> *Particles);

		public:
			double X;
			double Y;
			int Life;
			int radius;

			objAsteroid(int startX, int startY, int approxRadius, int randomness, double xSpeed, double ySpeed);
			~objAsteroid();
			virtual bool update(LinkedList<ObjectInterface*> *Asteroids, LinkedList<ObjectInterface*> *Particles); 
			virtual void draw(BITMAP *graphicsBuffer); //draws the object onto the given bitmap.
		};
	
	}
