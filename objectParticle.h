//REUBEN BELL
//objAsteroid.h
//20/11/09

#include <time.h>
#include "objectInterface.h"

namespace objects {
	#define COLOR_INC 128- 
	#define FPS_TARGET 30
	class objParticle : public ObjectInterface {
		private:
			double X;
			double Y;
			double Xspeed;
			double Yspeed;
			double sRadius;
			double radius;
			double dRadius;
			int color;
			int sColor;
			int dColor;
			int life;
			int updateCount;
			int updateNum;
			clock_t birth;

		public:
			objParticle(int startX, 
							int startY, 
							double xSpeed, 
							double ySpeed, 
							int startRadius, 
							int endRadius,
							int startColor, 
							int endColor,
							double lifeSpan);
			~objParticle();
			virtual bool update(); //updates the object.
			virtual void draw(BITMAP *graphicsBuffer); //draws the object onto the given bitmap.
		};
	
	}
