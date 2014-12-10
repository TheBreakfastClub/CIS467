#include "enemy.h"
#include "leftRightEnemy.h"
#include "../render/gfx.h"

LeftRightEnemy::LeftRightEnemy(int x, int y, GameWorld *world, 
  int speed, int touchDamage, int CrushDamage, int range) :
  Enemy(x, y, world, true, false, true, speed, touchDamage, crushDamage)
{
  direction = -1;
  x_min = x - range;
  x_max = x + range;
}  

LeftRightEnemy::~LeftRightEnemy() {}

void LeftRightEnemy::action()
{
  if(x <= x_min) move(speed*(direction=1), 0);
  else if(x >= x_max) move(speed*(direction=-1), 0);
//   else move(speed*direction, 0);
  else if(!move(speed*direction, 0)) direction *= -1;
}
