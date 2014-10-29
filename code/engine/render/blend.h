// This file defines blending modes for pixelation.
// It is safe to assume that at least one color is passed in.

#pragma once
#include <map>
#include "types.h"

using namespace std;

u32 blend_point_sample(u32 *colors, int count);

u32 blend_average(u32 *colors, int count);

u32 blend_average_opaque(u32 *colors, int count);


u32 blend_most_common(u32 *colors, int count);
