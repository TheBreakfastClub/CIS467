#include "enemy.h"
#include "upDownEnemy.h"

UpDownEnemy::UpDownEnemy(int x, int y, GameWorld *world, int speed, 
  int touchDamage, int crushDamage, int range) : 
  Enemy(x, y, world, true, false, true, speed, touchDamage, crushDamage)
{
  direction = -1;
  y_min = y - range;
  y_max = y + range;
  counter = range;
}  

UpDownEnemy::~UpDownEnemy() {}

void UpDownEnemy::action()
{
  move(0, direction);
  counter--;
  if(counter <= 0) {
    counter = y_max - y_min;
    direction *= -1;
  }

//   
//   
//   if(y <= y_min) move(0, speed*(direction=1));
//   else if(y >= y_max) move(0, speed*(direction=-1));
// //   else move(0, speed*direction);
//   else if(!move(0, speed*direction)) direction *= -1;
}
