#include "enemy.h"
#include "dumbSentry.h"
#include "gameWorld.h"
#include <cstdlib>

DumbSentry::DumbSentry(int x, int y, GameWorld *world, int speed, int range) : Enemy(x, y, world, speed)
{
	dx = 0;
	dy = 0;
	countdown = 0;
  this->range = range*range; // we use range^2 internally
}  

DumbSentry::~DumbSentry() {}

void DumbSentry::action()
{
	// determine how far away we are from the hero
	float a = x - world->hero->x;
	float b = y - world->hero->y;
  if((a*a + b*b) > range) return;

//	if (d2 <= r*r) { // if distance <= range

		if(countdown > 0) {
			if(!(countdown & 7)) {
				dx = ((rand() % 3) - 1)*speed;
				dy = ((rand() % 3) - 1)*speed;
			}
			turnPush(dx, dy);
			countdown--;
		}
//			if(turnPush(dx, dy)) countdown--;
//			else countdown=0;
		else {
			dx = 0, dy = 0;
			if (x > world->hero->x) dx = -speed;
			else if (x < world->hero->x) dx = speed;

			if (y > world->hero->y) dy = -speed;
			else if (y < world->hero->y) dy = speed;
	
			if((dx || dy) && !turnPush(dx, dy)) countdown = 48;
		}

}
