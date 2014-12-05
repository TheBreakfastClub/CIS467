/*********************************************************
File Name:	    enemy.h
Author:		    The Breakfast Club
Creation Date:  09-25-2014
Description:	Defines the different types of enemies in
		the world.
************************************************************/

#pragma once

#include <string>
#include <utility>
#include "sprite.h"
#include "character.h"
#include "hero.h"
#include "resolution.h"
#include "enemyType.h"

class Enemy: public Character {
public:
	Enemy(int hp, int speed, int damage, int x=0, int y=0, bool inv=false);
	Enemy(Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x=0, int y=0, bool inv=false);

    // True if the enemy hurts the hero by pushing it into walls
    bool pushes;

    // for enemies who make use of pathfinding
    static int count;
    int id;

	// subclasses of Enemy will define how to act
	virtual void action(Hero &hero, std::vector<Enemy*> &enemies, Image *map, Resolution res, float) = 0;
    pair<bool,bool> move (Hero &hero, Image *map, Resolution res, int xMov, int yMov, float);
    pair<bool,bool> moveCheckCollision(Hero &hero, Image *map, Resolution res, int dx, int dy, float);
    pair<bool,bool> moveCheckCollisionAndPush(Hero &hero, Image *map, Resolution res, int dx, int dy, float);
};


class StaticEnemy : public Enemy {

public:
	StaticEnemy(int hp, int speed, int damage, int x=0, int y=0, bool inv=true);
	StaticEnemy(Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x=0, int y=0, bool inv=true);
	
    void action(Hero &hero, std::vector<Enemy*> &enemies, Image *map, Resolution res, float);
};
