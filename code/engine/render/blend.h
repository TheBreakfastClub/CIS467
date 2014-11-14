// This file defines blending modes for pixelation.

#pragma once
#include "types.h"

u32 blend_point_sample(u32*, int);
u32 blend_average(u32*, int);
u32 blend_average_opaque(u32*, int);
u32 blend_most_common(u32*, int);
