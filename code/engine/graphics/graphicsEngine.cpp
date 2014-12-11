/*********************************************************
File Name:	    graphicsEngine.cpp
Author:		    The Breakfast Club
Creation Date:  10-15-2014
Description:    This class holds the code needed to create
                a graphics engine to paint items to the screen.
************************************************************/

// The includes
#include "graphicsEngine.h"
#include "../render/util.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "../render/util.h"

/**
 * Default constructor. User needs to call init before using
 * the engine.
 */
GraphicsEngine::GraphicsEngine()
{
    window = NULL;
    surface = NULL;
    screen = NULL;
    msgTime = 0;
}

/**
 * Deconstructor.
 */
GraphicsEngine::~GraphicsEngine() {
    cleanupSDL();
}

/**
 * This function initializes the graphics engine, returning true
 * if it is successful or if it is already initialized. Otherwise,
 * returns false.
 */
bool GraphicsEngine::init(const char *gameName, int width, int height) {

    if (window != NULL) return true; 
    return setupSDL(gameName, width, height);
}

/**
 * Sets up SDL to use for graphics. Returns false if there
 * was an error initializing.
 */
bool GraphicsEngine::setupSDL(const char *gameName, int width, int height) {

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create the SDL window to draw on
    window = SDL_CreateWindow(gameName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Get the SDL surface to draw on
    surface = SDL_GetWindowSurface(window);
    if (surface == NULL) {
        std::cout << "SDL_GetWindowSurface Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // Save a reference to the pixels in the SDL surface into an Image,
    // so that we can manipulate the pixels directly. If video card is not the right
    // pixel format, however, just allocate pixel memory for an Image directly.
    if(surface->format->Rmask == 0xff0000 && surface->format->Gmask == 0xff00 && 
			surface->format->Bmask == 0xff && surface->format->BytesPerPixel == 4 && 
			surface->pitch == 4*surface->w) {
				//cout << "Compatible window format, drawing directly to SDL Surface.\n";
				convert = 0;
				screen = new Image(surface->w, surface->h, surface->pixels); // image stores reference to the actual pixels on the screen
    }
    else {
			//cout << "Incompatible window format, using conversion.\n";
			convert = 1;	
			screen = new Image(surface->w, surface->h); // image actually allocates its own pixels
    }
    
    return true;
}

/**
 * Cleans up the SDL objects, freeing memory as necessary.
 */
void GraphicsEngine::cleanupSDL() {
    
    if (window) {
        delete (screen);
        SDL_DestroyWindow(window); // frees window and its associated surface
        SDL_Quit();
    }
}

/**
 * This method refreshes the window, displaying whatever has been drawn to
 * the screen.
 */
void GraphicsEngine::refreshScreen() {
    
    // Paint pixels to SDL Surface if video card's format is not consistent
    // with the pixel format in the Image class
    if(convert) {
        SDL_ConvertPixels(screen->w, screen->h, SDL_PIXELFORMAT_ARGB8888, screen->pixels,
				4*screen->w, surface->format->format, surface->pixels, surface->pitch);
    }

    // Display drawn Image to screen/window
    SDL_UpdateWindowSurface(window);
}

/** 
 * This method draws the GameUniverse to the screen. It does NOT 
 * refresh the screen, allowing the caller to decide when to display
 * what has been drawn.
 *
 * @param universe The game universe to draw to the screen
 */
void GraphicsEngine::drawGameUniverse(GameUniverse &universe) {

    // Grab references
    Hero *hero = &universe.hero;
    GameWorld *world = hero->world;
    GameMap *map = world->currentRes;
    Resolution res = world->currentResLevel;
    float scale = world->scale[res];

    // Draw the map to the screen, panning the map to the correct area
    int pan_x = clamp(hero->x - screen->w/2, 0, (int)(map->mapImg->w*scale) - screen->w);
    int pan_y = clamp(hero->y - screen->h/2, 0, (int)(map->mapImg->h*scale) - screen->h);
    screen->sblit(map->mapImg, -pan_x, -pan_y, scale);

    for (Portal* p : world->portals) {
      p->draw(screen, pan_x, pan_y);
    }

    // Draw the items to the screen
    for (Item* i : world->items) {
      i->draw(screen, pan_x, pan_y);
    }
    
    // Draw enemies
    for (Enemy *e : world->enemies) {
      e->draw(screen, pan_x, pan_y);
    }

    // Draw the hero to the screen
    hero->draw(screen, pan_x, pan_y); 

    // Draw the top layer, if it exists
    if (map->topLayer) {
        screen->asblit(map->topLayer, -pan_x, -pan_y, scale);
    }

    // display health
    char text[64];
    sprintf(text,"health:%4d:", hero->getHitPoints());
    screen->puttext(text, screen->w - 88, 0, 0xffffffff); // white

    // display status message
    if(msgTime > 0) {
      screen->puttext(msg, screen->w/2 - 4*strlen(msg), 0, 0xffff0000); // red
      msgTime--;
    }
    
}

/**
 * Display status message for ~10s
 *
 * @param text Message to display
 */
void GraphicsEngine::message(const char *text) {
  strncpy(msg, text, 64);
  msgTime = 600;
}
