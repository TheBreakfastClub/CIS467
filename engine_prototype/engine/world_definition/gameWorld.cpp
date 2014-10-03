/*********************************************************
File Name:	    gameWorld.cpp
Author:		    The Breakfast Club
Creation Date:  09-25-2014
Description:    Holds the data defining the world
************************************************************/

#include "gameWorld.h"
#include <SDL2/SDL.h>
#include <iostream> 
#include <numeric>

/**
 * dim_x, dim_y : dimensions of window in SDL's units
 * pix_length, pix_height : dimensions of the gameWorld in Pixel size. NOTE: consider removing this since the world in Pixel size depends on current resolution
 */
GameWorld::GameWorld(int dim_x, int dim_y, int pix_dim, int pix_length, int pix_height) 
    : dim_x(dim_x), dim_y(dim_y), pix_dim(pix_dim), medRes(pix_length/2, pix_height/2), 
      lowRes(pix_length/4, pix_height/4), pix_length(pix_length), pix_height(pix_height)
{
    currentRes = &lowRes;
    currentResLevel = 0; // 0 -- low, 1 -- medium, 2 -- high
}

bool GameWorld::setup(SDL_Renderer *r)
{	
	return set_map(r);
}

bool GameWorld::set_map(SDL_Renderer *r)
{
	// Set the high resolution texture
	SDL_Surface *temp_surf = IMG_Load("resources/Test1CL.png");
	highRes = SDL_CreateTextureFromSurface(r, temp_surf);
	if (highRes == NULL) {
		std::cout << "Error in GameWorld::set_map. highRes texture was null.\n";
		return false;
	}

	// Pixelize for medRes and lowRes
	pixelize(temp_surf, medRes, 16);
	pixelize(temp_surf, lowRes, 32);

	SDL_FreeSurface(temp_surf);
	return true;
}

void GameWorld::next_resolution()
{
	if (currentResLevel < 2)
		currentResLevel++;
	_set_current_res();
}

void GameWorld::prev_resolution()
{
	if (currentResLevel > 0)
		currentResLevel--;
	_set_current_res();
}

void GameWorld::_set_current_res()
{
	switch (currentResLevel) {
		case 0:
			currentRes = &lowRes; break;
		case 1:
			currentRes = &medRes; break;
		case 2:
			currentRes = NULL;
	}
}

/* pixelize higher_res onto lower_res, where block_dim is the square dimension that defines 
   the size of the Pixels in lower_res, in terms of higher_res pixels 
   (e.g. a block_dim of 2 defines a Pixel size in lower_res of 2x2 Pixels from higher_res) 
   NOTE: Currently super broken. Just using the other pixelize function to create both medRes and lowRes */
void GameWorld::pixelize(GameMap &higher_res, GameMap &lower_res, int block_dim)
{
	int lres_pix_per_row = higher_res.width / block_dim;  // num. of Pixels per row for lower_res
	int lres_pix_rows = higher_res.height / block_dim;    // num. of Pixel rows for lower_res

	std::cout << "lres Pixels per row: " << std::to_string(lres_pix_per_row) << std::endl;
	std::cout << "lres Pixel rows: " << std::to_string(lres_pix_rows) << std::endl;

	for (int row = 0; row < lres_pix_rows; row+=block_dim) {			// set row and column for each new
		for (int col = 0; col < lres_pix_per_row; col+=block_dim) {     // row of pixels created for lower_res

			std::vector<Pixel> pixs(block_dim*block_dim);
			for (int y = row; y < row + block_dim; y++) {		// collect Pixels in this area
				for (int x = col; x < col + block_dim; x++) {
					pixs.push_back(higher_res.test_layer[y * higher_res.width + x]);
				}
			}
			Pixel avg;											// average Pixels from this area
			for (int i = 1; i < pixs.size(); i++) {
				if (i == 1)
					avg = Pixel_Util::pixel_avg(pixs[i-1], pixs[i]);
				else {
					avg = Pixel_Util::pixel_avg(avg, pixs[i]);
				}
			}
			lower_res.test_layer.push_back(avg);
		}
	}
	lower_res.width = lres_pix_per_row;
	lower_res.height = lres_pix_rows;
	lower_res.phys_dim = higher_res.phys_dim * block_dim;

	std::cout << "Total Pixels in lowRes: " << std::to_string(lower_res.test_layer.size()) << std::endl;
}

/* Pixelize an actual surface to a GameMap layer. pix_dim refers to the physical dimension that defines any square Pixel */
void GameWorld::pixelize(SDL_Surface *image, GameMap &map, int pix_dim)
{
	int pix_per_row = image->w / pix_dim; // Pixels per row (NOT actual pixels)
	int pix_rows = image->h / pix_dim;    // Number of Pixel rows (NOT actual pixels)

	std::cout << "image width: " << image->w << std::endl;
	std::cout << "image height: " << image->h << "\n";
	std::cout << "Pixel dimension in actual pixels: " << pix_dim << "\n\n";
	std::cout << "Pixels per row: " << pix_per_row << std::endl;
	std::cout << "Pixel rows: " << pix_rows << "\n\n";

	// get the raw pixel data from the image surface
	Uint32 *raw_pix = (Uint32*) image->pixels;

	// Create Pixel array
	for (int pix_y = 0; pix_y < pix_rows; pix_y++) { // pix_y in terms of Pixels (capital P)
		int start_y = pix_dim * pix_y;
		for (int pix_x = 0; pix_x < pix_per_row; pix_x++) {
			int start_x = pix_dim * pix_x;	

			// Look at each physical pixel starting at (start_x, start_y), getting RGBA values
			std::vector<Uint8> rs(pix_dim*pix_dim);
			std::vector<Uint8> gs(pix_dim*pix_dim);
			std::vector<Uint8> bs(pix_dim*pix_dim);
			std::vector<Uint8> as(pix_dim*pix_dim);
			for (int y = start_y; y < start_y + pix_dim; y++) {
				for (int x = start_x; x < start_x + pix_dim; x++) {
					Uint32 pixel = raw_pix[y * image->h + x];
					Uint8 r, g, b, a;

					Uint8 *colors = (Uint8*) &pixel;
					//b = (pixel >> 16 & 0xFF);
					//g = (pixel >> 8 & 0xFF);
					//r = (pixel & 0xFF);
					//a = pixel;
					r = colors[0];
					g = colors[1];
					b = colors[2];
					a = colors[3];

					rs.push_back(r);
					gs.push_back(g);
					bs.push_back(b);
					as.push_back(a);
				}
			}

			// Create and add average pixel
			Pixel p;
			p.r = (Uint8) (std::accumulate(rs.begin(), rs.end(), 0) / (pix_dim * pix_dim));
			p.g = (Uint8) (std::accumulate(gs.begin(), gs.end(), 0) / (pix_dim * pix_dim));
			p.b = (Uint8) (std::accumulate(bs.begin(), bs.end(), 0) / (pix_dim * pix_dim));
			p.a = (Uint8) (std::accumulate(as.begin(), as.end(), 0) / (pix_dim * pix_dim));
			map.test_layer.push_back(p);
		}
	}

	// Set the map's new properties
	map.width = pix_per_row;
	map.height = pix_rows;
	map.phys_dim = pix_dim;

	this->pix_dim = pix_dim;
	this->pix_length = pix_per_row;
	this->pix_height = pix_rows;
}
