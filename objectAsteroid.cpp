#include <allegro.h>
#include <math.h>

#include "objectAsteroid.h"
#include "objectParticle.h"

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

	radius = (int)(radius * (1-randomness/200));
	
	Life = radius * 2;

	Xspeed = xSpeed;
	Yspeed = ySpeed;
	}

objAsteroid::~objAsteroid() {
	delete pointListX;
	delete pointListY;
	}

bool objAsteroid::update(LinkedList<ObjectInterface*> *Asteroids, LinkedList<ObjectInterface*> *Particles) {
	X += Xspeed;
	Y += Yspeed;

	if (Life < 0) {
		for (int i = 0; i < rand() % 50; i++) {
			spawnSmoke(X + rand()%radius - rand()%radius, Y + rand()%radius - rand()%radius, Particles);
			}
		
		return false;
		}

	return true;
	}

void objAsteroid::draw(BITMAP *G) {
	for (int i = 1; i < pointCount; i++) {
		line(G, X + pointListX[i-1], Y + pointListY[i-1], X + pointListX[i], Y + pointListY[i], ASTEROID_COLOR);
		}
	line(G, X + pointListX[0], Y + pointListY[0], X + pointListX[pointCount-1], Y + pointListY[pointCount-1], ASTEROID_COLOR);

	textprintf_ex(G, font, X + 30, Y + 30, makecol(255, 255, 255), -1, "%d - %d", Life, radius);
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
