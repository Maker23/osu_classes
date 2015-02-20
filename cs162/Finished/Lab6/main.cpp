#include <cstdio> // sprintf
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define DEBUG true

#define SEARCH_TARGET 0

enum MenuChoice {LinearSearch, BubbleSort, SelectionSort, BinarySearch, Quit, unknown};
char MenuOptions[] = {'L','U','S','B','Q'};

// The filenames are defined as globals simply to make it easier
// for the programmer to find and edit them.
#define NumSortInputFiles 4
std::string SortInputFile[] = {
	"DataFiles/SearchTargetAtBeginning.txt",
	"DataFiles/SearchTargetAtEnd.txt",
	"DataFiles/SearchTargetAtMiddle.txt",
	"DataFiles/SearchTargetNotThere.txt",
};
#define NumSearchInputFiles 4
std::string SearchInputFile[] = {
	"DataFiles/Sorted_SearchTargetAtBeginning.txt",
	"DataFiles/Sorted_SearchTargetAtEnd.txt",
	"DataFiles/Sorted_SearchTargetAtMiddle.txt",
	"DataFiles/Sorted_SearchTargetNotThere.txt",
};

// Prototypes
bool BinarySearchInFile(std::string inputFileName, int targetValue);
bool LinearSearchInFile(std::string inputFileName, int targetValue);
bool SelectionSortFile(std::string inputFileName, std::string outputFileName);
bool BubbleSortFile(std::string inputFileName, std::string outputFileName);
void RunAllLinearSearches(int targetValue);
void RunAllBinarySearches(int targetValue);
void RunAllBubbleSorts(std::string outputFileName);
void RunAllSelectionSorts(std::string outputFileName);
MenuChoice getUserMenuChoice();
std::string getStringFromUser(std::string Prompt, std::string DefaultAnswer);

/*****************************************************************/
int main()
{
	std::string outputFileName;
	std::string tmpString;
	MenuChoice nextChoice = Quit;
	
  // Enter the main menu and loop until quit
	do
	{
		nextChoice = getUserMenuChoice();
		switch (nextChoice){
			case LinearSearch:
				RunAllLinearSearches(SEARCH_TARGET); // Look for the search target in all files
				break;
			case BubbleSort:
				std::cout << "Bubble sort is not yet implemented; use Selection sort instead" << std::endl;
				//outputFileName = getStringFromUser("File name for sorted output", "BubbleSortOutput");
				//RunAllBubbleSorts(outputFileName);
				break;
			case SelectionSort:
				outputFileName = getStringFromUser("File name for sorted output", "SelectSortOutput");
				RunAllSelectionSorts(outputFileName);
				break;
			case BinarySearch:
				RunAllBinarySearches(SEARCH_TARGET); // Look for the search target in all files
				break;
			case Quit:
				break;
			default:
				std::cout << "Unrecognized command, try again" << std::endl;
				break;
		}
	}
	while (nextChoice != Quit);
}


/*****************************************************************/
void RunAllLinearSearches(int targetValue)
{
  for (int i=0; i<NumSortInputFiles; i++)
	{
		LinearSearchInFile(SortInputFile[i], targetValue);
	}
}

/*****************************************************************/
bool LinearSearchInFile(std::string inputFileName, int targetValue)
{
	std::ifstream inputStream;	
	std::string tmpString;
	int tmpInt;
	int lineCounter = 1;

	inputStream.open(inputFileName);
	if (! inputStream.good() )
	{
		std::cout << "ERROR: couldn't open " << inputFileName << std::endl;
		return false;
	}

	getline(inputStream, tmpString); // TODO: Change this to cin
	while ( inputStream.good() )
	{
		tmpInt = atoi(tmpString.c_str());

		if (tmpInt == targetValue)
		{
			std::cout << "Found " << targetValue << " at line " << lineCounter 
				<< " of " << inputFileName << std::endl;
			inputStream.close();
		  return true;
		}
		getline(inputStream, tmpString);
		lineCounter++;
	}
	std::cout << "Warning: did not find " << targetValue << " in "
				<< inputFileName << std::endl;
	inputStream.close();
	return false;// Did not find target value
  	
}
/*****************************************************************/
void RunAllBinarySearches(int targetValue)
{
  for (int i=0; i<NumSearchInputFiles; i++)
	{
		BinarySearchInFile(SearchInputFile[i], targetValue);
	}
}

bool BinarySearchInFile(std::string inputFileName, int targetValue)
{
	int inputInt;
	int startSearch;
	int endSearch;
	int midPoint;
	int counter = 1;
	bool found=false;
	std::ifstream inputStream;	
	std::vector <int> inputValue;


  // Create a vector with values from the file
	inputStream.open(inputFileName);
	if (! inputStream.good() )
	{
		std::cout << "ERROR: couldn't open " << inputFileName << std::endl;
		return false;
	}
	while ( inputStream >> inputInt)
	{
    inputValue.push_back(inputInt);
	}


  // Now search the vector
  startSearch = 0;
	endSearch = inputValue.size() - 1;
	midPoint = (((endSearch - startSearch) / 2) + startSearch);  // more or less
	while (!found && startSearch <= endSearch )
	{
		//std::cout << "     step # " << counter << "  startSearch = " << startSearch << ", midPoint = " <<midPoint<< ", endSearch = " << endSearch << std::endl;
		if (inputValue[midPoint] == targetValue ) {
			std::cout << "Found target value " << targetValue << " at position " 
				<< midPoint << " (" << counter << " step binary search of " 
				<< inputFileName << ")" << std::endl;
			found=true;
		}
		else if (inputValue[midPoint] > targetValue)
		{
			//std::cout << "high    value[midPoint] = " << inputValue[midPoint] << std::endl;;
			endSearch = midPoint-1;
		}
		else if (inputValue[midPoint] < targetValue)
		{
			//std::cout << "low     value[midPoint] = " << inputValue[midPoint] << std::endl;;
			startSearch = midPoint+1;
		}
		counter ++;
		midPoint = (((endSearch - startSearch) / 2) + startSearch);
		if (counter > 120 ) break; // this was useful while testing :)
	}
	if (!found)
		std::cout << "Did not find target value " << targetValue << " in " << counter 
			<< " steps, binary search of " << inputFileName << std::endl;

	return found;
}
/*****************************************************************/
void RunAllBubbleSorts(std::string outputFileName)
{
	std::string tmpString;
	char buffer[23];
  for (int i=0; i<NumSortInputFiles; i++)
	{
		sprintf(buffer,"%d", i);
		tmpString = outputFileName + '.' + buffer;
		BubbleSortFile(SortInputFile[i], tmpString);
	}
}
bool BubbleSortFile(std::string inputFileName, std::string outputFileName)
{
	// TODO
	std::cout << "Bubble sort is not yet implemented (input file " << inputFileName << ", output file " << outputFileName << ")" << std::endl;
}

/*****************************************************************/
void RunAllSelectionSorts(std::string outputFileName)
{
	std::string tmpString;
	char buffer[23];
  for (int i=0; i<NumSortInputFiles; i++)
	{
		sprintf(buffer,"%d", i);
		tmpString = outputFileName + '.' + buffer;
		SelectionSortFile(SortInputFile[i], tmpString);
	}
}
bool SelectionSortFile(std::string inputFileName, std::string outputFileName)
{
	std::vector <int> inputValue;
	std::ifstream inputStream;	
	std::ofstream outputStream;	
	std::string tmpString;
	int inputInt;
	int min = 0;
	int tmpInt;

	// Open both the input and output files
	inputStream.open(inputFileName);
	if (! inputStream.good() )
	{
		std::cout << "ERROR: couldn't open " << inputFileName << std::endl;
		return false;
  }
	outputStream.open(outputFileName);
	if (! outputStream.good() )
	{
		std::cout << "ERROR: couldn't open " << outputFileName << " for write" << std::endl;
		return false;
  }

  // Read the input file into a vector of integers
	getline(inputStream, tmpString);
	while ( inputStream.good() )
	{
		inputInt = atoi(tmpString.c_str()); // This is not ideal...
    inputValue.push_back(inputInt);
		getline(inputStream, tmpString);
	}

  // Now sort the vector, using the selection sort algorithm
	for (int counter = 0; counter < inputValue.size() -1; counter ++) 
	{
		min = counter;
  	for (int vectorIndex = counter+1 ; vectorIndex < inputValue.size(); vectorIndex++)
		{
			if (inputValue[vectorIndex] < inputValue[min] )
			{
				min = vectorIndex;
			}
		}
		tmpInt = inputValue[counter];
		inputValue[counter] = inputValue[min];
		inputValue[min] = tmpInt;
  }
  inputStream.close();

	if (DEBUG) std::cout << "Sorted vector = ";
	for (int counter = 0; counter < inputValue.size(); counter ++) 
	{
		if (DEBUG) std::cout << inputValue[counter] << " ";
		if ( outputStream.good() )
			outputStream << inputValue[counter] << std::endl;
	}
	if (DEBUG) std::cout << std::endl;

  outputStream.close();


}
/*****************************************************************/
//enum MenuChoice {LinearSearch, BubbleSort, SelectionSort, BinarySearch, Quit, unknown};
//char MenuOptions[] = {'L','U','S','I','Q'};
MenuChoice getUserMenuChoice()
{
	char menuOption;
	MenuChoice menuChoice;
	char inputBuffer[1024];

	std::cout << std::endl <<
		"[L]inear Search (four pre-existing files)" << std::endl <<
		"[B]inary Search (four pre-existing, pre-sorted files)" << std::endl <<
		"[S]election Sort (four pre-existing files)" << std::endl <<
		"[Q]uit the program" << std::endl << std::endl <<
		"What do you want to do? (L,I,S,Q): ";
  menuOption = std::cin.get(); // get the first character
	std::cin.getline(inputBuffer,1024); // throw away anything else they typed

	for (int i=0; i<5; i++)
	{
		if (toupper(menuOption) == MenuOptions[i])
		{
			menuChoice = (MenuChoice) i;
			return (menuChoice);
		}
	}
	return (unknown);
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
