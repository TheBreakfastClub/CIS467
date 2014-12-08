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

Enemy::Enemy(int x, int y, GameWorld *world, int speed) : Character(x, y, world, speed) {}

Enemy::~Enemy() {}

StaticEnemy::StaticEnemy(int x, int y, GameWorld *world) : Enemy(x, y, world) 
{
  solid = false;
  speed = 0;
}

StaticEnemy::~StaticEnemy() {}

void StaticEnemy::action() {
    if(world->hero->overlaps(this)) world->hero->damage(1);
}