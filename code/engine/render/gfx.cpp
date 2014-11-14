#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "gfx.h"
#include "image.h"

Image* loadImage(const char *filename)	{
	SDL_Surface *gfx = IMG_Load(filename);
	if(!gfx) {
		std::cout << "Unable to load " << filename << ": " << IMG_GetError() << std::endl;
		return 0;
	}
	
	Image *img = new Image(gfx->w, gfx->h);
	
 	SDL_ConvertPixels(gfx->w, gfx->h, gfx->format->format, gfx->pixels, 
 		gfx->pitch, SDL_PIXELFORMAT_ARGB8888, (void *)img->pixels, 4*img->w);
	SDL_FreeSurface(gfx);
	
// 	premultiply colors by alpha
	u32 c,red,green,blue,alpha;
	for(int i = 0; i < img->w * img->h; i++) {
		c = img->pixels[i];
		alpha = c >> 24;
		red = ((c >> 16) & 0xff)*alpha/255;
		green = ((c >> 8) & 0xff)*alpha/255;
		blue = (c & 0xff)*alpha/255;
		img->pixels[i] = (alpha << 24) + (red << 16) + (green << 8) + blue;
	}
	return img;
}	

Image* downsample(Image *src, int width, int height, u32 (*blend_func)(u32*, int))
{
	Image *dst = new Image(width, height);

	u32 colors[(src->w/width+1) * (src->h/height+1)];
	
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			int count = 0;
			for(int j = y*src->h/height; j < (y+1)*src->h/height; j++) {
				for(int i = x*src->w/width; i < (x+1)*src->w/width; i++) {
					colors[count++] = src->pixels[src->w * j + i];
				}
			}
			dst->pixels[width*y + x] = count ? blend_func(colors, count) : 0;
		}
	}
	return dst;
}

// For showing that a character/enemy/whatever has been damaged
Image* redTint(Image *src, int amt)
{
        Image *dest = new Image(src->w, src->h);
        for (int i = 0; i < src->w * src->h; i++) {
                u32 c, r, g, b, a;
                c = src->pixels[i];
                a = c >> 24;
                r = ((c >> 16) & 0xff) * a / 255;
                g = ((c >> 8) & 0xff) * a / 255;
                b = (c & 0xff) * a / 255;
                if (a < 40) {
                        //std::cout << "Color info on full alpha: a: " << std::to_string(a) << " r: " << std::to_string(r) << " g: " << std::to_string(g) << " b: " << std::to_string(b) << std::endl;
                        continue; // don't alter the color of a transparent pixel
                }
                if (r + amt <= 255)
                        dest->pixels[i] = (a << 24) + (r + amt << 16) + (g << 8) + b;
                else
                        dest->pixels[i] = (a << 24) + (255 << 16) + (g << 8) + b;
        }
        return dest;
}
