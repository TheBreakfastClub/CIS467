/*********************************************************
File Name:	    sprite.h
Author:		    The Breakfast Club
Creation Date:  09-28-2014
Description:	Defines the different types of sprites that can
                be in the world.
************************************************************/

#pragma once

#include "../render/image.h"
#include <utility>

class Sprite {

    private:
        

    public:
        Sprite(int x, int y, Image *spriteImage);
        int x;
        int y;
        Image *spriteImage;
};

