/*********************************************************
File Name:	    enemy.h
Author:		    The Breakfast Club
Creation Date:  09-25-2014
Description:	Defines the different types of enemies in
		the world.
************************************************************/

#pragma once

#include <string>
#include <utility>
#include "character.h"
#include "hero.h"
#include "resolution.h"
#include "enemyType.h"

class Enemy: public Character {
public:
  Enemy(int x, int y, GameWorld *world, int speed = 1);
  ~Enemy();

  int touchDamage;
  int crushDamage;

  // for enemies who make use of pathfinding
  static int count;
  int id;

	// subclasses of Enemy will define how to act
	virtual void action() = 0;
//     pair<bool,bool> move (Hero &hero, Image *map, Resolution res, int xMov, int yMov);
//     pair<bool,bool> moveCheckCollision(Hero &hero, Image *map, Resolution res, int dx, int dy);
//     pair<bool,bool> moveCheckCollisionAndPush(Hero &hero, Image *map, Resolution res, int dx, int dy);
};


class StaticEnemy : public Enemy {

public:
  StaticEnemy(int x, int y, GameWorld *world);
  ~StaticEnemy();

  void action();
};