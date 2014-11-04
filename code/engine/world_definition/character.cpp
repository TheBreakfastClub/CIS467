/*********************************************************
File Name:	    character.cpp
Author:		    The Breakfast Club
Creation Date:  09-28-2014
Description:	Defines the different types of sprites that can
                be in the world.
************************************************************/

#include "character.h"
#include "../render/gfx.h"

Character::Character() : Sprite(0, 0, NULL), hit(false) {}

Character::Character(int hp, int speed, int damage, int x, int y, bool inv, Image *charImg)
 : hitPoints(hp), speed(speed), attackDmg(damage), invincible(inv), hit(false), Sprite(x, y, charImg) 
{
	if (charImg != NULL)
		hitImage = Gfx::redTint(charImg, 50);
}


