/*********************************************************
File Name:	    item.h
Author:		    The Breakfast Club
Creation Date: 	    09-25-2014
Description:	    Defines the item attributes.
************************************************************/

#include "item.h"

Item::Item(int x, int y, std::string pname, bool obtainable)
 : Sprite(x, y), name(pname), obtainable(obtainable) {}



