#include <iostream>
#include <fstream>
#include <sstream>

#define DEBUG false
#include "Filter.h"

void resetStream(std::ifstream &inputStream);
void fileCopy(std::ifstream &inputStream, std::ostream &outputStream, Filter *myFilter);

int main() {
	char inputChar;
  std::string inputFile = "testInput.txt";

	std::ofstream outputStream;


  std::ifstream inputStream(inputFile);
	if (!inputStream.good() )
	{
		std::cout << "Could not open " << inputFile << "; exiting..." << std::endl;
		return(1);
	}
	else
	{
		std::cout << "Reading from " << inputFile << std::endl;
	}

  // Declare many filter instances
	Filter myFilter;
	Uppercase myUppercase;
	Encrypt myEncrypt(39);
	Cipher myCipher(13);

	std::cout << "Plain copy ===================================" << std::endl;;
  fileCopy(inputStream, std::cout, &myFilter);
	std::cout << "Uppercase ====================================" << std::endl;;
  fileCopy(inputStream, std::cout, &myUppercase);
	std::cout << "Encryption ===================================" << std::endl;;
  fileCopy(inputStream, std::cout, &myEncrypt);
	std::cout << "Cipher =======================================" << std::endl;;
	resetStream(inputStream);
	myCipher.doFilter(inputStream, std::cout);

}

void resetStream(std::ifstream &inputStream)
{
	std::cout << std::endl;
	inputStream.clear();
	inputStream.seekg(0,inputStream.beg);
}

void fileCopy(std::ifstream &inputStream, std::ostream &outputStream, Filter *myFilter)
{
	resetStream(inputStream);
	if (inputStream.good()){
		myFilter->doFilter(inputStream, outputStream);
	}
}

