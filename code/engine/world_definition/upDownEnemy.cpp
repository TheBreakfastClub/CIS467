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
  move(0, direction*speed);
  counter -= speed;
  if(counter <= 0) {
    direction *= -1;
    if(direction == 1) counter = y_max - y;
    else counter = y - y_min;
  }
}
