/**
 * This class handles the main elements of the graphics engine.
 */

#include "drawing.h"
#include <iostream>

/**
 * The constructor. You must call setupSDL() before using any SDL functionality.
  */
Drawing::Drawing(){

    // Set SDL Members to NULL for now
    window = NULL;
    screen = NULL;
    renderer = NULL;               
}

/**
 * The destructor. It frees up SDL objects and quits SDL.
 */
Drawing::~Drawing(){

    // Deallocate SDL Members and quit SDL
    cleanupSDL();
}


/**
 * This function initializes the necessary SDL members, returning
 * true if there were no errors, false if there were errors.
 */
bool Drawing::setupSDL(int screen_width, int screen_height)
{
	// Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

	// Create the SDL window and a surface to draw on
	window = SDL_CreateWindow("RAD GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
							   screen_width, screen_height, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}

	screen = SDL_GetWindowSurface(window);
	if (screen == NULL) {
		std::cout << "SDL_GetWindowSurface Error: " << SDL_GetError() << std::endl;
		return false;
	}

	// Instantiate a renderer for drawing geometric primitives
	/*if (!drawing.set_renderer(SDL_CreateRenderer(window, -1, 0))) {
		if (!drawing.set_renderer(SDL_GetRenderer(window))) { // <-- WHAT?!
			std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
			return false;
		}
	}*/
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL) {
		renderer = SDL_GetRenderer(window); // <<--- why does a renderer alreay exist with the window now? it never did before.
		if (renderer == NULL) {
			std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
			return false;
		}
	}

	return true;
}

/**
 * This function deallocates the SDL members and other instance variables.
 */
void Drawing::cleanupSDL()
{
    if (window != NULL) {
    
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        // SDL_FreeSurface(screen); SDL_DestroyWindow() takes care of freeing the window's surface (aka. the screen)

        window = NULL;
        screen = NULL;
        renderer = NULL;
    
        SDL_Quit();
    }
}

/* To be called before re-drawing the screen at each frame */
void Drawing::clear_screen() 
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); 
	SDL_RenderClear(renderer);
}

/* Just a wrapper for SDL_RenderPresent for now, but I suspect there will
   be more to this process at some point. */
void Drawing::update_screen()
{
	SDL_RenderPresent(renderer);
}

void Drawing::draw_rect(int start_x, int start_y, int width, int height, int r, int g, int b)
{
	SDL_Rect location_rect = {start_x, start_y, width, height};
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderFillRect(renderer, &location_rect);
}

void Drawing::draw_world(Grid& grid)
{
	clear_screen();

	// Draw grid 
	for (int x = 0; x < grid.dim_x; x++) {
		for (int y = 0; y < grid.dim_y; y++) {

            // TODO: Check the type of tile in this grid location and draw the image for that tile type at the current resolution 
            // ( we will have to load in the images for each tile type at each resolution during the Drawing setup )
            TileSet type = grid.grid[x][y].type->type;
            int r, g, b;
            switch(type) {
            
            case TileSet::TILE_FLOOR :
                r = 192; // Silver!
                g = 192;
                b = 192; 
                break;
             
            case TileSet::TILE_WATER :
                r = 0;   // CYAN!
                g = 255;
                b = 255;
                break;
            
            default: 
                r = g = b = x*y % 256;
            }

            
			draw_rect(x * grid.tile_dim, y * grid.tile_dim, grid.tile_dim, grid.tile_dim, r, g, b);
		}
	}
	update_screen();
}

