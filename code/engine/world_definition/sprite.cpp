/*********************************************************
File Name:	    sprite.cpp
Author:		    The Breakfast Club
Creation Date:  09-28-2014
Description:	Defines the different types of sprites that can
                be in the world.
************************************************************/

#include "sprite.h"

Sprite::Sprite(int x, int y, SpriteType *type, Image *spriteImage) : x(x), y(y), type(type), spriteImage(spriteImage) {}


