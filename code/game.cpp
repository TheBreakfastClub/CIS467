/*********************************************************
File Name:	    game.cpp
Author:		    The Breakfast Club
Description:    The main controller of the game.
************************************************************/

#include "game.h"

#define GAME_NAME "One Rad Waffle Game"
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

#define BACKGROUND_IMG "resources/background.png"
#define COLLISION_IMG "resources/fullBoardTest1.png"
#define TOP_IMG NULL

int pan_x, pan_y, step;


// The default constructor
Game::Game() : world("The Hub"), clock() 
{
	gameIsRunning = true;

    // just showing off the types of things the event timer can do...
    clock.add_event(new AutoPixEvent(&world));
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
    int h = world.h - 1 - WINDOW_HEIGHT;
    int w = world.w - 1 - WINDOW_WIDTH;

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
#if 0
    			case SDLK_UP:
                    pan_y -= step;
                    if (pan_y < 0) pan_y = 0;
    				break;
    			case SDLK_DOWN:
                    pan_y += step;
                    if (pan_y > h) pan_y = h;
    				break;
    			case SDLK_RIGHT:
                    pan_x += step;
                    if (pan_x > w) pan_x = w;
    				break;
    			case SDLK_LEFT:
                    pan_x -= step;
                    if (pan_x < 0) pan_x = 0;
    				break;
#endif
                case SDLK_KP_PLUS:
                case SDLK_PLUS:
                    world.next_resolution();
                    break;
                case SDLK_KP_MINUS:
                case SDLK_MINUS:
                    world.prev_resolution();
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
    int speed = step;
    //process movements keys multiple times, depending on speed
    for(int i = 0; i < speed; i++) {
        if(keys[SDL_SCANCODE_UP] && !keys[SDL_SCANCODE_DOWN]) dy += -1;
        if(keys[SDL_SCANCODE_DOWN] && !keys[SDL_SCANCODE_UP]) dy += 1;
        if(keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT]) dx += -1;
        if(keys[SDL_SCANCODE_RIGHT] && !keys[SDL_SCANCODE_LEFT]) dx += 1;
#if 0
        // This code will help when we start handling collisions
        // You will have to change the += above to just = though
        if(dx && dy) {
            if(!map->collision(hero, cx+dx, cy+dy)) cx+=dx, cy+=dy, redraw=true;
            else if(!map->collision(hero, cx+dx, cy)) cx+=dx, redraw=true;
            else if(!map->collision(hero, cx, cy+dy)) cy+=dy, redraw=true;
        }
        else if(dx) {
            if(!map->collision(hero, cx+dx, cy)) cx+=dx, redraw=true;
            else if(!map->collision(hero, cx+dx, cy-1)) cx+=dx, cy--, redraw=true;
            else if(!map->collision(hero, cx+dx, cy+1)) cx+=dx, cy++, redraw=true;
        }
        else if(dy) {
            if(!map->collision(hero, cx, cy+dy)) cy+=dy, redraw=true;
            else if(!map->collision(hero, cx-1, cy+dy)) cx--, cy+=dy, redraw=true;
            else if(!map->collision(hero, cx+1, cy+dy)) cx++, cy+=dy, redraw=true;
        }
#endif
    }
    
    // Update movement
    pan_x += dx;
    pan_y += dy;
    if (pan_y < 0) pan_y = 0;
    else if (pan_y > h) pan_y = h;
    if (pan_x < 0) pan_x = 0;
    else if (pan_x > w) pan_x = w;
}

/* Main game loop */
int Game::run()
{
	while (gameIsRunning) {
        graphics.drawGameWorld(world, pan_x, pan_y);
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
    // TODO: Setup a universe, rather than one world
    if (!world.init(BACKGROUND_IMG, COLLISION_IMG, TOP_IMG)) {
        std::cerr << "Error initializing game world\n";
        return false;
    }

    pan_x = pan_y = 0;
    step = 20;
    
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

