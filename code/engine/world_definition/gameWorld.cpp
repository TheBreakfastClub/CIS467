/*********************************************************
File Name:	    gameWorld.cpp
Author:		    The Breakfast Club
Creation Date:  09-25-2014
Description:    Holds the data defining the world
************************************************************/

#include "gameWorld.h"
#include <SDL2/SDL.h>
#include <iostream> 
#include <numeric>

GameWorld::GameWorld(string world_name) : worldName(world_name) 
{
    currentRes = &lowRes;
    currentResLevel = 0; // 0 -- Background, 1 -- Collision, 2 -- Top
}

void GameWorld::next_resolution()
{
	if (currentResLevel < 2)
		currentResLevel++;
	_set_current_res();
}

void GameWorld::prev_resolution()
{
	if (currentResLevel > 0)
		currentResLevel--;
	_set_current_res();
}

void GameWorld::_set_current_res()
{
	switch (currentResLevel) {
		case 0:
			currentRes = &lowRes; break;
		case 1:
			currentRes = &medRes; break;
		case 2:
			currentRes = &highRes; break;
	}
}

