/**
 * The main controller of the game.
 */

#include <cstdlib>
#include "game.h"

#define TILE_DIM 16
#define GRID_X 50
#define GRID_Y 50


Game::Game(int dim_x, int dim_y) 
	: world(dim_x, dim_y, TILE_DIM, dim_x, dim_y), drawing()
{
	running = true;
	//z = 0;
}

/* Update game logic at each iteration of the loop */
void Game::update()
{
	// check for collision, events, etc. TODO: Move this stuff (generally) to engine
}

// TESTING event timing
//Uint32 Game::inc_z(Uint32 interval, void* param)
//{
//	z++;
//	return 1000;
//}

void Game::handle_input()
{
	SDL_Event event;
	while(SDL_PollEvent(&event)) {

		// Quit (through close window decoration)
    	if (event.type == SDL_QUIT) {
    		running = false;
    		return;
    	}

    	// Keyboard
    	else if (event.type == SDL_KEYDOWN) {
    		switch (event.key.keysym.sym) {
    			case SDLK_UP:
    				std::cout << "UP\n";
    				break;
    			case SDLK_DOWN:
    				std::cout << "DOWN\n";
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
	while (running) {
		drawing.draw_world(world);
		handle_input();
		update();
		SDL_Delay(1000);
	}
	return 0;
}

bool Game::setup()
{
	return drawing.setupSDL(GRID_X * TILE_DIM, GRID_Y * TILE_DIM);
}

void Game::cleanup()
{
	// probably not necessary since each specific part of the engine cleans itself up. thoughts?
    /**
     * Steven's Thoughts: may not be important now. But if Game ever
     * allocates its own data, it will have to deallocate. We can always
     * re-add the cleanup method then, or just deallocate directly in
     * Game's destructor.
     */
}

int main(int argc, char* argv[])
{
	Game game(GRID_X, GRID_Y);
	if (!game.setup()) {
        std::cerr << "Error in setting up the game. Game is exiting.\n";
		return 1;
	}

	int signal = game.run();
	game.cleanup();
	return signal;
}
