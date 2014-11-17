/* vim: ts=2
 *
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/11/09
 *  Last Modification date: 2014/11/16
 *  Filename: ticTacToe.cpp
 *
 *  Overview:
 * 	Write a program that allows two people to play a game of tic-tac-toe.
 * 	Use a	3x3 array to represent the board. Display which player’s turn it
 * 	is, allow them to specify a square (as a pair of coordinates, first row
 * 	then column), and display the new state of the board. If one of the
 * 	players makes a winning move, declare that player the winner. If the
 * 	board becomes full and neither player has won, declare it a tie. 
 *
 * 	When running your program, allow the user to specify how many games
 * 	they want to play as a command line argument. Your program should let
 * 	them play that many games and then display how many games each player
 * 	has won and declare the overall winner (or tie). If the user does not
 * 	specify a command line argument the program should just play one game.
 * 	In a series of games, players X and O should switch who plays first.
 *
 */

#include <iostream>
#include "_validateIntegerInput.cpp"


#include <string>

#define DEBUG false
#define GRIDSIZE 3  // Size of a tic-tac-toe grid
#define X 88
#define O 79
#define DOT 46


void	initializeGrid(int gameGrid[][GRIDSIZE]);
void  printGrid(int gameGrid[][GRIDSIZE]);
void  takeATurn(int gameGrid[][GRIDSIZE], int Player);
bool	freeSpotsRemain(int gameGrid[][GRIDSIZE]);
int  	isThereAWinner(int gameGrid[][GRIDSIZE]);
void 	printUsage(char **argv);
int 	parseArguments(int argc, char **argv, int *arrayLen);

// TODO: comment everything
//
int main (int argc, char **argv)
{
	int gameGrid[GRIDSIZE][GRIDSIZE]; // The game grid
	int whichPlayer=0;	// Alternate between the two players
	int gamesPlayed=0;	// How many games have we played so far
	int totalGames;	  	// How many games are we going to play
	int winner = 0;			// Store the latest game winner
  int winsX = 0;			// Count the wins for X
	int winsO = 0;			// Count the wins for O

	if (parseArguments(argc, argv, &totalGames))
	{
		printUsage(argv); // Bad arguments?  Explain and exit
		return(1);
	}
	
	// Play one or more games of tic-tac-toe
	do {
		// Print the game header; initialize variables; print instructions
		if  (totalGames > 1)
			std::cout << std::endl 
				<< "=========" << std::endl 
				<< "Game # " << gamesPlayed+1 << std::endl 
				<< "=========" << std::endl;
		initializeGrid(gameGrid);
		winner = 0;
		if ((gamesPlayed%2)==0)
			whichPlayer=1; // Every other games starts with player O
		std::cout << "Enter moves by row then column" << std::endl;

		// Play one game
		do
		{
			if ( ! freeSpotsRemain(gameGrid)) 
			{
				break; // end this game
			}
			printGrid(gameGrid);
			if (whichPlayer)
				takeATurn(gameGrid, X);
			else
				takeATurn(gameGrid, O);
			whichPlayer = 1 - whichPlayer;	// Switch back and forth
		}
		while (! (winner = isThereAWinner(gameGrid)));

    // Announce the winner, if any (if not a tie).
		// If more than one game is being played, track each player's wins
		printGrid(gameGrid); // show the final result
		gamesPlayed++;
		if ( winner )
		{
			std::cout << "We have a winner! Congratulations player " 
			<< (char) winner << "!" << std::endl;
			switch (winner){
				case X:
					winsX ++; break;
				case O:
					winsO ++; break;
			}
		}
		else
		{
				std::cout << "Looks like it's a tie!" << std::endl;
		}
	}
	while (gamesPlayed < totalGames);

	// If we played more than one game, announce the overall winner
	if (totalGames > 1) 
	{
		if (winsX > winsO)
			std::cout << "X is the overall winner (" << winsX << " to " << winsO << ")"
				<< std::endl;
		else if (winsX < winsO)
			std::cout << "O is the overall winner (" << winsO << " to " << winsX << ")"
				<< std::endl;
	  else
			std::cout << "It's a tie - both players won " << winsO << " game";
			winsO==1 ? std::cout << std::endl : std::cout << "s" << std::endl;
	}
}

/*********************************************************************
 *
 *
 ********************************************************************/
void	initializeGrid(int gameGrid[][GRIDSIZE])
{
	for (int i = 0; i < GRIDSIZE; i++)
	{
		for (int j = 0; j < GRIDSIZE; j++)
		{
			gameGrid[i][j] = DOT;
		}
	}
}
/*********************************************************************
 *
 *
 ********************************************************************/
bool	freeSpotsRemain(int gameGrid[][GRIDSIZE])
{
	for (int i = 0; i < GRIDSIZE; i++)
	{
		for (int j = 0; j < GRIDSIZE; j++)
		{
			if ( gameGrid[i][j] == DOT)
			{
				return (true);
			}
		}
	}
	return(false);
}
/*********************************************************************
 *
 *
 ********************************************************************/
void  printGrid(int gameGrid[][GRIDSIZE])
{
	std::cout << "  0 1 2" << std::endl;
	for (int i = 0; i < GRIDSIZE; i++)
	{
		std::cout << i << " ";
		for (int j = 0; j < GRIDSIZE; j++)
		{
			std::cout << (char) gameGrid[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
/*********************************************************************
 *
 *
 ********************************************************************/
void  takeATurn(int gameGrid[][GRIDSIZE], int Player)
{
	std::string moveString = "";
	bool goodMove = false;
	bool freeSpot = false;
	int Move[2];
	do {
		do { 
			std::cout << "Player " << (char)Player << ", make your move: ";
			goodMove = getIntegerInput (Move, 2, 0, GRIDSIZE-1);
		}
		while (goodMove == false);

		if ( gameGrid[Move[0]][Move[1]] == DOT )
			freeSpot = true;
		else 
			std::cout << "That spot is already taken. Remember, row then column."
				<< std::endl;
	}
	while (freeSpot == false);
	
	gameGrid[Move[0]][Move[1]] = Player;
}
/*********************************************************************
 *
 *
 ********************************************************************/
int  isThereAWinner(int gameGrid[][GRIDSIZE])
{
  int winner = 0;

	for (int i = 0; i < GRIDSIZE; i++)
	{
		// Check rows and columns
		if ( gameGrid[i][0] != DOT) 
		{
			if ((gameGrid[i][0] == gameGrid[i][1])
				&&(gameGrid[i][0] == gameGrid[i][2]))
					return(gameGrid[i][0]);
		}
		if ( gameGrid[0][i] != DOT) 
		{
			if ((gameGrid[0][i] == gameGrid[1][i])
				&&(gameGrid[0][i] == gameGrid[2][i]))
					return(gameGrid[0][i]);
		}
	}
	// Check diagonals
	if ( gameGrid[0][0] != DOT) 
		if ((gameGrid[0][0] == gameGrid[1][1])
			&&(gameGrid[0][0] == gameGrid[2][2]))
			return(gameGrid[0][0]);
	if ( gameGrid[0][2] != DOT) 
		if ((gameGrid[0][2] == gameGrid[1][1])
			&&(gameGrid[0][2] == gameGrid[2][0]))
			return(gameGrid[0][0]);

	return(0);
}
/*********************************************************************
 *
 *
 ********************************************************************/
int parseArguments(int argc, char **argv, int *totalGames)
{
		int i;

		if (argc > 2)
		{
			return(1);
		}
		if (argc == 1)
		{
		  *totalGames=1;	
			return(0);
		}
		if (argc == 2){
		 	*totalGames = validateIntegerInput(argv[1],1,10);
		  if (*totalGames < 1) return(1);
		}	
		return(0);
}
/*********************************************************************
 *
 *
 ********************************************************************/
void printUsage(char **argv)
{
	std::cout << 
		"USAGE: " << argv[0] << " [1 - 10]" << std::endl <<
		"WHICH: Will play one or more games of two-player tic-tac-toe" <<std::endl << 
		" " << std::endl <<
		"       Use the optional argument to play more than one game, up to 10" 
		<< std::endl;
}
