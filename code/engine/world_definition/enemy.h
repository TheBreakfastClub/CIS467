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

    // True if the enemy hurts the hero by pushing it into walls
    bool pushes;

	// subclasses of Enemy will define how to act
	virtual void action(Hero &hero, Image *map, Resolution res) = 0;
    void move (Hero &hero, Image *map, Resolution res, int xMov, int yMov);
    bool moveCheckCollision(Hero &hero, Image *map, Resolution res, int dx, int dy);
    bool moveCheckCollisionAndPush(Hero &hero, Image *map, Resolution res, int dx, int dy);
};

class AutoSentry : public Enemy {
public:
	AutoSentry(int hp, int speed, int damage, int x=0, int y=0, bool inv=false);
	AutoSentry(Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x=0, int y=0, bool inv=false);
	
    void action(Hero &hero, Image *map, Resolution res);
};

class StaticEnemy : public Enemy {

public:
	StaticEnemy(int hp, int speed, int damage, int x=0, int y=0, bool inv=true);
	StaticEnemy(Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x=0, int y=0, bool inv=true);
	
    void action(Hero &hero, Image *map, Resolution res);
};

