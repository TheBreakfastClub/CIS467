/*********************************************************
File Name:	    hero.cpp
Author:		    The Breakfast Club
Creation Date:  09-28-2014
Description:	Defines the hero of the game universe.
************************************************************/

#include "hero.h"

Hero::Hero() {
    setHitPoints(100);
    invincible = false;
    speed = 5;
    attackDmg = 0;
    x = 150;
    y = 150;
}

Hero::~Hero() {

    while (!bag.empty()) {
        delete bag.back();
        bag.pop_back();
    }
    while (!crystals.empty()) {
        delete crystals.back();
        crystals.pop_back();
    }
}
