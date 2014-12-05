/*********************************************************
File Name:	    enemy.cpp
Author:		    The Breakfast Club
Creation Date:  09-25-2014
Description:	Defines the different types of enemies in
		the world.
************************************************************/

#include "enemy.h"
#include "../render/collision.h"
#include <cmath>
#include <iostream>

int Enemy::count = 1;

Enemy::Enemy(int hp, int speed, int damage, int x, int y, bool inv) 
 : Character(hp, speed, damage, x, y, inv), pushes(false) { id = count++; }

Enemy::Enemy(Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x, int y, bool inv) 
 : Character(charImgH, charImgM, charImgL, hp, speed, damage, x, y, inv), pushes(false) {}

/**
 * This checks to see if the enemy will collide with anything if it moves the given change in x and y.
 * This should be used if the enemy cannot push the hero.
 *
 * @return pair.first = true if the enemy was able to move to the indicated location, false otherwise
 * @return pair.second = true if the enemy collided with the hero, false otherwise
 */
pair<bool,bool> Enemy::moveCheckCollision(Hero &hero, Image *map, Resolution res, int dx, int dy, float s) {
    
    if(scollision(getSpriteImage(res), x+dx, y+dy, scale[res], map, 0, 0, s)) return make_pair(false,false);
    if(scollision(hero.getSpriteImage(res), hero.x, hero.y, hero.scale[res],
      getSpriteImage(res), x + dx, y + dy, scale[res])) {
        if (!hero.hit) {
            hero.changeHitPoints(-attackDmg);
            hero.hit = true;
        }
        return make_pair(false,true);
    }
    return make_pair(true, false);
}

/**
 * This checks to see if the enemy will collide with anything if it moves the given change in x and y.
 * It returns true if it collides, false otherwise. This should be used if the enemy can push the
 * hero. If the enemy then collides with the hero, it pushes the hero and returns false.
 * 
 * @return pair.first = true if the enemy was able to move to the indicated location, false otherwise
 * @return pair.second = true if the enemy collided with the hero, false otherwise
 */
pair<bool,bool> Enemy::moveCheckCollisionAndPush(Hero &hero, Image *map, Resolution res, int dx, int dy, float s) {

    if(scollision(getSpriteImage(res), x+dx, y+dy, scale[res], map, 0, 0, s)) return make_pair(false, false);
    if(scollision(hero.getSpriteImage(res), hero.x, hero.y, hero.scale[res],
      getSpriteImage(res), x+dx, y+dy, scale[res])) {
        if (scollision(hero.getSpriteImage(res), hero.x+dx, hero.y+dy, hero.scale[res], map, 0, 0, s)) {
            if (!hero.hit) {
                hero.changeHitPoints(-attackDmg);
                hero.hit = true;
            }
            return make_pair(false, true);
        } else {
            hero.x += dx;
            hero.y += dy;
            return make_pair(true, true);
        }
    }
    return make_pair(true, false);
}

/**
 * Moves the enemy by up to xMov horizontally and yMov vertically. If the enemy
 * would collide while moving to its new destination, it stops at the obstacle.
 *
 * 
 * @return pair.first = true if the enemy was able to move to the indicated location, false otherwise
 * @return pair.second = true if the enemy collided with the hero, false otherwise
 */
pair<bool,bool> Enemy::move (Hero &hero, Image *map, Resolution res, int xMov, int yMov, float s) {

    int dx = (xMov > 0) ? 1 : -1;
    int dy = (yMov > 0) ? 1 : -1;
    xMov = abs(xMov);
    yMov = abs(yMov);
    pair<bool,bool> results;

    if (!pushes) {

        int xInc = 0;
        int yInc = 0;

        // Move in both x and y direction
        while (xInc < xMov && yInc < yMov) {
            
            results = moveCheckCollision(hero, map, res, dx, dy, s);
            if(!results.first) return results;
            x += dx;
            y += dy;
            ++xInc;
            ++yInc;
        }
        
        // Move in either x or y direction, if needed
        while (xInc < xMov) {
            results = moveCheckCollision(hero, map, res, dx, 0, s);
            if (!results.first) return results;
            x += dx;
            ++xInc;
        }
        while (yInc < yMov) {
            results = moveCheckCollision(hero, map, res, 0, dy, s);
            if (!results.first) return results;
            y += dy;
            ++yInc;
        }

    } else {

        int xInc = 0;
        int yInc = 0;

        // Move in both x and y direction
        while (xInc < xMov && yInc < yMov) {
            
            results = moveCheckCollisionAndPush(hero, map, res, dx, dy, s);
            if(!results.first) return results;
            x += dx;
            y += dy;
            ++xInc;
            ++yInc;
        }

        // Move in either x or y direction, if needed
        while (xInc < xMov) {

            results = moveCheckCollisionAndPush(hero, map, res, dx, 0, s);
            if (!results.first) return results;
            x += dx;
            ++xInc;
        }
        while (yInc < yMov) {

            results = moveCheckCollisionAndPush(hero, map, res, 0, dy, s);
            if (!results.first) return results;
            y += dy;
            ++yInc;
        }
    }
    return results;
}


StaticEnemy::StaticEnemy(int hp, int speed, int damage, int x, int y, bool inv) 
 : Enemy(hp, speed, damage, x, y, inv) {}

StaticEnemy::StaticEnemy(Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x, int y, bool inv) 
 : Enemy(charImgH, charImgM, charImgL, hp, speed, damage, x, y, inv) {}

void StaticEnemy::action(Hero &hero, std::vector<Enemy*> &enemies, Image *map, Resolution res, float s) {

    if(scollision(hero.getSpriteImage(res), hero.x, hero.y, hero.scale[res],
      getSpriteImage(res), x, y, scale[res])) {
        if (!hero.hit) {
            hero.changeHitPoints(-attackDmg);
            hero.hit = true;
        }
    }
}
