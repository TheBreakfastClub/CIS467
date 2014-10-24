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

    public:
        Hero();
        ~Hero();

        vector<Item*> bag;

        // Add here other properties that the hero of a single type should have
};

