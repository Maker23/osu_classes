/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/10
 *  Last Modification date: 2014/10/12
 *  Filename: numGuess.cpp
 *
 *  Overview:
 *  a)	Ask one user to enter in the secret number to be guessed (you may 
 *  		decide the valid data type and range as the programmer)
 * 	b) 	Accept and store that number into a variable, 
 * 	c)	Use a loop to repeatedly do the following (you may choose how many 
 * 			guesses the user has):
 *  		i. Indicate what the range of possible numbers is so the user can make 
 *  				an informed guess!
 *  		ii. Tell the user how many guesses they have left,
 *  		iii. Ask the user to guess the secret number,
 *  		iv. Tell the user whether they are too high, too low, or correct
 *  		v. Change the range of numbers to reflect the effect that the user's 
 *  				newest guess had on the range of valid numbers,
 *  d)	Tells the 2nd user whether they got the number or ran out of guesses,
 *  		i. if the second user ran out of guesses, then the computer tells them:
 *  			1. what the secret number was,
 *  			2. how close their closest guess was,
 *  		ii. Otherwise prints congratulations.
 *  e)	Lets the users to play again (without terminating and restarting the 
 *  		program and without calling to the main function... more on that when 
 *  		we get to functions) if they want to (likely using a number or single 
 *  		letter to indicate yes or no)
 *
 *  Input:
 *  	secretNumber - From Player1, the number that Player2 will guess
 *	  latestGuess  - From Player2, an attempt to guess the secretNumber
 *
 *  Output:
 *  	Wordy prompts for Player1 and Player2
 *  	If win
 *  		Congratulation
 *		else
 *			Sad trombone. Print how close the guesser came
 *		Prompt to play again
 */
#include <iostream>
#include <string>
#include <climits>

#define MIN_NUMBER	1			// The lowest playing number
#define MAX_NUMBER	100		// The highest playing number
#define NUM_GUESSES	5			// How many chances to guess Player2 has
#define CLEAR_LINES	80		// How many <CR>s to print, to clear the scren

// A sad little routine to clear the screen
void ClearScreen(int numLines=CLEAR_LINES);	

// Validate that the user has typed an integer; optionally, within a range.
// If no range is specified use the system INT_MIN and INT_MAX
int ValidateIntegerInput (int Minval=INT_MIN, int Maxval=INT_MAX);

// Handle the guessing logic here
bool GuessTheNumber (int secretNumber, int maxTries, 
	int Minval=INT_MIN, int Maxval=INT_MAX);

// Using a global, not sure how to return two values from a function yet
int howClose;

int main () 
{
	int secretNumber;		// Player1's input, for Player2 to guess
	char answer = 'n';	// Whether or not to play again.

  do
	{
		std::cout << "PLAYER 1: Choose your secret number\n";
		secretNumber = ValidateIntegerInput(MIN_NUMBER,MAX_NUMBER);
  	ClearScreen();
		std::cout << "PLAYER 2: Try to guess the secret number!!\n";

		if ( GuessTheNumber(secretNumber, NUM_GUESSES, MIN_NUMBER, MAX_NUMBER)) 
		{
			std::cout << "Congratulations!  You guessed the secret number!!\n";
		}
		else 
		{
			std::cout << "Oh noes! <sad trombone> For the record, the secret "
				<< "number was " << secretNumber << ".\n You came " <<
		  	howClose << " away from guessing\n";
		}
		std::cin.ignore(10000, '\n');	// Throw away any random chars left in cin
		std::cout << "Do you want to play again? [y|n] ";
		std::cin.get(answer);
	}
	while ( answer == 'y' );	// TODO: better checking for non-y values

	return 0;
}

/***********************************************************************
 * GuessTheNumber
 *
 * 		Purpose:
 * 			Prompt the user through guessing a secret number
 * 		Input:
 * 			secretNumber:  The number that the user needs to guess
 * 			maxTries:  How many guessing tries the user is allowed
 * 			Minval:  Lowest number in the guessing range
 * 			Maxval:	Highest number in the guessing range
 * 		Output:
 * 			bool: True if the user guesse successfully, otherwise false
 *
 **********************************************************************/
bool GuessTheNumber (int secretNumber, int maxTries, int Minval, int Maxval)
{
	int numberOfGuesses = 0;	// Track of how many guesses have been made
	int currentMin = Minval;	// The current lower bound for guessing
	int currentMax = Maxval;	// The current upper bound for guessing
	int currentGuess = 0;			// The player's guess input

	std::cout << "Player1 has thought of a number between " << Minval << 
		" and " << Maxval << "\n";
  do 
	{
		if (numberOfGuesses >= maxTries )
		{
			std::cout << "\nSorry, you're out of guesses!\n";
			((secretNumber - currentMin) < (currentMax - secretNumber)) ?
				howClose = (secretNumber - currentMin):
				howClose = (currentMax - secretNumber);
			return false;
		}
		if (numberOfGuesses){
			std::cout << "Keep trying! You have " << (maxTries - numberOfGuesses) << " guesses left. ";
			if ( currentMin != Minval )
				std::cout << "\nYou now know that " << currentMin << " is the lower bound.\n";
			if ( currentMax != Maxval )
				std::cout << "\nYou now know that " << currentMax << " is the upper bound.\n";
		}
		else
		{
			std::cout << "You have " << maxTries << " guesses. ";
		}
		currentGuess = ValidateIntegerInput (currentMin, currentMax);

		if ( currentGuess > secretNumber )
		{
			std::cout << "That number is too high. ";
			if ( currentGuess < currentMax )
				currentMax = currentGuess - 1;
		}

		if ( currentGuess < secretNumber )
		{
			std::cout << "That number is too low. ";
			if ( currentGuess > currentMin )
				currentMin = currentGuess + 1;
		}
		numberOfGuesses ++;
	}
	while (currentGuess != secretNumber);

	return true;
}

/***********************************************************************
 * ClearScreen
 *
 * 		Purpose:
 * 			Clear the screen to hide Player1's input
 * 		Input:
 * 			Optional: number of lines to clear
 * 		Output:
 * 			None.
 *
 **********************************************************************/
void ClearScreen(int numLines)
{
	std::string blankLines;
	std::cout << blankLines.assign(numLines, '\n');
	return;
}

/***********************************************************************
 * ValidateIntegerInput
 * 		
 * 		Purpose:
 * 			Confirm that the user has input a valid integer;
 * 			optionally within a range.
 * 			If no range is given use system INT_MIN/INT_MAX
 * 		Input:
 * 			Optional: Max and Min range of valid numbers
 * 		Output:
 * 			int: A validated integer
 *
 **********************************************************************/
int ValidateIntegerInput(int Minval, int Maxval)
{
	int numericValue = 0;	// The input value that will be validated
	bool success = false;	// Keep looping until we detect a valid number

	while (! success) 
	{
		std::cout << "Enter an integer between " << Minval << " and " << Maxval << ": ";
		std::cin >> numericValue;
		while (! std::cin )
		{
			std::cout << "That was not a valid integer\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Enter an integer between " << Minval << " and " << Maxval << ": ";
			std::cin >> numericValue;
		}
	  if (numericValue >= Minval && numericValue <= Maxval)
		{
			success = true;
		}
		else 
		{
			std::cout << "Number is outside valid range.\n";
		}
	}
	return numericValue;
}
