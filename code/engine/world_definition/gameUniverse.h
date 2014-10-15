/*********************************************************
File Name:	    gameUniverse.h
Author:		    The Breakfast Club
Creation Date:  10-13-2014
Description:    This class holds the different sublevels/subworlds
                and other items common to the whole gameUniverse,
                such as the hero.
************************************************************/

#pragma once

#include "gameWorld.h"
#include "hero.h"
#include "sublevel.h"

class GameUniverse{
  public:
    GameWorld[Sublevel::COUNT] sublevels;
    Hero hero;
};
