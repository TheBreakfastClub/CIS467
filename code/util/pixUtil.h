/*********************************************************
File Name:	    pixUtil.h
Author:			Steven Hoffman
Creation Date:  11-12-2014
Description:	This class holds methods for working with
                the PixelationType enum.
************************************************************/

#pragma once

#include "pixelationTypes.h"

using namespace std;

class PixUtil {

private:
    PixUtil(); // Private because it is a utility class with static methods

public:
    static PixelationType getPixTypeFromIdx(int idx);

    // static u32 (*blend_func)(u32*, int) getPixAlgoFromPixType(PixelationType);

};
