#pragma once

#undef WARNING

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "types.h"
#include "util.h"
#include "color.h"
#include "point.h"
#include "font.h"

using namespace std;

// The Image class is a simplified counterpart to the SDL_Surface structure.
// Pixels are always in ARGB8888 format, the pitch is always the width, and
// the clipping rectangle is always the entire image.
class Image {
	bool dealloc;
	
	void init(int width, int height, void *pix, bool d);

	public:
	int w,h;
	u32 *pixels;
	double cx, cy;
	
	Image();
	
	Image(int width, int height);
	
	Image(int width, int height, void *buffer);
		
	~Image();

	void resize(int width, int height);
	
	void clear();

	void clear(u32 color);
	
  // original version, doesn't preserve alpha
  static inline u32 blend_old(u32 src, u32 dst);

  // super fast version postmultiplied version, doesn't preserve alpha
  static inline u32 blend2(u32 src, u32 dst);

  // super fast premultiplied alpha
  static inline u32 blend(u32 src, u32 dst);
	
  // no clipping
	void _blit(Image *src, int x, int y);
	
  void blit(Image *src, int x, int y);

	// no clipping
	void _ablit(Image *src, int x, int y);
	
	void ablit(Image *src, int x, int y);
	
	// no clipping yet
  bool collision(Image *src, int x, int y);
	
	// no clipping yet
  int overlap(Image *src, int x, int y);
	
	void scaleblit(Image *src);

	void ascaleblit(Image *src);
	
	static bool point_compare(const Point& a, const Point& b);
	
	void triangle(Point a, Point b, Point c, u32 color);
	// fixed point, tests full screen
	void ablit(Image *src, double X, double Y, double angle, double scale = 1.0);

	void putchar(unsigned char c, int x, int y, u32 color);

	void puttext(const char* text, int x, int y, u32 color);
	
	void puttext(string text, int x, int y, u32 color);
};
