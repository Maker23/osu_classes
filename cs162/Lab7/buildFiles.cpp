#include <cfloat>
#include <climits>
#include <cstdio> // sprintf
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <vector>

#include "File.h"

// Prototypes
std::string getStringFromUser(std::string Prompt, std::string DefaultAnswer);
int getIntFromUser(std::string Prompt, int DefaultAnswer, int MinRange, int MaxRange );

/*****************************************************************/
int main()
{
	bool written = false;
	std::ofstream saveToFile;
	std::string tmpFilename = "";
	std::string DataDirectory = "DataFiles/"; // End with a slash please :)
	std::string inputFileName = getStringFromUser("File name for random number data", "Lab7Input");
	int sizeOfInput = getIntFromUser("How many random numbers do you want in your files?", 1000, 1, INT_MAX);

	DataFile * allFiles[4];
	int allFileCounter=0;

  int middlePosition = sizeOfInput / 2;

	std::vector <int> randNumbers (sizeOfInput, 0); // Create an 'empty' vector

	std::cout << "Generating " << sizeOfInput << " random numbers ... ";
  srand(time(NULL));
  for (int i=0; i< randNumbers.size(); i++)
	{
		randNumbers[i] =  (rand() % 9) + 1; // Numbers between 1 and 9
	}
	std::cout << "done" << std::endl;

  
	allFiles[allFileCounter++] = new DataFile("AtBeginning.txt", " at the beginning", 0);
	allFiles[allFileCounter++] = new DataFile("AtMiddle.txt", " at the middle", sizeOfInput/2);
	allFiles[allFileCounter++] = new DataFile("AtEnd.txt", " at the end", sizeOfInput-1);
	allFiles[allFileCounter++] = new DataFile("NotThere.txt", " not in the file ", -1);

  for (int n =0 ; n< allFileCounter; n++ )
	{
		tmpFilename = DataDirectory + inputFileName + allFiles[n]->Name();
		std::cout << "Writing file with " <<  SEARCH_TARGET << allFiles[n]->Prompt() << ":  " << tmpFilename << std::endl;
		int Position = allFiles[n]->TargetPosition();
		saveToFile.open(tmpFilename);
		written = false;
  	for (int i=0; i< randNumbers.size(); i++)
		{
			if ( !written && (Position >= 0 ) &&  i >= allFiles[n]->TargetPosition() ) 
			{
				saveToFile << 0 << std::endl;
				written = true;
			}
			saveToFile << randNumbers[i] << std::endl;
		}
		saveToFile.close();
	}
  for (int n=0 ; n< allFileCounter; n++ )
	{
		delete (allFiles[n]); // for the lolz
	}

}
/*****************************************************************/
std::string getStringFromUser(std::string Prompt, std::string DefaultAnswer)
{
	std::string tmpString = "";
	do
	{
		std::cout << Prompt ;
		if (DefaultAnswer.compare("") != 0 )
		{
			std::cout << " [" << DefaultAnswer << "]";
		}
		std::cout << ": ";
		getline(std::cin,tmpString);
		if ( (tmpString.compare("") == 0) && (DefaultAnswer.compare("") != 0 ))
		{
			tmpString = DefaultAnswer;
		}
	}
	while ( tmpString.compare("") == 0 );
	return (tmpString);
}
/*****************************************************************/
int getIntFromUser(std::string Prompt, int DefaultAnswer, int MinRange, int MaxRange )
{
	//std::stringstream ss;
	std::string tmpString = "";
	float tmpFloat = FLT_MIN;
	int tmpInt = INT_MIN;
	bool Good = false;

	do {
		std::cout << Prompt ;
		std::cout << " [" << DefaultAnswer << "]";
		std::cout << ": ";
		getline(std::cin,tmpString);
		if (tmpString.compare("") == 0) 
		{
			tmpFloat = DefaultAnswer;
			tmpInt = (int)tmpFloat;
			Good = true;
		}
		else 
		{
			std::stringstream ss(tmpString);
			ss << tmpString;
			ss >> tmpFloat;
			if ( ss.fail() )
			{
				std::cout << "Error: input \"" << tmpString << "\" was not a number; try again" << std::endl;
			}
			else {
				tmpInt = (int)tmpFloat;
				if ( (float)tmpInt != tmpFloat )
				{
					std::cout << "Error: input \"" << tmpFloat << "\" was not an integer; try again" << std::endl;
				}
				else
				{
					Good = true;
				}
			}
		}
	}
	while ( ! Good );


	return (tmpInt);
}
