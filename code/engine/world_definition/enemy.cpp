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
	float a = abs(x - hero.x);
	float b = abs(y - hero.y);
	float dist = sqrt(a*a + b*b);
	//std::cout << "distance from hero: " << std::to_string(c) << std::endl;

	// move in for the kill if Hero is close enough
	if (dist <= 200.0f) {
		int x_inc = 0, y_inc = 0;
		if (x > hero.x) x_inc = -speed;
		else if (x < hero.x) x_inc = speed;
		if (y > hero.y) y_inc = -speed;
		else if (y < hero.y) y_inc = speed;

		// check for collision before updating position
		if (!hero.hit && hero.getSpriteImage(res)->collision(getSpriteImage(res), hero.x - x + x_inc, hero.y - y + y_inc)) {
			hero.hitPoints -= attackDmg;
			hero.hit = true;
			std::cout << "Hero HP: " << std::to_string(hero.hitPoints) << std::endl;
		}
		else if (!map->collision(getSpriteImage(res), x + x_inc, y + y_inc)) {
			x += x_inc;
			y += y_inc;
		}
	}
}
