/* vim: ts=2
 *
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/01/05
 *  Filename: LifeForms.cpp
 *
 *  Overview: A library of functions that create standard 'organisms' for
 *            Conway's Game of Life.
 *
 *  Arguments: All functions take the same arguments:
 *   = A game grid, which is passed by reference
 *   = X,Y coordinates which are the upper-left origin for the organism
 *
 */
#include <iostream>
#include <vector>

#define DEBUG false

void Blinker(std::vector<std::vector<bool> > &Grid, int x, int y)
{
  // Always start vertically. Programmer edict :)
  // TODO: Should check Grid.size() and consider margins
	//
	//  .....
	//  ..O..
	//  ..O..
	//  ..O..
	//  .....
	//
	if (DEBUG) std::cout << "Creating a Blinker at " << x << ", " << y << std::endl;
  if (  (x > Grid.size() ) 
		 || (y+2 > Grid[x].size() ))
	{
		std::cout << "Grid position error in Blinker!";
		return;
	}

	Grid[x][y] = true;
	Grid[x][y+1] = true;
	Grid[x][y+2] = true;
}

void Glider (std::vector<std::vector<bool> > &Grid, int x, int y)
{
	//  ......
	//  ..O...
	//  ...O..
	//  .OOO..
	//  ......
	//
	if (DEBUG) std::cout << "Creating a Glider at " << x << ", " << y << std::endl;
  if (  (x+2 > Grid.size() ) 
		 || (y+2 > Grid[x].size() ))
	{
		std::cout << "Grid position error in Glider!";
		return;
	}

	Grid[x][y+1] = true;
	Grid[x+1][y+2] = true;
	Grid[x+2][y] = true;
	Grid[x+2][y+1] = true;
	Grid[x+2][y+2] = true;
}
void Toad (std::vector<std::vector<bool> > &Grid, int x, int y)
{
	//  ......
	//  ..OOO.
	//  .OOO..
	//  ......
	if (DEBUG) std::cout << "Creating a toad at " << x << ", " << y << std::endl;
  if (  (x+2 > Grid.size() ) 
		 || (y+4 > Grid[x].size() ))
	{
		std::cout << "Grid position error in Toad";
		return;
	}

	Grid[x][y+1] = true;
	Grid[x][y+2] = true;
	Grid[x][y+3] = true;
	Grid[x+1][y] = true;
	Grid[x+1][y+1] = true;
	Grid[x+1][y+2] = true;
}

void Beacon (std::vector<std::vector<bool> > &Grid, int x, int y)
{
	//  .......
	//  .OO....
	//  .OO....
	//  ...OO..
	//  ...OO..
	//  .......
	//
	if (DEBUG) std::cout << "Creating a Beacon at " << x << ", " << y << std::endl;
  if (  (x+4 > Grid.size() ) 
		 || (y+4 > Grid[x].size() ))
	{
		std::cout << "Grid position error in Beacon";
		return;
	}

	Grid[x][y] = true;
	Grid[x][y+1] = true;
	Grid[x+1][y] = true;
	Grid[x+1][y+1] = true;

	Grid[x+2][y+2] = true;
	Grid[x+2][y+3] = true;
	Grid[x+3][y+2] = true;
	Grid[x+3][y+3] = true;
}

void GosperGliderGun (std::vector<std::vector<bool> > &Grid, int x, int y)
{
	//            1         2         3         4
	//  01234567890123456789012345678901234567890
	//  -.........................................
	//  0..........................O..............
	//  1........................O.O..............
	//  2..............OO......OO............OO...
	//  3.............O...O....OO............OO...
	//  4..OO........O.....O...OO.................
	//  5..OO........O...O.OO....O.O..............
	//  6............O.....O.......O..............
	//  7.............O...O.......................
	//  8..............OO..........................
	//  9.........................................
	if (DEBUG) std::cout << "Creating a Glider Gun at " << x << ", " << y << std::endl;
  if (  (x+9 > Grid.size() ) 
		 || (y+36 > Grid[x].size()))
	{
		std::cout << "Grid position error in Glider Gun";
		return;
	}

	Grid[x][y+25] = true;
	Grid[x+1][y+23] = true;
	Grid[x+1][y+25] = true;

	Grid[x+2][y+13] = true;
	Grid[x+2][y+14] = true;
	Grid[x+2][y+21] = true;
	Grid[x+2][y+22] = true;
	Grid[x+2][y+35] = true;
	Grid[x+2][y+36] = true;

	Grid[x+3][y+12] = true;
	Grid[x+3][y+16] = true;
	Grid[x+3][y+21] = true;
	Grid[x+3][y+22] = true;
	Grid[x+3][y+35] = true;
	Grid[x+3][y+36] = true;

	Grid[x+4][y+1] = true;
	Grid[x+4][y+2] = true;
	Grid[x+4][y+11] = true;
	Grid[x+4][y+17] = true;
	Grid[x+4][y+21] = true;
	Grid[x+4][y+22] = true;

	Grid[x+5][y+1] = true;
	Grid[x+5][y+2] = true;
	Grid[x+5][y+11] = true;
	Grid[x+5][y+15] = true;
	Grid[x+5][y+17] = true;
	Grid[x+5][y+18] = true;
	Grid[x+5][y+23] = true;
	Grid[x+5][y+25] = true;

	Grid[x+6][y+11] = true;
	Grid[x+6][y+17] = true;
	Grid[x+6][y+25] = true;

	Grid[x+7][y+12] = true;
	Grid[x+7][y+16] = true;
	Grid[x+8][y+13] = true;
	Grid[x+8][y+14] = true;
}
