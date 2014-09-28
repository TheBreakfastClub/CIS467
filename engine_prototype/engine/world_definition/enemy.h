/*********************************************************
File Name:	    enemy.h
Author:		    The Breakfast Club
Creation Date:  09-25-2014
Description:	Defines the different types of enemies in
		the world.
************************************************************/

#pragma once

// Includes
#include <string>
#include "enemy.h"

class TileType{

    public:
        
        TileType(std::string pname = "null", TileSet ptype = TileSet::COUNT);

        /** A short name describing the type of enemy (e.g. "S") */
        std::string name;
        
        /** Defines the kind of tile this is so that other classes may
         * easily tell what type of tile they are working with */
        sprite type; 

        /** Defines the amount of hitpoints an enemy has **/
	std::int hitPoints;

	/** Defines if an enemy is invincible **/
	std::bool invincible;

	/** Defines the speed of an enemy **/
	std::int speed;

	/** Defines the attack damage of an enemy**/
	std::int attackDmg

        // Add here other properties that all tiles of a single type should have

};

