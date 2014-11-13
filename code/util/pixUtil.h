/*********************************************************
File Name:	    pixUtil.h
Author:			Steven Hoffman
Creation Date:  11-12-2014
Description:	This class holds methods for working with
                pixelation algorithms.
************************************************************/

#pragma once

#include "../engine/render/blend.h"
#include "../engine/render/types.h"

using namespace std;

typedef u32 (*pixAlgo)(u32*, int);

class PixUtil {

private:
    PixUtil(); // Private because it is a utility class with static methods

public:
    static pixAlgo getPixAlgoFromIdx(int idx);

};
