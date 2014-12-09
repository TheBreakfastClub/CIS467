#include "enemy.h"
#include "upDownEnemy.h"

UpDownEnemy::UpDownEnemy(int x, int y, GameWorld *world, int speed, int range) : Enemy(x, y, world, speed)
{
  direction = -1;
  y_min = y - range;
  y_max = y + range;
}  

UpDownEnemy::~UpDownEnemy() {}

void UpDownEnemy::action()
{
  if(y <= y_min) push(0, speed*(direction=1));
  else if(y >= y_max) push(0, speed*(direction=-1));
//   else push(0, speed*direction);
  else if(!push(0, speed*direction)) direction *= -1;
}
