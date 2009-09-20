#include <allegro.h>
#include <math.h>
#include <time.h>

#include "objectParticle.h"

using namespace objects;

objParticle::objParticle(int startX, int startY, double xSpeed, double ySpeed, int startRadius, int endRadius, int startColor, int endColor, double lifeSpan) {
	X = startX;
	Y = startY;
	Xspeed = xSpeed;
	Yspeed = ySpeed;
	sRadius = startRadius;
	dRadius = endRadius;
	radius = sRadius;
	sColor = startColor;
	dColor = endColor;
	color = sColor;
	life = (int)(lifeSpan * CLOCKS_PER_SEC);
	birth = clock();
		
	updateCount = FPS_TARGET * lifeSpan;
	if (updateCount < 0) updateCount = 1;
	updateNum = 0;
	}

objParticle::~objParticle() {}

bool objParticle::update() {
	X += Xspeed;
	Y += Yspeed;
	
	radius = (int)(sRadius + (dRadius - sRadius)/updateCount*updateNum);
	color = makecol(
				(int)(getr(sColor) + (getr(dColor) - getr(sColor))/updateCount*updateNum),
				(int)(getg(sColor) + (getg(dColor) - getg(sColor))/updateCount*updateNum),
				(int)(getb(sColor) + (getb(dColor) - getb(sColor))/updateCount*updateNum)
				);

	updateNum ++;

	if (life + birth < clock() || radius <= 0) {
		return false;		
		}
	return true;
	}

void objParticle::draw(BITMAP *G) {
	circlefill(G, (int)X, (int)Y, (int)radius, color);
	}
