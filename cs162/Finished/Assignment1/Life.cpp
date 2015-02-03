/* vim: ts=2
 *
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2015/01/05
 *  Filename: Life.cpp
 *
 *  Overview:
 *    An ascii implementation of Conway's Game of Life that runs in a terminal.
 *
 *    This file contains the main() function, a loop that runs a user-given 
 *    number of generations. User input for game setup is also handled in this
 *    file, also the core logic of the game that calculates cell state changes.
 *
 *  Depends on:
 *    LifeForms.cpp		A library of 'organism' patterns: blinker, toad, etc
 *    validateIntegerInput.cpp		Confirms that user input is a valid integer
 */

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>  // for usleep

#define EDGE_MARGIN 36	// The size of the largest seed LifeForm

#define HEIGHT 22
#define WIDTH 80
#define ROWS (HEIGHT + (2*EDGE_MARGIN))
#define COLS (WIDTH + (2*EDGE_MARGIN))

#define DEBUG false

#include "LifeForms.h" // organism library
#include "validateIntegerInput.h" // overly complicated nonsense

void calculateNextGeneration(std::vector<std::vector<bool> > *Grid);
void initializeGrid(std::vector<std::vector<bool> > &Grid);
void displayGrid(std::vector<std::vector<bool> > &Grid, int generation_counter);
void zeroGrid(std::vector<std::vector<bool> > &Grid, int Rows, int Cols);

int main () 
{
	int full_generation_counter=0;
	int segment_generation_counter=0;
	int target_generations=0;
	std::string inputString = "";
	std::vector<std::vector<bool> > gameGrid;

	zeroGrid(gameGrid, ROWS, COLS); // includes margin around all edges
	initializeGrid(gameGrid); // TODO: Take user input

	displayGrid(gameGrid, full_generation_counter++);

	do {
		std::cout << "How many generations do you want to see?" << std::endl;
			//<< "Enter 0 to quit  [0-50]: ";
		//std::getline(std::cin,inputString);
		target_generations = validateIntegerInput(0,500,2,"Enter 0 to quit [0-500]: "); //TODO: Retry on error

		//target_generations = validateIntegerInput(inputString.c_str(),0,50); //TODO: Retry on error

  	while (segment_generation_counter < target_generations)
		{
			calculateNextGeneration(&gameGrid);
			displayGrid(gameGrid, full_generation_counter++);
			segment_generation_counter++;
			usleep(200000);
		}
		segment_generation_counter=0;
  }
	while (target_generations > 0);

}

/*************************************************************************
 * calculateNextGeneration
 *
 * Purpose: performs the core logic of the Game of Life algorithm.
 *          Counts neighbor cells and plans the next generation; updates
 *          the entire grid at the end of the calculation.
 * 	
 * Arguments: A pointer to a game grid. The grid is modified in place.
 *
 ************************************************************************/

void calculateNextGeneration(std::vector<std::vector<bool> > *Grid)
{
	std::vector<std::vector<bool> > nextGeneration;
	zeroGrid(nextGeneration, ROWS, COLS);

  if (DEBUG) std::cout << "Entering calcNexGen" << std::endl;
  int neighbors = 0;

	for (int x=0; x < (*Grid).size(); x++)
	{
		for (int y=0; y < (*Grid)[x].size(); y++)
		{
			//if (DEBUG) std::cout << "Examining neighbors of Grid[" << x << "][" << y << "]" << std::endl;
			neighbors = 0;
			for (int r = x-1; r <= x+1; r++ )
			{
				if (r < 0 ) continue;
				if (r > ROWS-1 ) continue;
				for (int q = y-1; q <= y+1; q++ )
				{
					if (q < 0 ) continue;
					if (q > COLS-1 ) continue;
					if ( r==x & q==y) continue;
					if ( (*Grid)[r][q]) neighbors++;
				}
			}
			if ((*Grid)[x][y]) 
			{
				if (neighbors < 2 ) 
				{
					// Die of loneliness
					if (DEBUG) std::cout << "point [" << x << "][" << y << "] is dying of loneliness, neighbors = " 
						<< neighbors << std::endl;
				  nextGeneration[x][y] = false;
				}
				else if (neighbors > 3)
				{
					// Die of overcrowding
					if (DEBUG) std::cout << "point [" << x << "][" << y << "] is dying of overcrowding, neighbors = " 
						<< neighbors << std::endl;
				  nextGeneration[x][y] = false;
				}
				else 
				{
					nextGeneration[x][y] = (*Grid)[x][y];
				}
			}
			else
			{
				if (neighbors == 3)
				{
					// Birth
					if (DEBUG) std::cout << "point [" << x << "][" << y << "] is being born" << std::endl;
				  nextGeneration[x][y] = true;
				}
				else 
				{
					nextGeneration[x][y] = (*Grid)[x][y];
				}
			}
		}
	}
  if (DEBUG) std::cout << "Setting pointer things" << std::endl;
	(*Grid) = nextGeneration;
  if (DEBUG) std::cout << "Exiting calcNexGen" << std::endl;

}
/*************************************************************************
 * initializeGride
 *
 * Purpose: Seeds a grid with pre-defined patterns as chosen by user input.
 * 	
 * Arguments: A pointer to a game grid. The grid is modified in place.
 *
 ************************************************************************/

void initializeGrid(std::vector<std::vector<bool> > &Grid)
{

	if (DEBUG) std::cout << "Entering initializeGrid" << std::endl;

	int nextChoice = 0;
	int xPos = 0;
	int yPos = 0;
	std::cout << "Choose one or more patterns to seed the grid:" << std::endl
		<< "  1     Programmer's mix" << std::endl
		<< "  2     Glider" << std::endl
		<< "  3     Blinker" << std::endl
		<< "  4     Beacon" << std::endl
		<< "  5     Toad" << std::endl
		<< "  6     Glider Gun" << std::endl;
	do
	{
		nextChoice = validateIntegerInput(0,6,1,"Enter 0 when finished [0-6]: ");
		if (nextChoice > 1) {
			std::cout << "Enter X Y coordinates for the pattern's upper-left corner." << std::endl;
			std::cout << "X [1-" << WIDTH << "]: ";
			yPos = validateIntegerInput(1,WIDTH,1,""); //TODO: Retry on error
			std::cout << "Y [1-" << HEIGHT << "]: ";
			xPos = validateIntegerInput(1,HEIGHT ,1,""); //TODO: Retry on error
		}
		switch (nextChoice){
			case 0:
				break;
			case 1:
				GosperGliderGun(Grid,1 + EDGE_MARGIN,10 + EDGE_MARGIN);
				Glider(Grid, 14 + EDGE_MARGIN, 6 + EDGE_MARGIN);
				Toad(Grid, 6 + EDGE_MARGIN, 44 + EDGE_MARGIN);
				Beacon(Grid, 15 + EDGE_MARGIN, 42 + EDGE_MARGIN);
				Blinker(Grid, 4 + EDGE_MARGIN, 6 + EDGE_MARGIN);
				break;
			case 2:
				Glider(Grid, xPos - 1 + EDGE_MARGIN, yPos - 1 + EDGE_MARGIN);
				break;
			case 3:
				Blinker(Grid, xPos - 1 + EDGE_MARGIN, yPos - 1 + EDGE_MARGIN);
				break;
			case 4:
				Beacon(Grid, xPos - 1 + EDGE_MARGIN, yPos - 1 + EDGE_MARGIN);
				break;
			case 5:
				Toad(Grid, xPos - 1 + EDGE_MARGIN, yPos - 1 + EDGE_MARGIN);
				break;
			case 6:
				GosperGliderGun(Grid, xPos - 1 + EDGE_MARGIN, yPos - 1 + EDGE_MARGIN);
				break;
			default:
				nextChoice = 7;
				break;
		}
	}
	while (nextChoice > 0);
	if (DEBUG) std::cout << "Exiting initializeGrid" << std::endl;
}


/*************************************************************************
 * displayGrid
 *
 * Purpose: Prints the grid. Converts the grid's bool values to ascii
 *          characters and uses std::cout to print to the terminal
 * 	
 * Arguments: A game grid, and a generational counter which is also printed
 *            so the user can see how many generations have passed.
 *
 ************************************************************************/

void displayGrid(std::vector<std::vector<bool> > &Grid, int generation_counter)
{

  if (DEBUG) std::cout << "Entering displayGrid" << std::endl;

	std::cout << "==== Generation " << generation_counter << " ====================" << std::endl;
	for (int x=EDGE_MARGIN; x < (Grid.size() - EDGE_MARGIN); x++)
	{
		for (int y=EDGE_MARGIN; y < (Grid[x].size() - EDGE_MARGIN); y++)
		{
			if ( Grid[x][y])
			{
				std::cout << 'O';
			}
			else
			{
				std::cout << '.';
			}
		}
		std::cout << std::endl;
	}
}
/*************************************************************************
 * zeroGrid
 *
 * Purpose: Allocates and initializes a game grid.
 * 	
 * Arguments: A game grid, and integers for size in Rows/Cols 
 *            The grid is passed by reference and is modified in place.
 *            The size of the grid is set to Rows*Cols and each element
 *            is initialized to false.
 *
 ************************************************************************/

void zeroGrid(std::vector<std::vector<bool> > &Grid, int Rows, int Cols)
{
	if (DEBUG) std::cout << "Entering zeroGrid" << std::endl;
	std::vector <std::vector <bool>> TmpGrid(Rows); // declare and allocate
	std::vector <bool> TmpRow (Cols, false); //declare, allocate, initialize

	for (int x=0; x <  Rows; x++)
	{
		//if (DEBUG) std::cout << "Allocating row" << x << std::endl;
		TmpGrid[x] = TmpRow;
	}
	Grid = TmpGrid; // one massive allocate/copy
	if (DEBUG) std::cout << "Exiting zeroGrid" << std::endl;
}
