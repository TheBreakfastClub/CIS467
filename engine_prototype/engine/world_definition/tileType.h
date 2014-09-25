/*********************************************************
File Name:	    tileType.h
Author:		    The Breakfast Club
Creation Date:  09-25-2014
Description:	Defines the different types of tiles that can
                make up the world.
************************************************************/

#pragma once

// Includes
#include <string>
#include <vector>
#include "tileSet.h"

class TileType{

    public:
        
        TileType(std::string pname = "null", TileSet ptype = TileSet::COUNT);

        /** A short name describing the type of tile (e.g. "wall") */
        std::string name;
        
        /** Defines the kind of tile this is so that other classes may
         * easily tell what type of tile they are working with */
        TileSet type; 

        /** blocking[i] = True if this tile type is blocking at pixelation level i */
        std::vector<bool> blocking;

        // Add here other properties that all tiles of a single type should have

};

