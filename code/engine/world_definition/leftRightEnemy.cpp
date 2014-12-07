#include "enemy.h"
#include "leftRightEnemy.h"
#include "../render/gfx.h"

LeftRightEnemy::LeftRightEnemy(int x, int y, GameWorld *world, int speed, int range) : 
  Enemy(x, y, world, speed)
{
  direction = -1;
  x_min = x - range;
  x_max = x + range;
}  

LeftRightEnemy::~LeftRightEnemy() {}

void LeftRightEnemy::action()
{
    // in the process of moving
    if (x > x_min && x < x_max)
      move(speed*direction, 0);
    else
      direction = direction * -1;
}
