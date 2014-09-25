/**
 * This class handles the main elements of the graphics engine.
 */

#pragma once

#include <SDL2/SDL.h>
#include "../grid.h"

class Drawing {

private:

	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Surface* screen;

public:

	Drawing();
	~Drawing();
	
	bool setupSDL(int screen_width, int screen_height);
	void cleanupSDL();
	
	void clear_screen();
	void update_screen();
	
	void draw_rect(int start_x, int start_y, int width, int height, int r, int g, int b);

	/* this is really just an example of how this could look */
	void draw_world(Grid& grid);

};
