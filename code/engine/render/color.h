#pragma once

#include "types.h"

struct Color {
	u8 b,g,r,a;
	
	Color(); 	
	Color(int, int, int, int);
	Color(int, int, int);
	Color(u32);
	Color& operator=(const u32);
	u32 operator()();
};
