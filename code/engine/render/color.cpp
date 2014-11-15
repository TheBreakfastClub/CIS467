#include "color.h"

Color::Color(int alpha, int red, int green, int blue) {
	a = alpha;
	r = red;
	g = green;
	b = blue;
}

Color::Color(int red, int green, int blue) {
	a = 255;
	r = red;
	g = green;
	b = blue;
}
 
Color::Color(u32 value) {
	*((u32*)this) = value;
}

Color& Color::operator=(const u32 value) {
	*((u32*)this) = value;
	return *this;
}

u32 Color::operator()() {
	return *((u32*)this);
}
