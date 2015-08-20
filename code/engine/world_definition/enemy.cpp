/*********************************************************
File Name:	   enemy.cpp
Author:		     The Breakfast Club
Creation Date: 09-25-2014
Description:	 Defines the different types of enemies in
               the world.
************************************************************/

#include "enemy.h"
#include "gameWorld.h"
#include <cmath>
#include <iostream>

int Enemy::count = 1;

Enemy::Enemy(int x, int y, GameWorld *world, bool solid, bool pushable, 
  bool pushes, int speed, int touchDamage, int crushDamage) : 
  Character(x, y, world, solid, pushable, pushes, speed) 
{
  this->touchDamage = touchDamage;
  this->crushDamage = crushDamage;
}

Enemy::~Enemy() {}

bool Enemy::move(int dx, int dy) {
  bool touches = overlaps(world->hero, x + dx, y + dy);
  bool moved = Character::move(dx, dy);
  if(touches) {
    if(moved || !pushes) world->hero->damage(touchDamage);
    else if(!world->hero->fits(world->hero->x + dx, world->hero->y + dy)) 
      world->hero->damage(crushDamage);
  }
  return moved;
}

bool Enemy::turnMove(int dx, int dy) {
  turn(dx, dy);
  return move(dx, dy);
}

StaticEnemy::StaticEnemy(int x, int y, GameWorld *world, int touchDamage) : 
  Enemy(x, y, world, false, false, false, 0, touchDamage, 0) {}

StaticEnemy::~StaticEnemy() {}

void StaticEnemy::action() {
    if(world->hero->overlaps(this)) world->hero->damage(touchDamage);
}
