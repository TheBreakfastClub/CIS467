/*********************************************************
File Name:	    gameWorld.cpp
Author:		    The Breakfast Club
Creation Date:  09-25-2014
Description:    Holds the data defining the world
************************************************************/

#include "gameWorld.h"

/**
 * dim_x, dim_y : dimensions of window in SDL's units
 * hRes_x, hRes_y : dimension of the gameWorld in Pixel size
 */
GameWorld::GameWorld(int dim_x, int dim_y, int tile_dim, int hRes_x, int hRes_y)
    : dim_x(dim_x), dim_y(dim_y), tile_dim(tile_dim), highRes(hRes_x, hRes_y),
    medRes(hRes_x/2, hRes_y/2), lowRes(hRes_x/4, hRes_y/4)
{
    currentRes = &lowRes;
    currentResLevel = 0;
}

