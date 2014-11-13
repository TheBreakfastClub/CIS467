/*********************************************************
File Name:	    pixUtil.cpp
Author:			Steven Hoffman
Creation Date:  11-12-2014
Description:	This class holds methods for working with
                pixelation algorithms.
************************************************************/

#include "pixUtil.h"

/**
 * This method defines which index (when reading in from a config file)
 * refers to which pixelation algorithm
 */
pixAlgo PixUtil::getPixAlgoFromIdx(int idx) {

    switch (idx) {
    case 0:
        return Blend::blend_point_sample;
    case 1:
        return Blend::blend_average;
    case 2:
        return Blend::blend_average_opaque;
    case 3:
        return Blend::blend_most_common;
    default:
        return Blend::blend_average;
    }
}
