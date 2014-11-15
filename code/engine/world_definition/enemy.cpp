/*********************************************************
File Name:	    enemy.cpp
Author:		    The Breakfast Club
Creation Date:  09-25-2014
Description:	Defines the different types of enemies in
		the world.
************************************************************/

#include "enemy.h"
//#include <stdlib.h>
#include <cmath>
#include <iostream>

Enemy::Enemy(int hp, int speed, int damage, int x, int y, bool inv) 
 : Character(hp, speed, damage, x, y, inv) {}

Enemy::Enemy(Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x, int y, bool inv) 
 : Character(charImgH, charImgM, charImgL, hp, speed, damage, x, y, inv) {}

AutoSentry::AutoSentry(int hp, int speed, int damage, int x, int y, bool inv) 
 : Enemy(hp, speed, damage, x, y, inv) {}

AutoSentry::AutoSentry(Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x, int y, bool inv) 
 : Enemy(charImgH, charImgM, charImgL, hp, speed, damage, x, y, inv) {}

void AutoSentry::action(Hero &hero, Image *map, Resolution res)
{
	// determine how far away we are from the hero
	float a = x - hero.x;
	float b = y - hero.y;
	float dist2 = a*a + b*b; // distance squared
	//std::cout << "distance from hero: " << std::to_string(c) << std::endl;

	// move in for the kill if Hero is close enough
	if (dist2 <= 40000.0) { // if distance <= 200
		int x_inc = 0, y_inc = 0;
		if (x > hero.x) x_inc = -speed;
		else if (x < hero.x) x_inc = speed;
		if (y > hero.y) y_inc = -speed;
		else if (y < hero.y) y_inc = speed;

		// move first
		if (!map->collision(getSpriteImage(res), x + x_inc, y + y_inc)) {
			x += x_inc;
			y += y_inc;
		}
		//then check for collision with hero
		if (!hero.hit && hero.getSpriteImage(res)->collision(getSpriteImage(res), x - hero.x, y - hero.y)) {
			hero.hitPoints -= attackDmg;
			hero.hit = true;
			std::cout << "Hero HP: " << std::to_string(hero.hitPoints) << std::endl;
		}

	}
}
