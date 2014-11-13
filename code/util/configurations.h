/*********************************************************
File Name:	    configurations.h
Author:			Steven Hoffman
Creation Date:  11-07-2014
Description:	This program reads in the info from a
                configuration file and makes it accessible
                by other programs.
************************************************************/

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "../engine/world_definition/sublevel.h"
#include "pixUtil.h"

using namespace std;

struct WorldDef {
    string name;
    int medCut; // Med resolution will be 1/medCut the size of high res
    int lowCut; // Low resolution will be 1/lowCut the size of high res
    pixAlgo pixelator; // Indicates the pixelation algorithm to use
    string bck_imgName; // name of background image file
    string col_imgName; // name of collision image file
    string top_imgName; // name of top image file (or "NULL")
};

struct ItemDef {
    Sublevel world; // The world that this item should be placed into
    int x; // location of the item
    int y;
    int itemType; // Indicates the ID of the type of item this is
    string imgName; // name of image file
};

struct PortalDef { 
    Sublevel homeWorld; // The world that this portal should be placed into
    Sublevel destWorld; // The world that this portal should move the hero to
    int homeX; // location of the portal
    int homeY;
    int destX; // location the portal should move the hero to
    int destY;
    string imgName; // name of image file
};

struct EnemyDef { 
    Sublevel world; // The world that this enemy should be placed into
    int x; // start location of the enemy
    int y;
    int speed;
    int enemyType; // Indicates the ID of the type of enemy this is
    string imgName; // name of image file
};

struct HeroDef {
    Sublevel world; // The world that this hero should be placed into
    int x; // start location of the hero
    int y;
    int speed;
    int hitPoints;
    bool invincible;
    string imgName; // name of image file
};

class Configurations {

public:
    vector<WorldDef> worlds;
    vector<ItemDef> items;
    vector<PortalDef> portals;
    vector<EnemyDef> enemies;
    HeroDef hero;

    Configurations();
    bool readInConfigurations(const char *fileName);
    void readInWorlds(ifstream &file);
    void readInHero(ifstream &file);
    void readInItems(ifstream &file);
    void readInPortals(ifstream &file);
    void readInEnemies(ifstream &file);
};

