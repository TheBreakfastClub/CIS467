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
	AutoSentry(int hp, int speed, int damage, int x=0, int y=0, bool inv=false);
	AutoSentry(Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x=0, int y=0, bool inv=false);
	
    void action(Hero &hero, std::vector<Enemy*> &enemies, Image *map, Resolution res);

    Pathfinder pathfinder;
	long moves;
	bool active;
};