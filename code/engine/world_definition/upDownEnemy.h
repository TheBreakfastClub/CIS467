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



class UpDownEnemy : public Enemy {
public:

    // int hp, int speed, int damage, int x=0, int y=0, bool inv=false

    // Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x=0, int y=0, bool inv=false
    UpDownEnemy(int hp, int speed, int damage, int x=0, int y=0, bool inv=false, int dist=0, int tme=0);
    void action(Hero &hero, std::vector<Enemy*> &enemies, Image *map, Resolution res, float);
    int time;
    int counter;
    int direction;
    int y_top;
    int y_bottom;
};
