#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gfx.h"
#include "image.h"
#include "blend.h"
#include "util.h"
#include "collision.h"

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char **argv)
{
	int cx, cy; // character x,y
	if(SDL_Init(SDL_INIT_VIDEO)) {
		cout << "Unable to initialize video.\n";
		return 1;
	}
	if(!IMG_Init(IMG_INIT_PNG)) {
		cout << "Error loading SDL_image: " << IMG_GetError() << endl;
		return 1;
	}
	
	SDL_Event event;

  Image *background, *world_map, *hero, *screen;

  if(argc == 1) {
    background = loadImage("gfx/Test1BG.png");
    world_map = loadImage("gfx/Test1CL.png");
    hero = loadImage("gfx/Hero.png");	
  }
  else if(argc == 4) {
    background = loadImage(argv[1]);
    world_map = loadImage(argv[2]);
    hero = loadImage(argv[3]);
  }
  else {
		printf("Usage: %s background.png collision.png hero.png\n", argv[0]);
		return 0;
	}

	bool convert;
	float scale = 1, worldscale = 1;
	
	SDL_Window *window = 
		SDL_CreateWindow("waffles", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			min(WINDOW_WIDTH, world_map->w), min(WINDOW_HEIGHT, world_map->h), 0);
	if(!window) {
		cout << "Unable  create game window.\n";
		return 1;
	}
	SDL_Surface *surface =
		SDL_GetWindowSurface(window);
	cout << "Created window: " << SDL_GetPixelFormatName(surface->format->format) << endl;
  cout << (int)surface->format->BitsPerPixel << " bits per pixel\n";
  cout << (int)surface->format->BytesPerPixel << " bytes per pixel\n";
  
  if(surface->format->Rmask == 0xff0000 && surface->format->Gmask == 0xff00 && 
		surface->format->Bmask == 0xff && surface->format->BytesPerPixel == 4 && 
		surface->pitch == 4*surface->w) {
			cout << "Compatible screen format, drawing directly to SDL Surface.\n";
			convert = false;
			screen = new Image(surface->w, surface->h, surface->pixels);
  }
  else {
		cout << "Incompatible screen format, using conversion.\n";
		convert = true;	
		screen = new Image(surface->w, surface->h);
  }
	
	Image *map = new Image(world_map->w, world_map->h);
	
	int i;
	int panx=0, pany=0;
	char res_text[32], coord_text[32];


	// offsceen map setup
	map->scaleblit(background);
	map->ascaleblit(world_map);

	//place character in a non-occupied, random spot
	while(map->collision(hero, cx = rand() % (map->w - hero->w), cy = rand() % (map->h - hero->h)));

 	// initial draw, before keypresses, etc
	screen->blit(map, -panx, -pany);
	screen->ablit(hero, cx - panx, cy - pany);

	u8 *keys = (u8*)SDL_GetKeyboardState(0);
	
	bool quit = false, redraw = false;
	float nx, ny;
  
	while(!quit) {
		while(SDL_PollEvent(&event)) {
			if(event.type==SDL_QUIT)
				quit = true;
			else if(event.type==SDL_WINDOWEVENT) // && event.window.event==SDL_WINDOWEVENT_EXPOSED)
				redraw = true;
			else if(event.type==SDL_KEYDOWN) {
				switch(event.key.keysym.sym) {
					case SDLK_MINUS:
            nx = cx + hero->w/2;
            ny = cy + hero->h/2;
            if(scale > 1 && !scollision(map, 0, 0, worldscale, hero, nx, ny, scale-1)) {
              scale--;
              cx = nx;
              cy = ny;
              redraw = true;
            }
						break;
					case SDLK_EQUALS: 
            nx = cx - hero->w/2;
            ny = cy - hero->h/2;
            if(scale < 8 && !scollision(map, 0, 0, worldscale, hero, nx, ny, scale+1)) {
              scale++;
              cx = nx;
              cy = ny;
              redraw = true;
            }
						break;
          case SDLK_9:
            nx = (cx + hero->w*scale/2)*(worldscale-1)/worldscale - hero->w*scale/2;
            ny = (cy + hero->h*scale/2)*(worldscale-1)/worldscale - hero->h*scale/2;
            if(worldscale > 1 && !scollision(map, 0, 0, worldscale-1, hero, nx, ny, scale)) {
              worldscale--;
              cx = nx;
              cy = ny;
              redraw = true;
            }
						break;
          case SDLK_0:
            nx = (cx + hero->w*scale/2)*(worldscale+1)/worldscale - hero->w*scale/2;
            ny = (cy + hero->h*scale/2)*(worldscale+1)/worldscale - hero->h*scale/2;
            if(worldscale < 32 && !scollision(map, 0, 0, worldscale+1, hero, nx, ny, scale)) {
              worldscale++;
              cx = nx;
              cy = ny;
              redraw = true;
            }
						break;
					case SDLK_ESCAPE:
						quit = true;
				}
			}
		}
		// now that we've handled "command keys", we need to handle motion keys
		// (and mouse in the future)
		int dx = 0, dy = 0;
		int speed = (keys[SDL_SCANCODE_LSHIFT] || keys[SDL_SCANCODE_RSHIFT]) ? 5 : 2;
		//process movements keys multiple times, depending on speed
		for(i = 0; i < speed; i++) {
			if(keys[SDL_SCANCODE_UP] && !keys[SDL_SCANCODE_DOWN]) dy = -1;
			if(keys[SDL_SCANCODE_DOWN] && !keys[SDL_SCANCODE_UP]) dy = 1;
			if(keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT]) dx = -1;
			if(keys[SDL_SCANCODE_RIGHT] && !keys[SDL_SCANCODE_LEFT]) dx = 1;
			if(dx && dy) {
				if(!scollision(map, 0, 0, worldscale, hero, cx+dx, cy+dy, scale)) cx+=dx, cy+=dy, redraw=true;
				else if(!scollision(map, 0, 0, worldscale, hero, cx+dx, cy, scale)) cx+=dx, redraw=true;
				else if(!scollision(map, 0, 0, worldscale, hero, cx, cy+dy, scale)) cy+=dy, redraw=true;
			}
			else if(dx) {
				if(!scollision(map, 0, 0, worldscale, hero, cx+dx, cy, scale)) cx+=dx, redraw=true;
				else if(!scollision(map, 0, 0, worldscale, hero, cx+dx, cy-1, scale)) cx+=dx, cy--, redraw=true;
				else if(!scollision(map, 0, 0, worldscale, hero, cx+dx, cy+1, scale)) cx+=dx, cy++, redraw=true;
			}
			else if(dy) {
				if(!scollision(map, 0, 0, worldscale, hero, cx, cy+dy, scale)) cy+=dy, redraw=true;
				else if(!scollision(map, 0, 0, worldscale, hero, cx-1, cy+dy, scale)) cx--, cy+=dy, redraw=true;
				else if(!scollision(map, 0, 0, worldscale, hero, cx+1, cy+dy, scale)) cx++, cy+=dy, redraw=true;
			}
		}
		
		if(redraw) {
			panx = clamp(cx + ((int)scale*hero->w - screen->w)/2, 0, (int)(worldscale*map->w) - screen->w);
			pany = clamp(cy + ((int)scale*hero->h - screen->h)/2, 0, (int)(worldscale*map->h) - screen->h);
			screen->sblit(map, -panx, -pany, worldscale);
			screen->asblit(hero, cx - panx, cy - pany, scale);

			sprintf(res_text, "World: %.1fx", worldscale);
			screen->puttext(res_text, 0, 0, 0xff0000);
			sprintf(res_text, "Hero: %.1fx", scale);
			screen->puttext(res_text, 0, 16, 0xff0000);
			sprintf(coord_text, "(%d,%d)", cx, cy);
			screen->puttext(coord_text, screen->w - strlen(coord_text)*8, 0, 0xff0000);
			
			if(convert) 
				SDL_ConvertPixels(screen->w, screen->h, SDL_PIXELFORMAT_ARGB8888, screen->pixels,
					4*screen->w, surface->format->format, surface->pixels, surface->pitch);
			SDL_UpdateWindowSurface(window);
			redraw = false;
		}
		SDL_Delay(12); // this should be adaptive, but is a good default
	}	
		

	delete world_map;
	delete map;
	delete hero;
	delete background;
	delete screen;
	
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}
