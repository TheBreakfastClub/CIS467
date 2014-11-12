/*********************************************************
File Name:	    pixUtil.cpp
Author:			Steven Hoffman
Creation Date:  11-12-2014
Description:	This class holds methods for working with
                the PixelationType enum.
************************************************************/

#include "pixUtil.h"

/**
 * This method defines which index (when reading in from a config file)
 * refers to which PixelationType. It should be based off the value of
 * the enum.
 */
PixelationType PixUtil::getPixTypeFromIdx(int idx) {
    
    switch (idx) {
    case 0:
        return POINT_SAMPLE;
    case 1:
        return AVERAGE;
    case 2:
        return AVERAGE_OPAQUE;
    case 3:
        return MOST_COMMON;
    default:
        return AVERAGE;
    }
}
