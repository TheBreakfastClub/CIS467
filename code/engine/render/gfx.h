#pragma once
#include "image.h"
#include "types.h"

Image* loadImage(const char*);
Image* downsample(Image*, int, int, u32 (*)(u32*, int));
Image* redTint(Image*, int);
