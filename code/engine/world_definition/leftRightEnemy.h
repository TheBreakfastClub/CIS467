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

class LeftRightEnemy : public Enemy {
public:
    LeftRightEnemy(int x, int y, GameWorld *world, int speed = 1, int range = 100);
    ~LeftRightEnemy();
    
    void action();
    int direction;
    int x_min;
    int x_max;
};