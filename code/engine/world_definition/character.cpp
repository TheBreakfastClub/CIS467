/*********************************************************
File Name:	    character.cpp
Author:		    The Breakfast Club
Creation Date:  09-28-2014
Description:	Defines the different types of sprites that can
                be in the world.
************************************************************/

#include "character.h"
#include "../render/gfx.h"

Character::Character() : Sprite(0, 0), hit(false), hitImage(NULL), 
    maxHitPoints(100) {}

Character::~Character() {
    if (hitImage) {
        delete hitImage;
    }
}

Character::Character(int hp, int speed, int damage, int x, int y, bool inv)
 : hitPoints(hp), maxHitPoints(hp), speed(speed), attackDmg(damage), invincible(inv), hit(false), hitImage(NULL), Sprite(x, y) {}

Character::Character(Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x, int y, bool inv)
 : hitPoints(hp), maxHitPoints(hp), speed(speed), attackDmg(damage), invincible(inv), hit(false), Sprite(x, y, charImgH, charImgM, charImgL) 
{
	if (charImgH && charImgM && charImgL) {
		hitImage = redTint(charImgH, 50);
    }
    else {
        hitImage = NULL;
    }
}

int Character::getHitPoints() {
    return hitPoints;
}

/**
 * Returns true if the hit points were successfully changed
 */
bool Character::changeHitPoints(int change) {
    
    if (!invincible || change > 0) {
        hitPoints += change;
        if (hitPoints > maxHitPoints) hitPoints = maxHitPoints;
        return true;
    }
    return false;
}

/**
 * Returns true if the hit points were successfully changed
 */
bool Character::setHitPoints(int newHitPoints) {

    return changeHitPoints(newHitPoints - hitPoints);
}

