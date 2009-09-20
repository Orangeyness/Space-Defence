#include <allegro.h>
#include <math.h>
#include <time.h>

#include "objectBullet.h"
#include "linkedLists.h"
#include "objectInterface.h"

using namespace objects;
using namespace linkedLists;

objBullet::objBullet(int startX, int startY, int destinationX, int destinationY, double dir, int spd) {
	X = startX;
	Y = startY;
	lX = X;
	lY = Y;
	dX = destinationX;
	dY = destinationY;
	speed = spd;
	direction = dir;
	stage = 0;	
	}

objBullet::~objBullet(){};

bool objBullet::update(LinkedList<ObjectInterface*>* Asteroids, LinkedList<ObjectInterface*>* Particles) {
	switch(stage) {
		case 0:
			lX = X;
			lY = Y;
			
			X = (int)(X + speed * sin(direction));
			Y = (int)(Y + speed * cos(direction));
			
			if (sqrt((dX - X) * (dX - X) + (dY - Y) * (dY - Y)) < speed) {
				stage ++;				
				}
			break;
		case 1:
			/*while(Asteroids->nodeCount > 0) {
				delete Asteroids->getFirstValue();	
				Asteroids->getFirst()->remove();
				}*/
			stage ++;
			break;
		case 2:
			return false;
			break;
		}	


	return true;	
	}

void objBullet::draw(BITMAP *G) {
	line(G, lX - 1, lY - 1, X - 1, Y - 1, BULLET_COLOR);
	line(G, lX - 1, lY, X - 1, Y, BULLET_COLOR);
	line(G, lX, lY - 1, X, Y - 1, BULLET_COLOR);
	line(G, lX, lY, X, Y, BULLET_COLOR);

	line(G, lX + 1, lY + 1, X + 1, Y + 1, BULLET_COLOR);
	line(G, lX + 1, lY, X + 1, Y, BULLET_COLOR);
	line(G, lX, lY + 1, X, Y + 1, BULLET_COLOR);
	line(G, lX, lY, X, Y, BULLET_COLOR);
	}
