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
#define COLLISION_IMG "resources/test4cl.png"
#define TOP_IMG NULL

// The default constructor
Game::Game() : world("The Hub") {
	gameIsRunning = true;
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
    			case SDLK_UP:
    				std::cout << "UP\n";
                    world.next_resolution();
    				break;
    			case SDLK_DOWN:
    				std::cout << "DOWN\n";
                    world.prev_resolution();
    				break;
    			case SDLK_RIGHT:
    				std::cout << "RIGHT\n";
    				break;
    			case SDLK_LEFT:
    				std::cout << "LEFT\n";
    				break;
    			default:
    				std::cout << "INPUT: Unhandled input\n";
    		}
    	}
    }
}

/* Main game loop */
int Game::run()
{
	while (gameIsRunning) {
        graphics.drawGameWorld(world, 0, 0);
        graphics.refreshScreen();
		handle_input();
		update();
		SDL_Delay(30);
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

