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
        int x;
        int y;

    public:
        Sprite(int x, int y, SpriteType *type);

        SpriteType *type;
};

