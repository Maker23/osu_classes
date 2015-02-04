#include <iostream>
#include <fstream>
#include <sstream>

#define DEBUG true
#include "Filter.h"

void resetStream(std::ifstream &inputStream);

int main() {
	char inputChar;
  std::string inputFile = "testInput.txt";
  std::string plainCopyFile = "Output_plain.txt";
  std::string uppercaseCopyFile = "Output_uppercase.txt";
  std::string encryptCopyFile = "Output_encrypt.txt";
  std::string cipherCopyFile = "Output_cipher.txt";

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

	outputStream.open(plainCopyFile);
	if ( outputStream.good() )
	{
		resetStream(inputStream);
		myFilter.doFilter(inputStream, outputStream);
		outputStream.close();
	}

	outputStream.open(uppercaseCopyFile);
	if ( outputStream.good() )
	{
		resetStream(inputStream);
		myUppercase.doFilter(inputStream, outputStream);
		outputStream.close();
	}

	outputStream.open(encryptCopyFile);
	if ( outputStream.good() )
	{
		resetStream(inputStream);
		myEncrypt.doFilter(inputStream, outputStream);
		outputStream.close();
	}

	outputStream.open(cipherCopyFile);
	if ( outputStream.good() )
	{
		resetStream(inputStream);
		myCipher.doFilter(inputStream, outputStream);
		outputStream.close();
	}


}

void resetStream(std::ifstream &inputStream)
{
	inputStream.clear();
	inputStream.seekg(0,inputStream.beg);
}

