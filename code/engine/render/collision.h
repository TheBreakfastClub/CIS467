#pragma once
#include "image.h"

bool collision(Image*, int, int, Image*, int, int);
int overlap(Image*, int, int, Image*, int, int);
bool scollision(Image*, int, int, float, Image*, int, int, float);
int soverlap(Image*, int, int, float, Image*, int, int, float);
