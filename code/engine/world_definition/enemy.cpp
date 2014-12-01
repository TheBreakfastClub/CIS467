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
 : Character(hp, speed, damage, x, y, inv), pushes(false) {}

Enemy::Enemy(Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x, int y, bool inv) 
 : Character(charImgH, charImgM, charImgL, hp, speed, damage, x, y, inv), pushes(false) {}

/**
 * This checks to see if the enemy will collide with anything if it moves the given change in x and y.
 * It returns true if it collides, false otherwise. This should be used if the enemy cannot push the
 * hero.
 */
bool Enemy::moveCheckCollision(Hero &hero, Image *map, Resolution res, int dx, int dy) {

    if (map->collision(getSpriteImage(res), x + dx, y + dy)) return true;
    if (hero.getSpriteImage(res)->collision(getSpriteImage(res), x + dx - hero.x, y + dy - hero.y)) {
        if (!hero.hit) {
            hero.hitPoints -= attackDmg;
            hero.hit = true;
            std::cout << "Hero HP: " << std::to_string(hero.hitPoints) << std::endl;
        }
        return true;
    }
    return false;
}

/**
 * This checks to see if the enemy will collide with anything if it moves the given change in x and y.
 * It returns true if it collides, false otherwise. This should be used if the enemy can push the
 * hero. If the enemy then collides with the hero, it pushes the hero and returns false.
 */
bool Enemy::moveCheckCollisionAndPush(Hero &hero, Image *map, Resolution res, int dx, int dy) {

    if (map->collision(getSpriteImage(res), x + dx, y + dy)) return true;
    if (hero.getSpriteImage(res)->collision(getSpriteImage(res), x + dx - hero.x, y + dy - hero.y)) {
        if (map->collision(getSpriteImage(res), hero.x + dx, hero.y + dy)) {
                  
            if (!hero.hit) {
                hero.hitPoints -= attackDmg;
                hero.hit = true;
                std::cout << "Hero HP: " << std::to_string(hero.hitPoints) << std::endl;
            }
            return true;
        } else {
            hero.x += dx;
            hero.y += dy;
        }
    }
    return false;
}

/**
 * Moves the enemy by up to xMov horizontally and yMov vertically. If the enemy
 * would collide while moving to its new destination, it stops at the obstacle.
 */
void Enemy::move (Hero &hero, Image *map, Resolution res, int xMov, int yMov) {

    int dx = (xMov > 0) ? 1 : -1;
    int dy = (yMov > 0) ? 1 : -1;
    xMov = abs(xMov);
    yMov = abs(yMov);

    if (!pushes) {

        int xInc = 0;
        int yInc = 0;

        // Move in both x and y direction
        while (xInc < xMov && yInc < yMov) {

            if(moveCheckCollision(hero, map, res, dx, dy)) return;
            x += dx;
            y += dy;
            ++xInc;
            ++yInc;
        }
        
        // Move in either x or y direction, if needed
        while (xInc < xMov) {
            if (moveCheckCollision(hero, map, res, dx, 0)) return;
            x += dx;
            ++xInc;
        }
        while (yInc < yMov) {
            if (moveCheckCollision(hero, map, res, 0, dy)) return;
            y += dy;
            ++yInc;
        }

    } else {

        int xInc = 0;
        int yInc = 0;

        // Move in both x and y direction
        while (xInc < xMov && yInc < yMov) {

            if(moveCheckCollisionAndPush(hero, map, res, dx, dy)) return;
            x += dx;
            y += dy;
            ++xInc;
            ++yInc;
        }

        // Move in either x or y direction, if needed
        while (xInc < xMov) {
            if (moveCheckCollisionAndPush(hero, map, res, dx, 0)) return;
            x += dx;
            ++xInc;
        }
        while (yInc < yMov) {
            if (moveCheckCollisionAndPush(hero, map, res, 0, dy)) return;
            y += dy;
            ++yInc;
        }
    }
}

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

        move(hero, map, res, x_inc, y_inc);
	}
}

StaticEnemy::StaticEnemy(int hp, int speed, int damage, int x, int y, bool inv) 
 : Enemy(hp, speed, damage, x, y, inv) {}

StaticEnemy::StaticEnemy(Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x, int y, bool inv) 
 : Enemy(charImgH, charImgM, charImgL, hp, speed, damage, x, y, inv) {}

void StaticEnemy::action(Hero &hero, Image *map, Resolution res) {

    if (hero.getSpriteImage(res)->collision(getSpriteImage(res), x - hero.x, y - hero.y)) {
        if (!hero.hit) {
            hero.hitPoints -= attackDmg;
            hero.hit = true;
            std::cout << "Hero HP: " << std::to_string(hero.hitPoints) << std::endl;
        }
    }
}

