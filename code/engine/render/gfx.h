#pragma once

#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "image.h"
#include "util.h"

using namespace std;

class Gfx {

private:
    Gfx(); // Private because this is a utility class with static methods

public:

    static Image* loadImage(const char *filename);
    
    static Image* downsample(Image *src, int width, int height, u32 (*blend_func)(u32*, int));

};

