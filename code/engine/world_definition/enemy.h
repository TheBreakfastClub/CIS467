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

class Enemy: public Character {
public:
	Enemy(int hp, int speed, int damage, int x=0, int y=0, bool inv=false, Image *char_img=NULL);

	// keep a count of how many enemies have been generated. current count when spawned
	// will be an ememy's id.
	static int count;
	int id;

	// subclasses of Enemy will define how to act
	virtual void action(Hero &hero, std::vector<Enemy*> &enemies, Image *map) = 0;

};


