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
#include "dumbSentry.h"

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
    
    // the set_resolution routine shuffles world objects around as needed in little-big mode
    // it is therefore important to preserve order of operations here...
    
    // shuffles everything back to "normal" in the old world (little-big)
    currentWorld->set_resolution(HIGH);

    // Move the hero *before* setting resolution in the new world
    hero.x = x;
    hero.y = y;

    // adjust the world reference
    currentWorld = sublevels[level];
    currentLevel = level;
    // if we are low-res + little-big, the character's coordinates will be adjusted appropriately
    currentWorld->set_resolution(res);
    

    // all Objects (including the hero) need a pointer to their current world
    hero.world = currentWorld;
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
        if(hero.within(.7, item)) {
            
          if(item->name.find("crystal") != std::string::npos)
          {
            hero.crystals.push_back(item);
            it = currentWorld->items.erase(it);
            return true;
          }
          else
          {  
            hero.bag.push_back(item);
            it = currentWorld->items.erase(it);
                  return true;
          }
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
        if(hero.within(.4, portal)) {
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
        
        if (!sublevels[sub] -> init(bck, col, top, &hero, world->pixelator, world->medCut, world->lowCut))
            return false;
        sublevels[sub]->worldName = world->name; 

    }

    // Initialize the items
    for(ItemDef i : config.items) {
        GameWorld *w = sublevels[i.world];
        Item *newItem = new Item(i.x, i.y, w, i.solid, i.pushable, i.imgName);
        if (!newItem->loadImage(i.imgName.c_str(), w->medCut, w->lowCut)) return false;
        w->items.push_back(newItem);
    }
    
    // Initialize the portals
    for(PortalDef p : config.portals) {
        GameWorld *w = sublevels[p.homeWorld];
        Portal *newPortal = new Portal(p.homeX, p.homeY, w, "<portal>", true, p.destWorld, p.destX, p.destY);
        if (!newPortal->loadImage(p.imgName.c_str(), w->medCut, w->lowCut)) return false;
        w->portals.push_back(newPortal);
    }

    // Initialize the enemies
    for (EnemyDef e : config.enemies) {
        GameWorld *w = sublevels[e.world];
        if (e.enemyType == STATIC_ENEMY) {
            StaticEnemy *enemy = new StaticEnemy(e.x, e.y, w, e.touchDamage);
            if (!enemy->loadImage(e.imgName.c_str(), w->medCut, w->lowCut)) return false;
            w->enemies.push_back(enemy);
        }
        else if (e.enemyType == AUTO_SENTRY) {
            AutoSentry *enemy = new AutoSentry(e.x, e.y, w, e.solid, e.pushable,
              e.pushes, e.speed, e.touchDamage, e.crushDamage);
            if (!enemy->loadImage(e.imgName.c_str(), w->medCut, w->lowCut, true)) return false;
            enemy->pathfinder.set_grid(&(w->grid));
            w->enemies.push_back(enemy);
        }
        else if (e.enemyType == UP_DOWN) {
            UpDownEnemy *enemy = new UpDownEnemy(e.x, e.y, w, e.speed, 
              e.touchDamage, e.crushDamage, e.range);
            if (!enemy->loadImage(e.imgName.c_str(), w->medCut, w->lowCut)) return false;
            w->enemies.push_back(enemy);
        }
        else if (e.enemyType == LEFT_RIGHT) {
            LeftRightEnemy *enemy = new LeftRightEnemy(e.x, e.y, w, e.speed, 
              e.touchDamage, e.crushDamage, e.range);
            if (!enemy->loadImage(e.imgName.c_str(), w->medCut, w->lowCut)) return false;
            w->enemies.push_back(enemy);
        }
				else if (e.enemyType == DUMB_SENTRY) {
						DumbSentry *enemy = new DumbSentry(e.x, e.y, w, e.solid, e.pushable, 
              e.pushes, e.speed, e.touchDamage, e.crushDamage);
            if (!enemy->loadImage(e.imgName.c_str(), w->medCut, w->lowCut, true)) return false;
            w->enemies.push_back(enemy);
        }

    }

    // Define the Hero
    hero.x = config.hero.x;
    hero.y = config.hero.y;
    hero.world = sublevels[config.hero.world];
    hero.speed = config.hero.speed;
    hero.setHitPoints(config.hero.hitPoints);
    hero.invincible = config.hero.invincible;
    hero.pushes = config.hero.pushes;
    if(!hero.loadImage(config.hero.imgName.c_str(), hero.world->medCut, hero.world->lowCut, true))
      return false;
    return true;
}
