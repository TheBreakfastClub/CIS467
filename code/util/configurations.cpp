/*********************************************************
File Name:	    configurations.cpp
Author:				Steven Hoffman
Creation Date:  11-07-2014
Description:	  
************************************************************/

#include "configurations.h"

Configurations::Configurations() {}

/**
 * Reads in the configurations from the file specified, returning
 * false if there were errors
 *
 * Format:
 * For each world (in the order given in Sublevel.h)
 *      world_name
 *      background_image_name
 *      collision_image_name
 *      top_image_name (or "NULL")
 *      medCut lowCut
 *      pixAlg
 *      . //Dividing line to make more human readable; you can put anything here
 * -- // Dividing line between sections; must be "--"
 * For the Hero:
 *      world_id (the int for the enum describing the world from sublevel.h)
 *      x y
 *      speed  max_hit_points 
 *      invincible (put a 0 for not invincible, 1 for invincible)
 *      img_name
 * --
 * For each Item:
 *      world_id (the int for the enum describing the world from sublevel.h)
 *      x y
 *      item_id
 *      img_name
 *      .
 * --
 * portal_img_name
 * .
 * For each Portal:
 *      home_world_id (home = where the portal is located)
 *      homeX homeY
 *      dest_world_id (dest = where the portal should take you)
 *      destX destY
 *      .
 * --
 * For each enemy:
 *      world_id
 *      x y
 *      speed
 *      enemy_id
 *      imgName
 *      .
 * --
 */
bool Configurations::readInConfigurations(const char *fileName) {

    // Open file
    ifstream file (fileName);
    if (!file.good()) return false;
   
    readInWorlds(file);
    readInHero(file);
    readInItems(file);
    readInPortals(file);
    readInEnemies(file);

    file.close();
    return true;
}

string sublevelToStr(const Sublevel &world) {

        string worldName;
        switch (world) {

        case Sublevel::HUB:
            worldName = "HUB";
            break;
        case Sublevel::FLOUR:
            worldName = "FLOUR";
            break;
        case Sublevel::SUGAR:
            worldName = "SUGAR";
            break;
        case Sublevel::BAKING_SODA:
            worldName = "BAKING_SODA";
            break;
        case Sublevel::BUTTER:
            worldName = "BUTTER";
            break;
        case Sublevel::COUNT:
            worldName = "VOID";
            break;
        }
        return worldName;
}

#if 0
int main (void) {
    
    Configurations config;
    config.readInConfigurations("config.example");

    // Print worlds
    for (WorldDef w : config.worlds) {
       cout << w.name << endl; 
       cout << w.bck_imgName << endl; 
       cout << w.col_imgName << endl; 
       cout << w.top_imgName << endl; 
       cout << w.medCut << " " << w.lowCut << endl;
       cout << w.pixAlg << endl;
       cout << "." << endl;
    }
    cout << "======================" << endl;
   
    // Print hero
    cout << sublevelToStr(config.hero.world) << endl;
    cout << config.hero.x << " " << config.hero.y << endl;
    cout << config.hero.speed << " " << config.hero.hitPoints << endl;
    cout << (config.hero.invincible ? "Invincible" : "Not Invincible") << endl;
    cout << config.hero.imgName << endl;
    cout << "======================" << endl;

    // Print items
    for (ItemDef i : config.items) {
        
        cout << sublevelToStr(i.world) << endl;
        cout << i.x << " " << i.y << endl;
        cout << i.itemType << endl;
        cout << i.imgName << endl;
        cout << "." << endl;
    }
    cout << "======================" << endl;

    // Print Portals
    cout << config.portals[0].imgName << endl << "." << endl;
    for (PortalDef p : config.portals) {
        cout << sublevelToStr(p.homeWorld) << endl;
        cout << p.homeX << " " << p.homeY << endl;
        cout << sublevelToStr(p.destWorld) << endl;
        cout << p.destX << " " << p.destY << endl;
        cout << "." << endl;
    }
    cout << "======================" << endl;

    // Print Enemies
    for (EnemyDef e : config.enemies) {
        cout << sublevelToStr(e.world) << endl;
        cout << e.x << " " << e.y << endl;
        cout << e.speed << endl;
        cout << e.enemyType << endl;
        cout << e.imgName << endl;
    }
    cout << "======================" << endl;
}
#endif

void Configurations::readInWorlds(ifstream &file) {

    string line;

    // Gather the worlds
    vector<Sublevel> world_list(Sublevel::COUNT);
    world_list[Sublevel::HUB] = Sublevel::HUB;
    world_list[Sublevel::FLOUR] = Sublevel::FLOUR;
    world_list[Sublevel::SUGAR] = Sublevel::SUGAR;
    world_list[Sublevel::BAKING_SODA] = Sublevel::BAKING_SODA;
    world_list[Sublevel::BUTTER] = Sublevel::BUTTER;

    // Read in the world data
    for (auto iter = world_list.begin(); iter != world_list.end(); ++iter) {

        WorldDef world;
        getline(file, world.name);
        getline(file, world.bck_imgName);
        getline(file, world.col_imgName);
        getline(file, world.top_imgName);
 
        getline(file, line);
        stringstream ss(line);
        ss >> world.medCut;
        ss >> world.lowCut;

        int pixAlgoIdx;
        getline(file, line);
        stringstream ss2(line);
        ss2 >> pixAlgoIdx;
        world.pixelator = PixUtil::getPixAlgoFromIdx(pixAlgoIdx);

        worlds.push_back(world);
        getline(file, line); // Read in dividing line
    }
    getline(file,line); // Read in dividing line
}

void Configurations::readInEnemies(ifstream &file) {

    string line;

    // Read in Enemy info
    getline(file, line);
    while (line != "--") {
        
        EnemyDef enemy;

        int type;
        stringstream ss(line);
        ss >> type;
        enemy.world = (Sublevel) type;

        getline(file, line);
        stringstream ss2(line);
        ss2 >> enemy.x;
        ss2 >> enemy.y;

        getline(file, line);
        stringstream ss3(line);
        ss3 >> enemy.speed;

        getline(file, line);
        stringstream ss4(line);
        ss4 >> enemy.enemyType;

        getline(file, enemy.imgName);
        enemies.push_back(enemy);

        getline(file, line); // Read in dividing line
        getline(file, line); // Read in next line for processing in next loop
    }
}

void Configurations::readInPortals(ifstream &file) {
    
    string line;

    // Read in portal info
    string portalImgName;
    getline(file, portalImgName);
    getline(file, line); // Read in dividing line
    getline(file, line);
    while (line != "--") {
    
        PortalDef portal;
        portal.imgName = portalImgName;

        int type;
        stringstream ss(line);
        ss >> type;
        portal.homeWorld = (Sublevel) type;

        getline(file, line);
        stringstream ss2(line);
        ss2 >> portal.homeX;
        ss2 >> portal.homeY;

        getline(file, line);
        stringstream ss3(line);
        ss3 >> type;
        portal.destWorld = (Sublevel) type;

        getline(file, line);
        stringstream ss4(line);
        ss4 >> portal.destX;
        ss4 >> portal.destY;

        portals.push_back(portal);
        getline(file, line); // Read in dividing line
        getline(file, line); // Read in next line for processing in next loop
    }
}

void Configurations::readInHero(ifstream &file) {
    
    string line;

    // Read in hero details
    int type;
    getline(file, line);
    stringstream ss(line);
    ss >> type;
    hero.world = (Sublevel) type;
    
    getline(file, line);
    stringstream ss2(line);
    ss2 >> hero.x;
    ss2 >> hero.y;

    getline(file, line);
    stringstream ss3(line);
    ss3 >> hero.speed;
    ss3 >> hero.hitPoints;
    
    getline(file, line);
    stringstream ss4(line);
    hero.invincible = (line != "0");

    getline(file, hero.imgName);
    getline(file, line); // Read in dividing line
}

void Configurations::readInItems(ifstream &file) {

    // Read in items
    string line;
    getline(file, line);
    while (line != "--") {
        
        ItemDef item;

        stringstream ss(line);
        int type;
        ss >> type;
        item.world = (Sublevel) type;

        getline(file, line);
        stringstream ss2(line);
        ss2 >> item.x;
        ss2 >> item.y;

        getline(file, line);
        stringstream ss3(line);
        ss3 >> item.itemType;

        getline(file, item.imgName);
        items.push_back(item);

        getline(file, line); // Read in dividing line
        getline(file, line); // Read in next line for processing in next loop
    }

}

