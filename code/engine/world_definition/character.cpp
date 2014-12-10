/*********************************************************
File Name:	    character.cpp
Author:		    The Breakfast Club
Creation Date:  09-28-2014
Description:	Defines the different types of sprites that can
                be in the world.
************************************************************/

#include "character.h"
#include "../render/gfx.h"

Character::Character() 
{
  world = 0;
}  

Character::Character(int x, int y, GameWorld *world, bool solid, bool pushable, bool pushes, int speed) : 
  Object(x, y, world, solid, pushable)
{
  hitPoints = 100;
  maxHitPoints = 100;
  this->pushes = pushes;
  this->speed = speed;
  invincible = false;
  hit = false;
}

Character::~Character() {}

bool Character::move(int dx, int dy) {
  if(pushes) return push(dx, dy);
  else return moveTo(x + dx, y + dy);
}


int Character::getHitPoints() {
    return hitPoints;
}

/**
 * Returns true if the hit points were successfully changed
 */
bool Character::changeHitPoints(int change) {
    
    if (!invincible || change > 0) {
        hitPoints += change;
        if (hitPoints > maxHitPoints) hitPoints = maxHitPoints;
        return true;
    }
    return false;
}

/**
 * Returns true if the hit points were successfully changed
 */
bool Character::setHitPoints(int hp) {
  return hitPoints = hp;
}

void Character::damage(int d) {
  if(d && !hit && !invincible) {
    hitPoints -= d;
    hit = true;
  }
}