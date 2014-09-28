/*********************************************************
File Name:	    item.h
Author:		    The Breakfast Club
Creation Date:  09-25-2014
Description:	Defines the item attributes.
************************************************************/

#pragma once

// Includes
#include <string>
#include "item.h"

class item{

    public:
        
        TileType(std::string pname = "null", TileSet ptype = TileSet::COUNT);

        /** A short name describing the type of item (e.g. "eggs") */
        std::string name;
        
        /** Defines if the item is obtainable or not **/
	std::bool obtainable;

        // Add here other properties that all items of a single type should have

};

