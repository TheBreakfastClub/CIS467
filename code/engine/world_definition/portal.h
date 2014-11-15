/*********************************************************
File Name:	    portal.h
Author:		    The Breakfast Club
Creation Date: 	    11-12-2014
Description:	    Defines the portal attributes.
************************************************************/

#pragma once

// Includes
#include <string>
#include "portal.h"
#include "sprite.h"
#include "sublevel.h"
#include "../render/image.h"
#include "../render/gfx.h"

class Portal: public Sprite {

    public:
        
        Portal(int x, int y, std::string pname = "null", bool usable=true, Sublevel destination = Sublevel::HUB);

        /** A short name describing the type of item (e.g. "eggs") */
        std::string name;
        
        /** Defines if the item is obtainable or not **/
        bool obtainable;

	/** Defines what Sublevel the portal leads to **/
	Sublevel destination;
        // Add here other properties that all items of a single type should have

};

