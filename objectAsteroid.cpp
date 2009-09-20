#include <allegro.h>
#include <math.h>

#include "objectAsteroid.h"

using namespace objects;

objAsteroid::objAsteroid(int startX, int startY, int approxRadius, int randomness, int xSpeed, int ySpeed) {
	X = startX;
	Y = startY;
	radius = approxRadius;

	pointCount = MIN_POINT_COUNT + rand() % (MAX_POINT_COUNT - MIN_POINT_COUNT);
	pointListX = new int[pointCount];
	pointListY = new int[pointCount];
		
	for (int i = 0; i < pointCount; i++) {
		pointListX[i] = (int)(radius * sin(2 * PI * ((double)i / (double)pointCount)) * ((100-randomness) + rand() % randomness)/100);
		pointListY[i] = (int)(radius * cos(2 * PI * ((double)i / (double)pointCount)) * ((100-randomness) + rand() % randomness)/100); 
		}

	radius = (int)(radius * (1-randomness/2));

	Xspeed = xSpeed;
	Yspeed = ySpeed;
	}

objAsteroid::~objAsteroid() {
	delete pointListX;
	delete pointListY;
	}

bool objAsteroid::update() {
	X += Xspeed;
	Y += Yspeed;

	return true;
	}

void objAsteroid::draw(BITMAP *G) {
	for (int i = 1; i < pointCount; i++) {
		line(G, X + pointListX[i-1], Y + pointListY[i-1], X + pointListX[i], Y + pointListY[i], ASTEROID_COLOR);
		}
	line(G, X + pointListX[0], Y + pointListY[0], X + pointListX[pointCount-1], Y + pointListY[pointCount-1], ASTEROID_COLOR);
	}
