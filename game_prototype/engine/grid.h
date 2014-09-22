#ifndef GRID_H
    #define GRID_H

#include "location.h"
#include <vector>
#include <cassert>

class Grid {

	public:
		
		std::vector<std::vector<Location> > grid;
		int dim_x, dim_y;
		Grid(int dim_x, int dim_y);
		std::vector<Location>& operator[](int index);

};

#endif