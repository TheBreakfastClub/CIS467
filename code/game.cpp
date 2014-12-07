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
    collMap = NULL;
}

/**
 * This generates a copy of the current map image with all the
 * pushing enemies included. This should be used when checking for collisions
 * with the world.
 */
void Game::generateCollMap() {
    
    if (collMap) {
        delete collMap;
    }

    // Create a copy of the map containing all pushing enemies for collision
    collMap = new Image (universe.currentWorld->currentRes->mapImg->w, universe.currentWorld->currentRes->mapImg->h);
    collMap->blit(universe.currentWorld->currentRes->mapImg, 0, 0);
    for (Enemy *e : universe.currentWorld->enemies) {
        if (e->pushes)
            collMap->ablit(e->getSpriteImage(universe.currentRes()), e->x, e->y);
    }
}

/* Update game logic at each iteration of the loop */
void Game::update()
{

    // Let each enemy take its turn
    for (Enemy *e : universe.currentWorld->enemies) {
        if (e->pushes) {    
            e->action(universe.hero, universe.currentWorld->enemies, 
                universe.currentWorld->currentRes->mapImg, universe.currentRes());
        } else {
            e->action(universe.hero, universe.currentWorld->enemies, collMap, universe.currentRes());
        }
    }

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
	  //universe.
	  //Change the level to the starting level
	  universe.changeWorld(Sublevel::HUB, Resolution::LOW, universe.hero.x, universe.hero.y);
	  if (!universe.init(config)) {
	      std::cerr << "Error initializing game universe\n";
	      exit(0);
	  }
	  graphics.message("YOU DIED!"); //trying to make the message last longer
	  
	  
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
	  if (universe.hero.bag[i]->name == "resources/egg.png") egg = 1;
	  if (universe.hero.bag[i]->name == "resources/milk.png") milk = 1;
	  if (universe.hero.bag[i]->name == "resources/sugar.png") sugar = 1;
	  if (universe.hero.bag[i]->name == "resources/baking_powder.png") bakingPowder = 1;
	  if (universe.hero.bag[i]->name == "resources/butter.png") butter = 1;
	  if (universe.hero.bag[i]->name == "resources/flour.png") flour = 1;
	  
      }
      if (egg+milk+sugar+bakingPowder+butter+flour == 6)
      {
	  graphics.message("UR DA BEST!!!!");
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
   
    // Get max height and width to pan to
    int h = universe.currentWorld->h - 1;// - WINDOW_HEIGHT;
    int w = universe.currentWorld->w - 1;// - WINDOW_WIDTH;

    // Grab reference to the keys
    u8 *keys = (u8*)SDL_GetKeyboardState(0);
    
    //Determine if the screen needs to be re-drawn
    bool redraw;

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
                    universe.currentWorld->next_resolution(universe.hero);
                    break;
                case SDLK_KP_MINUS:
                case SDLK_MINUS:
                case SDLK_9:
                case SDLK_a:
                    universe.currentWorld->prev_resolution(universe.hero);
                    break;
		    
		case SDLK_h:
		  if(universe.hero.getHitPoints() > 0)
		  {
              int maxHitPoints = universe.hero.maxHitPoints;

		      for(int iterator = 0; iterator < universe.hero.bag.size() && universe.hero.getHitPoints() != maxHitPoints; iterator++)
		      {
		            if(universe.hero.bag[iterator]->name == "resources/milk.png" && universe.hero.bag[iterator]->obtainable) {
		      
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
    Image *heroImg = universe.hero.getSpriteImage(universe.currentRes());
    
    //process movements keys multiple times, depending on speed
    for(int i = 0; i < speed; ++i) {
        if(yMomentum < 0) dy = -1;
        if(yMomentum > 0) dy = 1;
        if(xMomentum < 0) dx = -1;
        if(xMomentum > 0) dx = 1;

        if(dx && dy) {
	        //checking for diagonal change
            if(!collMap->collision(heroImg, universe.hero.x+dx, universe.hero.y+dy))
    	    {
    	      universe.hero.x+=dx;
    	      universe.hero.y+=dy;
    	      redraw=true;
    	    }
    	    //checking for horizontal change
            else if(!collMap->collision(heroImg, universe.hero.x+dx, universe.hero.y)){
    	      universe.hero.x+=dx;
    	      redraw=true;
      	    }
    	    //change for vertical change
            else if(!collMap->collision(heroImg, universe.hero.x, universe.hero.y+dy)){
    	      universe.hero.y+=dy; 
    	      redraw=true;
    	    }
        }
        else if(dx) {
            if(!collMap->collision(heroImg, universe.hero.x+dx, universe.hero.y)) universe.hero.x+=dx, redraw=true;
            else if(!collMap->collision(heroImg, universe.hero.x+dx, universe.hero.y-1)) {
    	        universe.hero.x+=dx;
    	        universe.hero.y--;
    	        redraw=true;
    	    }
            else if(!collMap->collision(heroImg, universe.hero.x+dx, universe.hero.y+1)) {
    	      universe.hero.x+=dx;
    	      universe.hero.y++;
    	      redraw=true;
    	    }
        }
        else if(dy) {
            if(!collMap->collision(heroImg, universe.hero.x, universe.hero.y+dy)) universe.hero.y+=dy, redraw=true;
            else if(!collMap->collision(heroImg, universe.hero.x-1, universe.hero.y+dy)){
	            universe.hero.x--;
    	        universe.hero.y+=dy;
	        redraw=true;
	        }
            else if(!collMap->collision(heroImg, universe.hero.x+1, universe.hero.y+dy)){
        	    universe.hero.x++;
	            universe.hero.y+=dy;
	            redraw=true;
	        }
        }
    }
    
    // Update movement
    //universe.hero.x += dx;
    //universe.hero.y += dy;
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
        generateCollMap();
		handle_input();
		update();
		clock.tick();
        //std::cout << std::to_string(clock.avgFPS()) << std::endl;
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
 * @return True if setup was completed successfully, false otherwise.
 */
bool Game::setup(const char *gameName, int width, int height)
{
    // Load configurations
#ifdef USING_MAC
    if (!config.readInConfigurations("/Users/thomasverstraete/Dropbox/GVSU/SeniorProjCIS467/code/CIS467/code/util/thomas.config")) {
#else
    if (!config.readInConfigurations(".config")) {
#endif
        return false;
    }

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
	if (!game.setup(GAME_NAME, WINDOW_WIDTH, WINDOW_HEIGHT)) {
        std::cerr << "Error in setting up the game. Game is exiting.\n";
		return 1;
	}
	int signal = game.run();
	return signal;
}

