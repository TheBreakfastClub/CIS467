/*********************************************************
File Name:	    enemy.h
Author:		    The Breakfast Club
Creation Date:  09-25-2014
Description:	Defines the different types of enemies in
		the world.
************************************************************/

#pragma once

#include <string>
#include "sprite.h"
#include "character.h"
#include "hero.h"
#include "resolution.h"

class Enemy: public Character {
public:
	Enemy(int hp, int speed, int damage, int x=0, int y=0, bool inv=false);
	Enemy(Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x=0, int y=0, bool inv=false);

	// subclasses of Enemy will define how to act
	virtual void action(Hero &hero, Image *map, Resolution res) = 0;

};

class AutoSentry : public Enemy {
public:
	AutoSentry(int hp, int speed, int damage, int x=0, int y=0, bool inv=false);
	AutoSentry(Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x=0, int y=0, bool inv=false);
	
    void action(Hero &hero, Image *map, Resolution res);
};
