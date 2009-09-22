#include <allegro.h>
#include <math.h>

#include "objectAsteroid.h"
#include "objectParticle.h"

using namespace objects;

objAsteroid::objAsteroid(int startX, int startY, int approxRadius, int randomness, double xSpeed, double ySpeed) {
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

	radius = (int)(radius * (1-randomness/200));
	
	Life = radius * 2;

	Xspeed = xSpeed;
	Yspeed = ySpeed;

	int time = SCREEN_H/Yspeed;
	int Count = 0;
	while ((X + Xspeed * time < 0 || X + Xspeed * time > SCREEN_W) && Count < 100) {
		Xspeed -= Xspeed/4; 
		Count ++;
		}
	}

objAsteroid::~objAsteroid() {
	delete pointListX;
	delete pointListY;
	}

bool objAsteroid::update(LinkedList<ObjectInterface*> *Asteroids, LinkedList<ObjectInterface*> *Particles) {
	X += Xspeed;
	Y += Yspeed;

	if (Y > SCREEN_H + 100) Life = 0;

	if (Life < 0) {
		for (int i = 0; i < rand() % 50; i++) {
			if (Particles != NULL) spawnSmoke((int)X + rand()%radius - rand()%radius, (int)Y + rand()%radius - rand()%radius, Particles);
			}
		
		return false;
		}

	return true;
	}

void objAsteroid::draw(BITMAP *G) {
	for (int i = 1; i < pointCount; i++) {
		line(G, (int)X + pointListX[i-1], (int)Y + pointListY[i-1], (int)X + pointListX[i], (int)Y + pointListY[i], ASTEROID_COLOR);
		}
	line(G, (int)X + pointListX[0], (int)Y + pointListY[0], (int)X + pointListX[pointCount-1], (int)Y + pointListY[pointCount-1], ASTEROID_COLOR);
	}

void objAsteroid::spawnSmoke(int X, int Y, LinkedList<ObjectInterface*>* Particles) {
	int cloudCount = 20 + rand() % 20;
	for (int i = 0; i < cloudCount; i++) {
		double xSpeed = (-(rand() % 30) + rand() % 30)/10;
		double ySpeed = (-(rand() % 30) + rand() % 30)/10;				
		int startColor = makecol(200 + (rand() %10), 100 + (rand() %10), 100 + (rand() %10));
		int endColor = makecol(50 - (rand() %5), 50 - (rand() %5), 50 - (rand() %5));
		int startSize = 1 + rand() % 10;
		int endSize = 1 + rand() % 20;
		double lifeSpan = 0.7 + (rand() % 40)/100;
		
		Particles->addFirst(new objParticle(X + rand()%5 - rand()%5, Y + rand()%5 - rand()%5, xSpeed, ySpeed, startSize, endSize, startColor, endColor, lifeSpan));
		}
	}
