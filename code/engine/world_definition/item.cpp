/*********************************************************
File Name:	    item.h
Author:		    The Breakfast Club
Creation Date: 	    09-25-2014
Description:	    Defines the item attributes.
************************************************************/

#include "item.h"

Item::Item(int x, int y, GameWorld *world, bool solid, bool pushable, 
  std::string name, bool obtainable) : Object(x,y, world, solid, pushable)
{
  this->name = name;
  this->obtainable = obtainable;
}

Item::~Item() {}

