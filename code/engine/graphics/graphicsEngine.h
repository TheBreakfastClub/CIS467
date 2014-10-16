/*********************************************************
File Name:	    graphicsEngine.h
Author:		    The Breakfast Club
Creation Date:  10-15-2014
Description:    This class holds the code needed to create
                a graphics engine to paint items to the screen.
************************************************************/

#pragma once

// Includes
#include <SDL2/SDL_image.h>
#include "../render/image.h"
#include "../world_definition/gameWorld.h"

using namespace std;

class GraphicsEngine {

public:

    GraphicsEngine();
    ~GraphicsEngine();
    bool init(const char *gameName, int width, int height);

    void refreshScreen();
    void drawGameWorld(const GameWorld &world, const int &pan_x, const int &pan_y);

private:
   
    /** Variables defining the game screen */
    SDL_Window *window;
    SDL_Surface *surface;
    Image *screen;

    bool setupSDL(const char *gameName, int width, int height);
    void cleanupSDL();

};

