#pragma once

#include <SDL2/SDL.h>
#include "../grid.h"

/* So I've actually started on something that would take care of the drawing.
   Eventually It'd have the "draw_world" function I mentioned */
class Drawing {

private:

	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Surface* screen;

public:

	Drawing();
	~Drawing();
	
	bool setup(int screen_width, int screen_height);
	void cleanup();
	
	void clear_screen();
	void update_screen();
	
	void draw_rect(int start_x, int start_y, int width, int height, int r, int g, int b);

	/* this is really just an example of how this could look */
	void draw_world(Grid& grid);

};
