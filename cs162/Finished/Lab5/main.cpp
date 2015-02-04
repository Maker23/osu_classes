#include <iostream>
#include <fstream>
#include <sstream>

#define DEBUG false
#include "Filter.h"

int main() {

	char inputChar;
  std::string inputWord;
	std::stringstream ss;


	Filter myFilter;
	Cipher myCipher(13);
	Encrypt myEncrypt(39);
	Uppercase myUppercase;
 
	std::cout << "Enter a line of text: ";
  getline (std::cin, inputWord);

	std::cout << "Plaintext = ";
	ss << inputWord;
	myFilter.doFilter(ss, std::cout);
	std::cout << std::endl;
	ss.clear();

	std::cout << "Encrypt = ";
	ss << inputWord;
	myEncrypt.doFilter(ss, std::cout);
	std::cout << std::endl;
	ss.clear();

	std::cout << "Uppercase = ";
	ss << inputWord;
	myUppercase.doFilter(ss, std::cout);
	std::cout << std::endl;
	ss.clear();

	std::cout << "Cipher = ";
	ss << inputWord;
	myCipher.doFilter(ss, std::cout);
	std::cout << std::endl;
	ss.clear();


}

