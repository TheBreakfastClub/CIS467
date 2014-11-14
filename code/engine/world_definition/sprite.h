/*********************************************************
File Name:	    sprite.h
Author:		    The Breakfast Club
Creation Date:  09-28-2014
Description:	Defines the different types of sprites that can
                be in the world.
************************************************************/

#pragma once

#include "../render/image.h"
#include "../../util/pixUtil.h"
#include "../render/blend.h"
#include "../render/gfx.h"
#include "resolution.h"
#include <utility>

class Sprite {

    private:
        Image *spriteImageH;
        Image *spriteImageM;
        Image *spriteImageL;
        bool deallocNeeded;

    public:
        Sprite(int x, int y);
        Sprite(int x, int y, Image *spriteImageH, Image *spriteImageM, Image *spriteImageL);
        ~Sprite();
        int x;
        int y;
       
        Image* getSpriteImage(Resolution res);
        bool setSpriteImage(const char *imgFileName, 
            pixAlgo pixelator = blend_average_opaque, 
            int medCut = 8, int lowCut = 16);
        void setSpriteImage(Image *spriteImageHigh, 
            Image *spriteImageMed, Image *spriteImageLow);
};
