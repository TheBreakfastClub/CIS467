#include <SDL2/SDL.h>
#ifdef USING_MAC
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif
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
Image* redTint(Image *src)
{
  Image *dest = new Image(src->w, src->h);
  for (int i = 0; i < src->w * src->h; i++)
		dest->pixels[i] = (src->pixels[i] & 0xffff0000) + ((src->pixels[i] & 0xfefe) >> 1);
	return dest;
}
