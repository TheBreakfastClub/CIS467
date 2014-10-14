#pragma once

#include <stdio.h>
#include <string>
#include "types.h"

struct Color {
	u8 b,g,r,a;
	
	Color() {}
 	
	Color(int alpha, int red, int green, int blue) {
		a = alpha;
		r = red;
		g = green;
		b = blue;
	}

	Color(int red, int green, int blue) {
		a = 255;
		r = red;
		g = green;
		b = blue;
	}
 	
	Color(u32 value) {
		*((u32*)this) = value;
	}
	
	Color& operator=(const u32 value) {
		*((u32*)this) = value;
		return *this;
	}

	u32 operator()() {
		return *((u32*)this);
	}
};
