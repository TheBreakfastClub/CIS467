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

Character::Character(int x, int y, GameWorld *world, int speed) : Object(x, y, world)
{
  hitPoints = 100;
  maxHitPoints = 100;
  this->speed = speed;
  invincible = false;
}

Character::~Character() {}

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
  if(!hit && !invincible) {
    hitPoints -= d;
    hit = true;
  }
}