/*********************************************************
File Name:	    hero.h
Author:		    The Breakfast Club
Creation Date:  09-25-2014
Description:	Defines the hero attributes.
************************************************************/

#pragma once

// Includes
#include <string>
#include "character.h"
#include "item.h"
#include <vector>

class Hero: public Character{
    private:
        Sprite *hitSprite;

    public:
        Hero();
        ~Hero();
        bool loadImage(const char *fileName, int medCut = 8, int lowCut = 16, bool rotates = false);
        void draw(Image *screen, int panX, int panY);
        vector<Item*> bag;
        vector<Item*> crystals;

        // Add here other properties that the hero of a single type should have
};

