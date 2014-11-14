#pragma once

#include "../../using_mac.h"
#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#ifdef USING_MAC
    #include <SDL2_image/SDL_image.h>
#else
    #include <SDL2/SDL_image.h>
#endif
#include "image.h"
#include "util.h"

using namespace std;

class Gfx {

private:
    Gfx(); // Private because this is a utility class with static methods

public:

    static Image* loadImage(const char *filename);
    
    static Image* downsample(Image *src, int width, int height, u32 (*blend_func)(u32*, int));

    static Image* redTint(Image *src, int amt);

};

