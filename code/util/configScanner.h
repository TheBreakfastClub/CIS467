/*********************************************************
File Name:	    configScanner.h
Author:			Steven Hoffman
Creation Date:  11-07-2014
Description:	This program reads in the info from a
                configuration file and makes it accessible
                by other programs.
************************************************************/

#pragma once

#include <iostream>
#include <stdlib.h>
#include <string>
#include "../engine/world_definition/sublevel.h"

using namespace std;

struct WorldDef {
    string name;
    string imgName; // name of image file
    int medCut; // Med resolution will be 1/medCut the size of high res
    int lowCut; // Low resolution will be 1/lowCut the size of high res
    int pixAlg; // Indicates the ID of the pixelation algorithm to use
};

struct ItemDef {
    int x; // location of the item
    int y;
    int itemType; // Indicates the ID of the type of item this is
    string imgName; // name of image file
    Sublevel world; // The world that this item should be placed into
}

class ConfigScanner {

public:
    vector<WorldDef> worlds;
    vector<ItemDef> items;

};

