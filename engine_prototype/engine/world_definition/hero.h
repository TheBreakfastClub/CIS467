/*********************************************************
File Name:	    hero.h
Author:		    The Breakfast Club
Creation Date:  09-25-2014
Description:	Defines the hero attributes.
************************************************************/

#pragma once

// Includes
#include <string>
#include "hero.h"

class hero{

    public:
        
        SpriteType(std::string pname = "null", SpriteSet ptype = SpriteSet::COUNT);

        /** A short name describing the type of hero (e.g. "mainCharacter") */
        std::string name;
        
        /** Defines the kind of sprite this is so that other classes may
         * easily tell what type of sprite they are working with */
        sprite type; 

        /** Defines the amount of hitpoints an hero has **/
	std::int hitPoints;

	/** Defines if an hero is invincible **/
	std::bool invincible;

	/** Defines the speed of an hero **/
	std::int speed;

	/** Defines the attack damage of an hero**/
	std::int attackDmg

        // Add here other properties that the hero of a single type should have

};

