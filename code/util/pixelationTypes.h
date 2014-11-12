/*********************************************************
File Name:	    pixelationTypes.h
Author:			Steven Hoffman
Creation Date:  11-12-2014
Description:	This class holds an enum that refers to the
                different pixelation algorithms available.
************************************************************/

#pragma once

enum PixelationType {
    POINT_SAMPLE,
    AVERAGE,
    AVERAGE_OPAQUE,
    MOST_COMMON,
    PIX_COUNT
};

