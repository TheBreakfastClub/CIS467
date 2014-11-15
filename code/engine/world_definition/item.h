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
#include "sprite.h"
#include "../render/image.h"
#include "../render/gfx.h"

class Item: public Sprite {

    public:
        
        Item(int x, int y, std::string pname = "<item>", bool obtainable=true);

        /** A short name describing the type of item (e.g. "eggs") */
        std::string name;
        
        /** Defines if the item is obtainable or not **/
        bool obtainable;

        // Add here other properties that all items of a single type should have

};

