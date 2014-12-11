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
#include "sublevel.h"
#include "../render/image.h"
#include "../render/gfx.h"
#include "object.h"

class Portal: public Object {

public:
    Portal(int x, int y, GameWorld *world, std::string name = "<portal>", bool usable = true, 
      Sublevel destination = Sublevel::HUB, int dstX = 0, int dstY = 0);
    ~Portal();
    
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

