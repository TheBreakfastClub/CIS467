/*********************************************************
File Name:	    pixel.h
Author:			The Breakfast Club
Creation Date:  09-26-2014
Description:	Holds definitions about the pixels that make
                up the game world.
************************************************************/

#pragma once

#include <string>

/**
 * Defines one pixel.
 * You may access the individual argb values or the entire
 * 32-bit int.
 */
union Pixel {
    unsigned int argb;
    struct {
        unsigned char a,r,g,b;
    };
};

/**
 * Holds static methods for working with pixels
 */
class Pixel_Util {

    public:
        static Pixel make_pixel(unsigned char a, unsigned char r, unsigned char g, unsigned char b);
        static Pixel pixel_avg (Pixel pix1, Pixel pix2);

    private:
        Pixel_Util();

};
