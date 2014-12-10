/*********************************************************
File Name:	    enemy.cpp
Author:		    The Breakfast Club
Creation Date:  09-25-2014
Description:	Defines the different types of enemies in
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

// returns true if move is successful OR we have "crushed" the hero
bool Enemy::move(int dx, int dy) {
  if(overlaps(world->hero, x+dx, y+dy)) { // touching the hero
    if(!pushes || Character::move(dx, dy)) {
      std::cout << "touching " << touchDamage << "\n";
      world->hero->damage(touchDamage);
    }
    else {
      world->hero->damage(crushDamage);
      std::cout << "crushing" << crushDamage << "\n";
    }
    return true;
  }
  else return Character::move(dx, dy);
}

StaticEnemy::StaticEnemy(int x, int y, GameWorld *world, int touchDamage) : 
  Enemy(x, y, world, 0, false, false, false, touchDamage, 0) {}

StaticEnemy::~StaticEnemy() {}

void StaticEnemy::action() {
    if(world->hero->overlaps(this)) world->hero->damage(1);
}