#include <allegro.h>
#include <math.h>
#include <time.h>

#include "objectBullet.h"
#include "linkedLists.h"
#include "objectInterface.h"
#include "objectAsteroid.h"
#include "objectParticle.h"

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
			updatePosition();
			
			break;break;
		case 1:
			dealDamage(Asteroids);

			stage ++;
			break;break;
		case 2:
			spawnShockWave(Particles);
		
			stage ++;
			stageAdvanceTime = clock() + 0.1 * CLOCKS_PER_SEC;
			break;break;
		case 3:
			spawnFire(Particles);

			if (stageAdvanceTime < clock()) {
				stage ++;				
				}
			break;break;
		case 4:
			spawnSmoke(Particles);

			stage ++;
			break;break;
		case 5:
			return false;
			break;
		}	


	return true;	
	}

void objBullet::draw(BITMAP *G) {
	if (stage <= 1) {
		line(G, lX - 1, lY - 1, X - 1, Y - 1, BULLET_COLOR);
		line(G, lX - 1, lY, X - 1, Y, BULLET_COLOR);
		line(G, lX, lY - 1, X, Y - 1, BULLET_COLOR);
		line(G, lX, lY, X, Y, BULLET_COLOR);

		line(G, lX + 1, lY + 1, X + 1, Y + 1, BULLET_COLOR);
		line(G, lX + 1, lY, X + 1, Y, BULLET_COLOR);
		line(G, lX, lY + 1, X, Y + 1, BULLET_COLOR);
		line(G, lX, lY, X, Y, BULLET_COLOR);
		}
	}

void objBullet::updatePosition() {			
	lX = X;
	lY = Y;
	
	X = (int)(X + speed * sin(direction));
	Y = (int)(Y + speed * cos(direction));
	
	if (sqrt((dX - X) * (dX - X) + (dY - Y) * (dY - Y)) < BULLET_DAMAGE_RADIUS/2) {
		stage ++;				
		}
	}

void objBullet::dealDamage(LinkedList<ObjectInterface*>* Asteroids) {
	LinkedListNode<ObjectInterface*>* currentNode = Asteroids->getFirst();
	while(currentNode != NULL) {
		objAsteroid* chkAsteroid = (objAsteroid*)currentNode->getValue();

		double distance = sqrt((chkAsteroid->X - X) * (chkAsteroid->X - X) + (chkAsteroid->Y - Y) * (chkAsteroid->Y - Y));
		if (distance < BULLET_DAMAGE_RADIUS + chkAsteroid->radius) {
			chkAsteroid->Life -= BULLET_DAMAGE_MIN + 	(int)(BULLET_VARIBLE_DAMAGE * distance / (BULLET_DAMAGE_RADIUS + chkAsteroid->radius));
			}

		currentNode = currentNode->getNext();
		}
	}

void objBullet::spawnShockWave(LinkedList<ObjectInterface*>* Particles) {
	int ringCount = 40 + rand() % 30;
	int ringSpeed = 20 + rand() % 15;
	for (int i = 0; i < ringCount; i++) {
		int xSpeed = ringSpeed + rand() % 8 - rand() % 8;
		int ySpeed = ringSpeed + rand() % 8 - rand() % 8;

		if (rand() % 2 == 1) xSpeed =- xSpeed;
		if (rand() % 2 == 1) ySpeed =- ySpeed;
		
		int startColor = makecol(255 - rand() % 10, 240 - rand() % 10, rand() % 10);
		int endColor = makecol(60 - rand() % 10, 130 + rand() % 10, rand() % 10);
		int startSize = 2;
		int endSize = 1;
		double lifeSpan = 0.08;
		Particles->addLast(new objParticle(X, Y, xSpeed, ySpeed, startSize, endSize, startColor, endColor, lifeSpan));
		}
	}

void objBullet::spawnFire(LinkedList<ObjectInterface*>* Particles) {
	int fireCount = rand() % 100;
	for (int i = 0; i < fireCount; i++) {
		int xSpeed = 1 + rand()%11;
		int ySpeed = 1 + rand()%11;
		
		if (rand() % 2 == 1) xSpeed =- xSpeed;
		if (rand() % 2 == 1) ySpeed =- ySpeed;
		
		int startColor = makecol(255 - rand()%100, rand()%60, rand()%60);
		int endColor = makecol(10, 10, 10);
		int startSize = 2 + rand()%3;
		int endSize = 1;
		double lifeSpan = 1 + (rand()%70)/100;

		Particles->addLast(new objParticle(X, Y, xSpeed, ySpeed, startSize, endSize, startColor, endColor, lifeSpan));
		}
	}

void objBullet::spawnSmoke(LinkedList<ObjectInterface*>* Particles) {
	int cloudCount = 20 + rand() % 20;
	for (int i = 0; i < cloudCount; i++) {
		double xSpeed = (-(rand() % 30) + rand() % 30)/10;
		double ySpeed = (-(rand() % 30) + rand() % 30)/10;				
		int startColor = makecol(100 + (rand() %10), 100 + (rand() %10), 100 + (rand() %10));
		int endColor = makecol(30 - (rand() %5), 30 - (rand() %5), 30 - (rand() %5));
		int startSize = 1 + rand() % 10;
		int endSize = 1 + rand() % 20;
		double lifeSpan = 0.4 + (rand() % 40)/100;
		
		Particles->addFirst(new objParticle(X + rand()%5 - rand()%5, Y + rand()%5 - rand()%5, xSpeed, ySpeed, startSize, endSize, startColor, endColor, lifeSpan));
		}
	}
