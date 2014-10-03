/*********************************************************
File Name:	    sprite.h
Author:		    The Breakfast Club
Creation Date:  09-28-2014
Description:	Defines the different types of sprites that can
                be in the world.
************************************************************/

#pragma once

#include "spriteType.h"
#include <utility>

class Sprite {

    private:
        std::pair<int,int> xy;

    public:
        Sprite(int x, int y, SpriteType *type);

        SpriteType *type;

        /** Defines the amount of hitpoints a sprite has **/
	    int hitPoints;

    	/** Defines if a sprite is invincible **/
	    bool invincible;

	    /** Defines the speed of a sprite **/
	    int speed;
	    
        /** Defines the attack damage of a sprite **/
	    int attackDmg;
};

