/*********************************************************
File Name:	    spriteType.h
Author:		    The Breakfast Club
Creation Date:  09-28-2014
Description:	Defines the different types of sprites that can
                be in the world.
************************************************************/

#pragma once

// Includes
#include <string>

// Custom includes
#include "spriteSet.h"

class SpriteType{

    public:
        
        // Constructor
        SpriteType(std::string pname = "null", SpriteSet ptype = SpriteSet::COUNT);

        /** A short name describing the type of sprite (e.g. "spikeBall") */
        std::string name;
        
        /** Defines the kind of sprite this is so that other classes may
         * easily tell what type of sprite they are working with */
        SpriteSet type; 

    	/** The max amount of hitpoints the sprite has (i.e. when fully healthy) **/
        int max_hitpoints;


        // Add here other properties that all sprites of a single type should have

};

