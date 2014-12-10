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
#include "../render/image.h"
#include "../render/gfx.h"
#include "object.h"

class Item: public Object {

    public:
        Item(int x, int y, GameWorld *world, bool solid = false, bool pushable = false, 
          std::string name = "<item>", bool obtainable = true);
        ~Item();
        
        /** A short name describing the type of item (e.g. "eggs") */
        std::string name;
        
        /** Defines if the item is obtainable or not **/
        bool obtainable;

        // Add here other properties that all items of a single type should have

};

