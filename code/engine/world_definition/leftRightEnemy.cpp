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
  if(x <= x_min) push(speed*(direction=1), 0);
  else if(x >= x_max) push(speed*(direction=-1), 0);
//   else push(speed*direction, 0);
  else if(!push(speed*direction, 0)) direction *= -1;
}
