/*********************************************************
File Name:	    pixel.cpp
Author:			The Breakfast Club
Creation Date:  09-26-2014
Description:	Holds definitions about the pixels that make
                up the game world.
************************************************************/

#include "pixel.h"

/**
 * Creates a pixel with specified argb values and returns it
 */
Pixel Pixel_Util::make_pixel(unsigned char a, unsigned char r, unsigned char g, unsigned char b) {

    // Todo: error check for values > 255
    Pixel pix;
    pix.a = a;
    pix.r = r;
    pix.g = g;
    pix.b = b;
    return pix;
}

Pixel Pixel_Util::pixel_avg (Pixel pix1, Pixel pix2) {

    Pixel pix;
    pix.argb = ((pix1.argb & 0xFEFEFEFE) >> 1) + ((pix2.argb & 0xFEFEFEFE) >> 1);
    return pix;
}
