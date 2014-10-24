/*********************************************************
File Name:	    hero.cpp
Author:		    The Breakfast Club
Creation Date:  09-28-2014
Description:	Defines the hero of the game universe.
************************************************************/

#include "hero.h"

Hero::Hero() {
    hitPoints = 100;
    invincible = false;
    speed = 1;
    attackDmg = 0;
    x = 0;
    y = 0;
    spriteImage = NULL;
}

