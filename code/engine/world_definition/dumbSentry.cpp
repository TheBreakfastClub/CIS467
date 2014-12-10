#include "enemy.h"
#include "dumbSentry.h"
#include "gameWorld.h"
#include <cstdlib>

DumbSentry::DumbSentry(int x, int y, GameWorld *world, bool solid, bool pushable, 
  bool pushes, int speed, int touchDamage, int crushDamage) : 
  Enemy(x, y, world, solid, pushable, pushes, speed, touchDamage, crushDamage)
{
	dx = 0;
	dy = 0;
	countdown = 0;
}  

DumbSentry::~DumbSentry() {}

void DumbSentry::action()
{
		if(countdown > 0) {
			if(!(countdown & 7)) {
				dx = ((rand() % 3) - 1)*speed;
				dy = ((rand() % 3) - 1)*speed;
			}
			turnMove(dx, dy);
			countdown--;
		}

		else {
			dx = 0, dy = 0;
			if (x > world->hero->x) dx = -speed;
			else if (x < world->hero->x) dx = speed;

			if (y > world->hero->y) dy = -speed;
			else if (y < world->hero->y) dy = speed;
	
			if((dx || dy) && !turnMove(dx, dy)) countdown = 48;
		}

}
