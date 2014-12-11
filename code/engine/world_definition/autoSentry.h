#pragma once

#include "../ai/pathfinder.h"
#include "enemy.h"
#include "hero.h"

#include <vector>
#include <utility>
#include <cmath>
#include <iostream>
#include <string>

class AutoSentry : public Enemy {
public:
  AutoSentry(int x, int y, GameWorld *world, bool solid, bool pushable, bool pushes, 
    int speed, int touchDamage, int crushDamage);
  ~AutoSentry();
  
  void action();

  Pathfinder pathfinder;
	long moves;
	bool active;
};