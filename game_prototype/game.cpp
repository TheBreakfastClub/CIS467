#include <cstdlib>
#include "game.h"

#define LOCATION_DIM 16
#define GRID_X 50
#define GRID_Y 50


Game::Game(int dim_x, int dim_y) 
	: grid(dim_x, dim_y)
{
	running = true;
}

/* Update game logic at each iteration of the loop */
void Game::update()
{
	// check for collision, events, etc. TODO: Move this stuff (generally) to engine
}

/* Render graphics to the screen */
void Game::draw()
{
	//Clear screen 
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); 
	SDL_RenderClear(renderer);

	// - create Drawable class, to store sprites and other assets for drawing
	// - create a map of (key: const Entity &e, value: Drawable d)

	// Draw grid -- TODO: move this into graphics engine
	for (int x = 0; x < grid.dim_x; x++) {
		for (int y = 0; y < grid.dim_y; y++) {
			SDL_Rect location_rect = {x * LOCATION_DIM, y * LOCATION_DIM, LOCATION_DIM, LOCATION_DIM};
			int r = rand() % 256;
			int g = rand() % 256;
			int b = rand() % 256;
			SDL_SetRenderDrawColor(renderer, r, g, b, 255);
			SDL_RenderFillRect(renderer, &location_rect);
		}
	}
	SDL_RenderPresent(renderer);

	//SDL_UpdateWindowSurface(window);
}

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
		draw();
		handle_input();
		update();
		SDL_Delay(30);
	}
	return 0;
}

bool Game::setup()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	// Create the SDL window and a surface to draw on
	window = SDL_CreateWindow("RAD GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
							   GRID_X * LOCATION_DIM, GRID_Y * LOCATION_DIM, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}
	screen = SDL_GetWindowSurface(window);

	// Instantiate a renderer for drawing geometric primitives
	renderer = SDL_CreateRenderer(window, -1, 0);

	return true;
}

void Game::cleanup()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	Game game(GRID_X, GRID_Y);
	if (!game.setup()) {
		return 1;
	}

	int signal = game.run();
	game.cleanup();
	return signal;
}