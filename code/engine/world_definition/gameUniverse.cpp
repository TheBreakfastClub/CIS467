/*********************************************************
File Name:	    gameUniverse.cpp
Author:		      The Breakfast Club
Creation Date:  09-25-2014
Description:    Holds the data defining the universe
************************************************************/

#include "gameUniverse.h"
#include <iostream> 
#include <numeric>
#include "upDownEnemy.h"
#include "leftRightEnemy.h"

/**
 * Default constructor for the universe. Must call GameUniverse::init()
 * before using the GameUniverse instance.
 */
GameUniverse::GameUniverse(string universe_name) : universeName(universe_name) 
{
  sublevels[Sublevel::HUB] = new GameWorld("hub");
  sublevels[Sublevel::FLOUR] = new GameWorld("flour");
  sublevels[Sublevel::SUGAR] = new GameWorld("sugar");
  sublevels[Sublevel::BAKING_SODA] = new GameWorld("baking_soda");
  sublevels[Sublevel::BUTTER] = new GameWorld("butter");

  currentWorld = sublevels[Sublevel::HUB];
  currentLevel = Sublevel::HUB;
}

/**
 * This method changes the game world to the provided sublevel at the
 * provided resolution. It also moves the hero to the location provided
 * by x, y
 */
void GameUniverse::changeWorld(Sublevel level, Resolution res, int x, int y) {

    if (level == currentLevel) return;

    // adjust the world reference
    currentWorld = sublevels[level];
    currentLevel = level;
    currentWorld->set_resolution(res);

    // Move the hero
    hero.x = x;
    hero.y = y;
}

/**
 * This method checks to see if the hero collides with any items
 * in the currentWorld at the current resolution. If the hero collides
 * with an item, it will pick up the first item it collides with, placing
 * it in the hero's bag and returning true.  If the hero collides with no
 * items, it returns false.
 */
bool GameUniverse::checkCollisionsWithItems() {
    
    auto it = currentWorld->items.begin();
    while (it != currentWorld->items.end()) {

        Item *item = *it;

        // Continue if item is unobtainable
        if (!item->obtainable) {
            ++it;
            continue;
        }


        // Check if item and hero collide
        Resolution res = currentRes();
        if (hero.getSpriteImage(res)->collision(item->getSpriteImage(res), hero.x - item->x, hero.y - item->y)) {
            hero.bag.push_back(item);
            it = currentWorld->items.erase(it);
            return true;
        }
        ++it;
    }
    return false;
}

bool GameUniverse::checkCollisionsWithPortal(){
  
    auto port = currentWorld->portals.begin();
    while (port != currentWorld->portals.end()) {

        Portal *portal = *port;

        // Continue if portal is unusable
        if (!portal->usable) {
            ++port;
            continue;
        }


        // Check if portal and hero collide
        Resolution res = currentRes();
        if (hero.getSpriteImage(res)->collision(portal->getSpriteImage(res), hero.x - portal->x, hero.y - portal->y)) {
            changeWorld(portal->destination, currentWorld->currentResLevel, portal->xDest, portal->yDest);
            return true;
        }
        ++port;
    }
    return false;
}

/*
bool GameUniverse::checkCollisionsWithEnemies() {

}
*/

Resolution GameUniverse::currentRes() {
    return currentWorld->currentResLevel;
}

// The deconstructor
GameUniverse::~GameUniverse() {
    if(sublevels[Sublevel::HUB])
      delete(sublevels[Sublevel::HUB]);
      
    if(sublevels[Sublevel::FLOUR])
      delete(sublevels[Sublevel::FLOUR]);
      
    if (sublevels[Sublevel::SUGAR])
      delete(sublevels[Sublevel::SUGAR]);
      
    if(sublevels[Sublevel::BAKING_SODA])
      delete(sublevels[Sublevel::BAKING_SODA]);
      
    if(sublevels[Sublevel::BUTTER])
      delete(sublevels[Sublevel::BUTTER]);
    
}

/**
 * This function initializes the game universe using the images defined in
 * gameUniverse.h as the high resolution game universe. It returns false 
 * if any errors are encountered while initializing, true otherwise.
 *
 * This method must be called before any other GameUniverse functions.
 */
bool GameUniverse::init(const Configurations &config) {

    // Gather the worlds
    vector<Sublevel> world_list(Sublevel::COUNT);
    world_list[Sublevel::HUB] = Sublevel::HUB;
    world_list[Sublevel::FLOUR] = Sublevel::FLOUR;
    world_list[Sublevel::SUGAR] = Sublevel::SUGAR;
    world_list[Sublevel::BAKING_SODA] = Sublevel::BAKING_SODA;
    world_list[Sublevel::BUTTER] = Sublevel::BUTTER;

    // Initialize the worlds
    for (Sublevel sub : world_list) {
        
        const WorldDef *world = &config.worlds[sub];
        const char *bck = world->bck_imgName.c_str();
        const char *col = world->col_imgName.c_str();
        const char *top = (world->top_imgName == "NULL" ? NULL : world->top_imgName.c_str());
        if (! sublevels[sub] -> init(bck, col, top, world->pixelator, world->medCut, world->lowCut))
            return false;
        sublevels[sub]->worldName = world->name; 

    }

    // Hub & Flower Portals

    // First to Flower
    Portal *htof1Portal = new Portal(288, 128, "Portal", true, Sublevel::FLOUR, 700, 100);
    if (!htof1Portal->setSpriteImage("resources/portal.png")) return false;
    sublevels[Sublevel::HUB]->portals.push_back(htof1Portal);

    // Second to Flower
    Portal *htof2Portal = new Portal(768, 768, "Portal", true, Sublevel::FLOUR, 860, 300);
    if (!htof2Portal->setSpriteImage("resources/portal.png")) return false;
    sublevels[Sublevel::HUB]->portals.push_back(htof2Portal);

    // First to Hub
    Portal *ftohPortal = new Portal(896, 80, "Portal", true, Sublevel::HUB, 288, 200);
    if (!ftohPortal->setSpriteImage("resources/portal.png")) return false;
    sublevels[Sublevel::FLOUR]->portals.push_back(ftohPortal);

    // Second to Hub
    Portal *ftoh2Portal = new Portal(896, 192, "Portal", true, Sublevel::HUB, 768, 700);
    if (!ftoh2Portal->setSpriteImage("resources/portal.png")) return false;
    sublevels[Sublevel::FLOUR]->portals.push_back(ftoh2Portal);


    // Hub & Sugar Portals

    // First to Sugar
    Portal *htos1Portal = new Portal(608, 128, "Portal", true, Sublevel::SUGAR, 100, 100);
    if (!htos1Portal->setSpriteImage("resources/portal.png")) return false;
    sublevels[Sublevel::HUB]->portals.push_back(htos1Portal);

    // Second to Sugar
    Portal *htos2Portal = new Portal(1248, 768, "Portal", true, Sublevel::SUGAR, 2360, 500);
    if (!htos2Portal->setSpriteImage("resources/portal.png")) return false;
    sublevels[Sublevel::HUB]->portals.push_back(htos2Portal);

    // First to Hub
    Portal *stohPortal = new Portal(64, 300, "Portal", true, Sublevel::HUB, 608, 200);
    if (!stohPortal->setSpriteImage("resources/portal.png")) return false;
    sublevels[Sublevel::SUGAR]->portals.push_back(stohPortal);

    // Second to Hub
    Portal *stoh2Portal = new Portal(2260, 550, "Portal", true, Sublevel::HUB, 1248, 700);
    if (!stoh2Portal->setSpriteImage("resources/portal.png")) return false;
    sublevels[Sublevel::SUGAR]->portals.push_back(stoh2Portal);

    



    // int hp, int speed, int damage, int x=0, int y=0, bool inv=false, Image *char_img=NULL, int dist=0, int tme=0
    UpDownEnemy *ude1 = new UpDownEnemy(50, 1, 25, 384, -100, false, 150, 0);
    if (!ude1->setSpriteImage("resources/updown1.png")) return false;
    // UpDownEnemy *ude1 = new UpDownEnemy(50, 2, 25, 550, 250, false, NULL, 30, 0);
    sublevels[Sublevel::SUGAR]->enemies.push_back(ude1);

    LeftRightEnemy *lre1 = new LeftRightEnemy(50, 1, 25, 1530, 128, false, 150, 0);
    if (!lre1->setSpriteImage("resources/leftright1.png")) return false;
    // LeftRightEnemy *lre1 = new LeftRightEnemy(50, 2, 25, 550, 250, false, NULL, 30, 0);
    sublevels[Sublevel::SUGAR]->enemies.push_back(lre1);

    // int hp, int speed, int damage, int x=0, int y=0, bool inv=false, Image *char_img=NULL, int dist=0, int tme=0
    UpDownEnemy *ude2 = new UpDownEnemy(50, 1, 25, 1666, 150, false, 150, 0);
    if (!ude2->setSpriteImage("resources/updownsingleR.png")) return false;
    // UpDownEnemy *ude2 = new UpDownEnemy(50, 2, 25, 550, 250, false, NULL, 30, 0);
    sublevels[Sublevel::SUGAR]->enemies.push_back(ude2);

    UpDownEnemy *ude3 = new UpDownEnemy(50, 1, 25, 1742, 300, false, 150, 0);
    if (!ude3->setSpriteImage("resources/updownsingle.png")) return false;
    // UpDownEnemy *ude3 = new UpDownEnemy(50, 2, 25, 550, 250, false, NULL, 30, 0);
    sublevels[Sublevel::SUGAR]->enemies.push_back(ude3);

    // 417


    // Define the Hero
    if (!(hero.setSpriteImage(config.hero.imgName.c_str()))) return false;
    if (!(hero.hitImage = redTint(hero.getSpriteImage(Resolution::HIGH), 150))) return false;
    hero.x = config.hero.x;
    hero.y = config.hero.y;
    hero.speed = config.hero.speed;
    hero.hitPoints = config.hero.hitPoints;
    hero.invincible = config.hero.invincible;
    return true;
}
