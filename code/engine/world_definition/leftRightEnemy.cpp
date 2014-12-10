#include "enemy.h"
#include "leftRightEnemy.h"
#include "../render/gfx.h"

LeftRightEnemy::LeftRightEnemy(int x, int y, GameWorld *world, int speed, 
  int touchDamage, int crushDamage, int range) : 
  Enemy(x, y, world, true, false, true, speed, touchDamage, crushDamage)
{
  direction = -1;
  x_min = x - range;
  x_max = x + range;
  counter = range;
}  

LeftRightEnemy::~LeftRightEnemy() {}

void LeftRightEnemy::action()
{
  move(direction*speed, 0);
  counter -= speed;
  if(counter <= 0) {
    direction *= -1;
    if(direction == 1) counter = x_max - x;
    else counter = x - x_min;
  }
}
