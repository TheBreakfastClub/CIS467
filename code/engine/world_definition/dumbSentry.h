/*********************************************************
File Name:      enemy.h
Author:         The Breakfast Club
Creation Date:  09-25-2014
Description:    Defines the different types of enemies in
        the world.
************************************************************/

#pragma once

#include <string>
#include "sprite.h"
#include "character.h"
#include "hero.h"

class DumbSentry : public Enemy {
public:
    DumbSentry(int x, int y, GameWorld *world, bool solid, bool pushable, bool pushes, 
      int speed, int touchDamage, int crushDamage);
    ~DumbSentry();
    
    void action();
		int dx;
		int dy;
		int countdown;
};
