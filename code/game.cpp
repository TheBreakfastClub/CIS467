/*********************************************************
File Name:	    game.cpp
Author:		    The Breakfast Club
Description:    The main controller of the game.
************************************************************/

#include "game.h"
#include "engine/world_definition/enemy.h"
#include "engine/world_definition/autoSentry.h"

#define GAME_NAME "One Rad Waffle Game"
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

// The default constructor
Game::Game() : universe(GAME_NAME), clock() 
{
	gameIsRunning = true;
	xMomentum = 0;
	yMomentum = 0;
	maxXMomentum = 50;
	maxYMomentum = 50;
	nonButterMomentum = 1;
	momentumIncrease = 1;
}

/* Update game logic at each iteration of the loop */
void Game::update()
{

    // Let each enemy take its turn
    for (Enemy *e : universe.currentWorld->enemies)
      e->action();

    // Check for hit status (not sure on this implementation)
    if (universe.hero.hit && !clock.has_event("herohit")) {
        clock.add_event(new AnonEvent(1, [&](){
            universe.hero.hit = false;
        }), "herohit");
	
	if (universe.hero.getHitPoints() <= 0 )
	{
	  graphics.message("YOU DIED!");
	  for(int i = 0; i<Sublevel::COUNT; i++){
	      universe.sublevels[i]->enemies.clear();
	      universe.sublevels[i]->portals.clear();
	      universe.sublevels[i]->items.clear();
	  }
	  universe.hero.bag.clear(); //emptying out the hero's inventory

	  //Change the level to the starting level
	  universe.changeWorld(Sublevel::HUB, Resolution::LOW, universe.hero.x, universe.hero.y);
	  if (!universe.init(config)) {
	      std::cerr << "Error initializing game universe\n";
	      exit(0);
	  }
	  
	}
	
    }
    if (universe.hero.bag.size() >=6) //can't have all items if you have less than 6 items
    { //Since the hero can have multiple eggs, we have to check all items in the inventory.
      int egg = 0;
      int flour = 0;
      int bakingPowder = 0;
      int milk = 0;
      int sugar = 0;
      int butter = 0;
      for(int i = 0; i<universe.hero.bag.size(); i++)
      {
	  if (universe.hero.bag[i]->name.find("egg")!= std::string::npos) egg = 1;
	  if (universe.hero.bag[i]->name.find("milk")!=std::string::npos) milk = 1;
	  if (universe.hero.bag[i]->name.find("sugar")!=std::string::npos) sugar = 1;
	  if (universe.hero.bag[i]->name.find("baking_powder") !=std::string::npos) bakingPowder = 1;
	  if (universe.hero.bag[i]->name.find("butter")!=std::string::npos) butter = 1;
	  if (universe.hero.bag[i]->name.find("flour")!=std::string::npos) flour = 1;
	  
      }
      if (egg+milk+sugar+bakingPowder+butter+flour == 6)
      {
	  graphics.message("YOU WIN!!!!");
	  for(int i = 0; i<Sublevel::COUNT; i++){
	      universe.sublevels[i]->enemies.clear();
	      universe.sublevels[i]->portals.clear();
	      universe.sublevels[i]->items.clear();
	  }
	  universe.hero.bag.clear(); //emptying out the hero's inventory
	  //universe.
	  //Change the level to the starting level
	  if (!universe.init(config)) {
	      std::cerr << "Error initializing game universe\n";
	      exit(0);
	  }
	  universe.changeWorld(Sublevel::HUB, Resolution::HIGH, universe.hero.x, universe.hero.y);
      }
    }

    universe.checkCollisionsWithItems();
    universe.checkCollisionsWithPortal();
}

/**
 * This method handles the inputs from the keyboard.
 * Make sure that the Graphics Engine has been initialized
 * before calling this method.
 */
void Game::handle_input()
{
    bool enableSliding;
    double levelXMomentum;
    double levelYMomentum;
    if(universe.currentWorld->worldName == "butter")
    {
      enableSliding = true;
    }
    else
    {
      enableSliding = false;
    }
   
//     // Get max height and width to pan to
//     int h = universe.currentWorld->h - 1;// - WINDOW_HEIGHT;
//     int w = universe.currentWorld->w - 1;// - WINDOW_WIDTH;

    // Grab reference to the keys
    u8 *keys = (u8*)SDL_GetKeyboardState(0);
    
    // Handle non-movement keyboard events
	SDL_Event event;
	while(SDL_PollEvent(&event)) {

		// Quit (through close window decoration)
    	if (event.type == SDL_QUIT) {
    		gameIsRunning = false;
    		return;
    	}

    	// Keyboard
    	else if (event.type == SDL_KEYDOWN) {
    		switch (event.key.keysym.sym) {
                case SDLK_p:
                    cout << "X,Y = " << universe.hero.x << "," << universe.hero.y << endl;
                    break;
                case SDLK_KP_PLUS:
                case SDLK_PLUS:
                case SDLK_0:
                case SDLK_d:
                    universe.currentWorld->next_resolution();
                    break;
                case SDLK_KP_MINUS:
                case SDLK_MINUS:
                case SDLK_9:
                case SDLK_a:
                    universe.currentWorld->prev_resolution();
                    break;
		    
		case SDLK_h:
		  if(universe.hero.getHitPoints() > 0)
		  {
              int maxHitPoints = universe.hero.maxHitPoints;

		      for(int iterator = 0; iterator < universe.hero.bag.size() && universe.hero.getHitPoints() != maxHitPoints; iterator++)
		      {
		            if((universe.hero.bag[iterator]->name.find("milk") != std::string::npos) && universe.hero.bag[iterator]->obtainable) {
		      
      			        universe.hero.bag[iterator]->obtainable = false;
			            graphics.message("Milk Used");
			            universe.hero.changeHitPoints(maxHitPoints/2);
			            if (universe.hero.getHitPoints() > maxHitPoints)
			                universe.hero.setHitPoints(maxHitPoints);
		            }
		      }
		  }
		  break;
        case SDLK_i:
		  cout << "Items in bag:\n";
		  for(int i = 0; i<universe.hero.bag.size(); i++)
		  {
		      cout << universe.hero.bag[i]->name <<endl;
		  }
		  
		  cout << "Crystal Number: " << universe.hero.crystals.size() << endl;
		  
                    break;
		case SDLK_l:
		    cout <<"Level: " <<universe.currentWorld->worldName << endl;
		    break;
                case SDLK_q:
                case SDLK_e:
                case SDLK_ESCAPE:
                    gameIsRunning = false;
                    break;
                case SDLK_1:
                    universe.changeWorld(Sublevel::HUB, universe.currentWorld->currentResLevel, universe.hero.x, universe.hero.y);
                    break; 
                case SDLK_2:
                    universe.changeWorld(Sublevel::FLOUR, universe.currentWorld->currentResLevel, universe.hero.x, universe.hero.y);
                    break;
                case SDLK_3:
                    universe.changeWorld(Sublevel::SUGAR, universe.currentWorld->currentResLevel, universe.hero.x, universe.hero.y);
                    break;
                case SDLK_4:
                    universe.changeWorld(Sublevel::BAKING_SODA, universe.currentWorld->currentResLevel, universe.hero.x, universe.hero.y);
                    break;
                case SDLK_5:
                    universe.changeWorld(Sublevel::BUTTER, universe.currentWorld->currentResLevel, universe.hero.x, universe.hero.y);
                    break;
    		}
    	}
    }
    
    if(!enableSliding) //if the level doesn't have sliding
    {
      
      levelXMomentum = 1;
      levelYMomentum = 1;
      
      if(keys[SDL_SCANCODE_UP] && !keys[SDL_SCANCODE_DOWN]) yMomentum = -1;
      if(keys[SDL_SCANCODE_DOWN] && !keys[SDL_SCANCODE_UP]) yMomentum = 1;
      if(keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT]) xMomentum = -1;
      if(keys[SDL_SCANCODE_RIGHT] && !keys[SDL_SCANCODE_LEFT]) xMomentum = 1;
    }
    
    else
    {
      levelXMomentum = maxXMomentum;
      levelYMomentum = maxYMomentum;
    
      if(keys[SDL_SCANCODE_UP] && !keys[SDL_SCANCODE_DOWN]) //if the keypress is up
      {
	  if(yMomentum > -maxYMomentum)
	      yMomentum-=momentumIncrease;
      }
      else if(keys[SDL_SCANCODE_DOWN] && !keys[SDL_SCANCODE_UP]) //if the keypress is down
      {
	if(yMomentum < maxYMomentum)
	  yMomentum +=momentumIncrease;
      }
      else {

	if(yMomentum > 0) yMomentum--;
	if(yMomentum < 0) yMomentum++;
      }
      if(keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT]) //if the keypress is left
      {
	if(xMomentum > -maxXMomentum)
	  xMomentum -=momentumIncrease;
      }
      else if(keys[SDL_SCANCODE_RIGHT] && !keys[SDL_SCANCODE_LEFT]) //if the keypress is right
      {
	if(xMomentum < maxXMomentum)
	  xMomentum +=momentumIncrease;
      }
      else {
	if(xMomentum > 0) xMomentum--;
	if(xMomentum < 0) xMomentum++;
      }
    }
    
    // Handle keyboard events
    int dx = 0, dy = 0;
    int speed = universe.hero.speed;
    double xMomPer = ((double)abs(xMomentum)) / levelXMomentum;
    double yMomPer = ((double)abs(yMomentum)) / levelYMomentum;
    double maxMomPer = 1.0;
    if (xMomPer > yMomPer) maxMomPer = xMomPer;
    else maxMomPer = yMomPer;
    speed = (int) speed * maxMomPer;

    //process movements keys multiple times, depending on speed
    for(int i = 0; i < speed; ++i) {
        if(yMomentum < 0) dy = -1;
        if(yMomentum > 0) dy = 1;
        if(xMomentum < 0) dx = -1;
        if(xMomentum > 0) dx = 1;

        universe.hero.turn(dx,dy);

        if(dx && dy) {
          if(!universe.hero.move(dx, dy))
            if(!universe.hero.move(dx, 0))
              universe.hero.move(0, dy);
        }
        else if(dx) {
          if(!universe.hero.move(dx, 0))
            if(!universe.hero.move(dx, -1))
              universe.hero.move(dx, 1);
        }
        else if(dy) {
          if(!universe.hero.move(0, dy))
            if(!universe.hero.move(-1, dy))
              universe.hero.move(1, dy);
        }
    }
    
    int w = universe.currentWorld->currentRes->mapImg->w * universe.currentWorld->scale[universe.currentRes()];
    int h = universe.currentWorld->currentRes->mapImg->h * universe.currentWorld->scale[universe.currentRes()];
    if (universe.hero.y < 0) universe.hero.y = 0;
    else if (universe.hero.y > h) universe.hero.y = h;
    if (universe.hero.x < 0) universe.hero.x = 0;
    else if (universe.hero.x > w) universe.hero.x = w;
    
    if (!enableSliding) {
      xMomentum = yMomentum = 0;
    }
}

/* Main game loop */
int Game::run()
{
	while (gameIsRunning) {
    graphics.drawGameUniverse(universe);
    graphics.refreshScreen();
		handle_input();
		update();
		clock.tick();
	}
	return 0;
}

/**
 * This function sets up the needed components for the game to run
 * and returns true if setup completed error free, false otherwise.
 *
 * @param gameName The name of the game to display on the game's window.
 * @param width The width of the game's window.
 * @param height The height of the game's window.
 * @param pathPrefix Prefix to prepend to each pathname (for loading images, etc)
 * @param configFileName Name of configuration file to load
 * @return True if setup was completed successfully, false otherwise.
 */
bool Game::setup(const char *gameName, int width, int height, const char *pathPrefix, const char *configFileName)
{
    // Load configurations
    config.setPathPrefix(pathPrefix);
    if(!config.readInConfigurations(configFileName)) return false;

    // Setup the Graphics Engine
    if (!graphics.init(gameName, width, height)) {
        std::cerr << "Error initializing graphics engine\n";
        return false;
    }

    // Setup the Game Universe
    if (!universe.init(config)) {
        std::cerr << "Error initializing game universe\n";
        return false;
    }

	return true;
}

/**
 * The main method. Instantiates and runs a game.
 */
int main(int argc, char* argv[])
{
	Game game;

  #ifdef USING_MAC
    const char *pathPrefix = "/Users/thomasverstraete/Dropbox/GVSU/SeniorProjCIS467/code/CIS467/code/";
    const char *configFileName = "/Users/thomasverstraete/Dropbox/GVSU/SeniorProjCIS467/code/CIS467/code/.config";
  #else
    const char *pathPrefix = "";
    const char *configFileName = ".config";
  #endif

  if(argc > 3) {
    std::cout << "Usage: " << argv[0] << " [[pathPrefix] configFile]\n\n";
    return 1;
  }
  else if(argc == 3) {
    pathPrefix = argv[1];
    configFileName = argv[2];
  }
  else if(argc == 2)
    configFileName = argv[1];
  
  if (!game.setup(GAME_NAME, WINDOW_WIDTH, WINDOW_HEIGHT, pathPrefix, configFileName)) {
        std::cerr << "Error in setting up the game. Game is exiting.\n";
		return 1;
	}
	return game.run();
}
