/*********************************************************
File Name:	    graphicsEngine.cpp
Author:		    The Breakfast Club
Creation Date:  10-15-2014
Description:    This class holds the code needed to create
                a graphics engine to paint items to the screen.
************************************************************/

// The includes
#include "graphicsEngine.h"
#include <iostream>
#include <stdlib.h>

/**
 * Default constructor. User needs to call init before using
 * the engine.
 */
GraphicsEngine::GraphicsEngine()
{
    window = NULL;
    surface = NULL;
    screen = NULL;
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
    // so that we can manipulate the pixels directly.
    screen = new Image(surface->w, surface->h, surface->pixels);
    
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
    SDL_UpdateWindowSurface(window);
}

/** 
 * This method draws the GameWorld to the screen. It does NOT 
 * refresh the screen, allowing the caller to decide when to display
 * what has been drawn.
 *
 * @param world The game world to draw to the screen
 * @param pan_x The horizontal distance from the top-left corner
 *      of the game map indicating the top-left corner of the area
 *      of the game map that should be drawn to the screen.
 * @param pan_y The vertical distance from the top-left corner
 *      of the game map indicating the top-left corner of the area
 *      of the game map that should be drawn to the screen.
 */
void GraphicsEngine::drawGameWorld(const GameWorld &world, const int &pan_x, const int &pan_y) {

    // Grab the current map to draw to 
    // and create an image to paint the map to
    GameMap *map = world.currentRes;
    Image *mapImg = new Image(map->w(), map->h());

    // Draw the background and collision layer
    mapImg->scaleblit(map->backgroundLayer);
    mapImg->ascaleblit(map->collisionLayer);

    // TODO: Draw Sprites (e.g. hero, enemies, items) onto mapImg

    // Draw the top layer, if it exists
    if (map->topLayer) {
        mapImg->ascaleblit(map->topLayer);
    }

    // Draw the map to the screen, panning the map to the correct area
    // TODO: see if we can paint directly to the screen, only painting
    // the items in the panned area.
    screen->blit(mapImg, -pan_x, -pan_y);
}

