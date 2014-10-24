/*********************************************************
File Name:	    game.cpp
Author:		    The Breakfast Club
Description:    The main controller of the game.
************************************************************/

#include "game.h"

#define GAME_NAME "One Rad Waffle Game"
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

// The default constructor
Game::Game() : universe(GAME_NAME), clock() 
{
	gameIsRunning = true;

    // just showing off the types of things the event timer can do...
    // clock.add_event(new AutoPixEvent(&world));
}

/* Update game logic at each iteration of the loop */
void Game::update()
{
	// check for collision, events, etc. 
    // TODO: Move this stuff (generally) to engine
}

/**
 * This method handles the inputs from the keyboard.
 * Make sure that the Graphics Engine has been initialized
 * before calling this method.
 */
void Game::handle_input()
{
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
                case SDLK_KP_PLUS:
                case SDLK_PLUS:
                case SDLK_2:
                    universe.currentWorld->next_resolution();
                    break;
                case SDLK_KP_MINUS:
                case SDLK_MINUS:
                case SDLK_1:
                    universe.currentWorld->prev_resolution();
                    break;
                case SDLK_i:
                    cout << "Items in bag: " << universe.hero.bag.size() << endl;
                    break;
                case SDLK_q:
                case SDLK_e:
                case SDLK_ESCAPE:
                    gameIsRunning = false;
                    break;
    		}
    	}
    }
    
    // Handle keyboard events
    int dx = 0, dy = 0;
    int speed = universe.hero.speed;
    Image *map = universe.currentWorld->currentRes->mapImg;
    //process movements keys multiple times, depending on speed
    for(int i = 0; i < speed; ++i) {
        if(keys[SDL_SCANCODE_UP] && !keys[SDL_SCANCODE_DOWN]) dy = -1;
        if(keys[SDL_SCANCODE_DOWN] && !keys[SDL_SCANCODE_UP]) dy = 1;
        if(keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT]) dx = -1;
        if(keys[SDL_SCANCODE_RIGHT] && !keys[SDL_SCANCODE_LEFT]) dx = 1;

        // This code will help when we start handling collisions
        // You will have to change the += above to just = though
        if(dx && dy) {
	    //checking for diagonal change
            if(!map->collision(universe.hero.spriteImage, universe.hero.x+dx, universe.hero.y+dy))
	    {
	      universe.hero.x+=dx;
	      universe.hero.y+=dy;
	      redraw=true;
	    }
	    //checking for horizontal change
            else if(!map->collision(universe.hero.spriteImage, universe.hero.x+dx, universe.hero.y)){
	      universe.hero.x+=dx;
	      redraw=true;
	    }
	    //change for vertical change
            else if(!map->collision(universe.hero.spriteImage, universe.hero.x, universe.hero.y+dy)){
	      universe.hero.y+=dy; 
	      redraw=true;
	    }
        }
        else if(dx) {
            if(!map->collision(universe.hero.spriteImage, universe.hero.x+dx, universe.hero.y)) universe.hero.x+=dx, redraw=true;
            else if(!map->collision(universe.hero.spriteImage, universe.hero.x+dx, universe.hero.y-1)){
	      universe.hero.x+=dx;
	      universe.hero.y--;
	      redraw=true;
	    }
            else if(!map->collision(universe.hero.spriteImage, universe.hero.x+dx, universe.hero.y+1)){
	      universe.hero.x+=dx;
	      universe.hero.y++;
	      redraw=true;
	    }
        }
        else if(dy) {
            if(!map->collision(universe.hero.spriteImage, universe.hero.x, universe.hero.y+dy)) universe.hero.y+=dy, redraw=true;
            else if(!map->collision(universe.hero.spriteImage, universe.hero.x-1, universe.hero.y+dy)){
	      universe.hero.x--;
	      universe.hero.y+=dy;
	      redraw=true;
	    }
            else if(!map->collision(universe.hero.spriteImage, universe.hero.x+1, universe.hero.y+dy)){
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

    universe.checkCollisionsWithItems();
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
    // Setup the Graphics Engine
    if (!graphics.init(gameName, width, height)) {
        std::cerr << "Error initializing graphics engine\n";
        return false;
    }

    // Setup the Game Universe
    if (!universe.init()) {
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

