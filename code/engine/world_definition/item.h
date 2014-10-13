/*********************************************************
File Name:	    item.h
Author:		    The Breakfast Club
Creation Date: 	    09-25-2014
Description:	    Defines the item attributes.
************************************************************/

#pragma once

// Includes
#include <string>
#include "item.h"
#include "spriteSet.h"

class Item{

    public:
        
        Item(std::string pname = "null", SpriteSet ptype = SpriteSet::COUNT);

        /** A short name describing the type of item (e.g. "eggs") */
        std::string name;
        
        /** Defines if the item is obtainable or not **/
        bool obtainable;

        // Add here other properties that all items of a single type should have

};

