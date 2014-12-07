#include "enemy.h"
#include "upDownEnemy.h"

UpDownEnemy::UpDownEnemy(int x, int y, GameWorld *world, int speed, int range) :
  Enemy(x, y, world, speed)
{
  direction = -1;
  y_min = y - range;
  y_max = y + range;
}  

UpDownEnemy::~UpDownEnemy() {}

void UpDownEnemy::action()
{
  if(!move(0, speed*direction) || y >= y_max || y <= y_min) direction *= -1;
}
