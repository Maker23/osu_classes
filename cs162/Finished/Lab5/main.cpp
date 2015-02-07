#include <iostream>
#include <fstream>
#include <sstream>

#define DEBUG true
#include "Filter.h"

/* ********************************************************************** 
 *
 * CS162 Lab5. Shoshana Abrass <abrasss@onid.oregonstate.edu>  2/8/2015
 *
 * The supplied test file should test the various edge cases for
 * character encryption. 
 *
 * This program reads in the test input file and runs all four of the
 * assignment's filters, writing each to a separate output file.
 * "Cipher" is encrypted, uppercase, and broken into 5-letter blocks.
 *
 *   Filter          Output file
 *   ----------      --------------------
 *   <none>          Output_plain.txt
 *   Upper case      Output_uppercase.txt
 *   Encrypt         Output_encrypt.txt
 *   Cipher          Output_cipher.txt  
 *
 *
 * Design decisions that were made:
 *   When encrypting, leave non-letter character untransformed
 *   When ciphering, skip (remove) non-letter characters
 *
 *
 * TODO: Should Cipher handle numbers as well as letters?
 *       I don't think it's critical, messages to be encoded 
 *       could simply spell out numbers ("three point one four one")
 *
 */

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

  // Declare many filter instances  :)
	Filter myFilter;
	Uppercase myUppercase;
	Encrypt myEncrypt(39); 
	Cipher myCipher(13);


  // Run the plain copy filter into it's output file
	outputStream.open(plainCopyFile);
	if ( outputStream.good() )
	{
		resetStream(inputStream);
		myFilter.doFilter(inputStream, outputStream);
		outputStream.close();
	}

  // Uppercase filter, write to the apprpriate output file
	outputStream.open(uppercaseCopyFile);
	if ( outputStream.good() )
	{
		resetStream(inputStream);
		myUppercase.doFilter(inputStream, outputStream);
		outputStream.close();
	}

  // Encryption filter, write to the apprpriate output file
	outputStream.open(encryptCopyFile);
	if ( outputStream.good() )
	{
		resetStream(inputStream);
		myEncrypt.doFilter(inputStream, outputStream);
		outputStream.close();
	}

  // Cipher filter, write to the apprpriate output file
	// Cipher is encryption + uppercase + 5-letter chunks
	outputStream.open(cipherCopyFile);
	if ( outputStream.good() )
	{
		resetStream(inputStream);
		myCipher.doFilter(inputStream, outputStream);
		outputStream << std::endl;
		outputStream.close();
	}

}

/* Reset the input string by clearing the eof bit and seeking
 * back to the beginning of the file.
 * This allows us to read the same file over and over.
 */
void resetStream(std::ifstream &inputStream)
{
	inputStream.clear();
	inputStream.seekg(0,inputStream.beg);
}

