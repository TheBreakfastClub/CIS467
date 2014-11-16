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
        
        Portal(int x, int y, std::string pname = "null", bool usable=true, Sublevel destination = Sublevel::HUB, int xDest = 0, int yDest = 0);

        /** A short name describing the type of portal (e.g. "hubPortal") */
        std::string name;
        
        /** Defines if the portal is usable or not **/
        bool usable;

	/** Defines what Sublevel the portal leads to **/
	Sublevel destination;
	
	/** x coordinate of where the portal leads to **/
	int xDest;
	
	/** y coordinate of where the portal leads to **/
	int yDest;
        // Add here other properties that all items of a single type should have

};

