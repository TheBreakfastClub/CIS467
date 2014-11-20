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
	AutoSentry(int hp, int speed, int damage, int x=0, int y=0, bool inv=false, Image *char_img=NULL);
	void action(Hero &hero, std::vector<Enemy*> &enemies, Image *map);
	Pathfinder pathfinder;
	long moves;
	bool active;
};