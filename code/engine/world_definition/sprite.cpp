/*********************************************************
File Name:	    sprite.cpp
Author:		    The Breakfast Club
Creation Date:  09-28-2014
Description:	Defines the different types of sprites that can
                be in the world.
************************************************************/

#include "sprite.h"

/**
 * This constructor should be used if the caller is going to set the image
 * by passing it a filename to load.
 */
Sprite::Sprite(int x, int y) : x(x), y(y), deallocNeeded(false), spriteImageH(NULL), spriteImageM(NULL), spriteImageL(NULL) {}

/**
 * This constructor allows the caller to pass the sprite images to the sprite.
 * In this case, the sprite is not responsible for deleting any of the images
 * itself and the caller must delete them.
 */
Sprite::Sprite(int x, int y, Image *spriteImageH, Image *spriteImageM, Image *spriteImageL) 
 : x(x), y(y), spriteImageH(spriteImageH) , spriteImageM(spriteImageM), spriteImageL(spriteImageL), deallocNeeded(false) {}

/**
 * Destructor
 */
Sprite::~Sprite() {
    if (deallocNeeded && spriteImageH) {
        if(spriteImageM != spriteImageH) delete spriteImageM;
        if(spriteImageL != spriteImageH) delete spriteImageL;
        delete spriteImageH;
    }
}

/**
 * Returns the image of the sprite based on the given resolution.
 */
Image* Sprite::getSpriteImage(Resolution res) {
    switch (res) {
    case Resolution::LOW:
        return spriteImageL;
    case Resolution::MED:
        return spriteImageM;
    case Resolution::HIGH:
        return spriteImageH;
    }
}

/**
 * Sets the sprite image for all resolutions, using the passed image as the
 * High resolution image. Returns true if there were no errors while setting
 * the image, false otherwise.
 */
bool Sprite::setSpriteImage(const char *imgFileName, pixAlgo pixelator, int medCut, int lowCut) {

    if (imgFileName == NULL) return false;

    // Deallocate old images if needed
    if (spriteImageH && deallocNeeded) {
        delete spriteImageH;
        delete spriteImageM;
        delete spriteImageL;
    }

    deallocNeeded = true;
    
    // Read in the high resolution image
    spriteImageH = loadImage(imgFileName);
    if (!spriteImageH) return false;
    
    scale[0] = lowCut;
    scale[1] = medCut;
    scale[2] = 1;

    if(pixelator) {
      // Create Medium resolution image
      spriteImageM = downsample(spriteImageH, spriteImageH->w/medCut, spriteImageH->h/medCut, pixelator);
    
      // Create Low resolution image
      spriteImageL = downsample(spriteImageH, spriteImageH->w/lowCut, spriteImageH->h/lowCut, pixelator);
    }
    else spriteImageL = spriteImageM = spriteImageH;

    return true;
}

/**
 * This sets the sprite images to those passed into the function. The caller
 * is now responsible for deleting these images, however.
 */
void Sprite::setSpriteImage(Image *spriteImageHigh, Image *spriteImageMed, Image *spriteImageLow) {
    
    if (!spriteImageHigh || !spriteImageMed || !spriteImageLow) return;

    // Deallocate old images if needed
    if (spriteImageH && deallocNeeded) {
        if(spriteImageM != spriteImageH) delete spriteImageM;
        if(spriteImageL != spriteImageH) delete spriteImageL;
        delete spriteImageH;
    }

    deallocNeeded = false;

    spriteImageH = spriteImageHigh;
    spriteImageM = spriteImageMed;
    spriteImageL = spriteImageLow;
}
