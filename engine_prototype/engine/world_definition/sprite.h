/*********************************************************
File Name:	    sprite.h
Author:		    The Breakfast Club
Creation Date:  09-28-2014
Description:	Defines the different types of sprites that can
                be in the world.
************************************************************/

#pragma once

// Includes
#include <string>

class TileType{

    public:
        
        TileType(std::string pname = "null", TileSet ptype = TileSet::COUNT);

        /** A short name describing the type of sprite (e.g. "spikeBall") */
        std::string name;
        
        /** Defines the kind of sprite this is so that other classes may
         * easily tell what type of sprite they are working with */
        sprite type; 

	/** The amount of hitpoints the sprite has **/
        std::int hitpoints;


        // Add here other properties that all tiles of a single type should have

};

