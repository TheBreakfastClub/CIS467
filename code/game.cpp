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
    int h = world.h - 1 - WINDOW_HEIGHT;
    int w = world.w - 1 - WINDOW_WIDTH;

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
        graphics.drawGameWorld(world, pan_x, pan_y);
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

