#include "Filter.h"

// Basic file filter member function
void Filter::doFilter(std::ifstream &in, std::ofstream &out)
{
	char inputChar;

	while ( in.get(inputChar))
	{
		out.put(transform(inputChar));
	}

}

// Member function that works on non-file streams
// Used for testing
void Filter::doFilter(std::istream &in, std::ostream &out)
{
	char inputChar;

	while ( in.get(inputChar))
	{
		out.put(transform(inputChar));
	}

}

char Filter::transform(const char inChar)
{
	//if (LIB_DEBUG) std::cout << "Base class transform" << std::endl;
	return(inChar); // Default filter does nothing
}

/* ********************************************************************* 
 *
 *
 * *********************************************************************/
Encrypt::Encrypt (int _RotateBy)
{
	if (LIB_DEBUG) std::cout << "Encrypt constructor " << std::endl;
	RotateBy = _RotateBy;
}

char Encrypt::transform (const char inChar)
{
	int charValue = (int) inChar;
	int asciiOffset = 0;

  if (charValue >=65 && charValue <= 90) {
		asciiOffset = 65;
	}
	else if (charValue >=97 && charValue <= 122) {
		asciiOffset = 97;
	}

	return(
		(asciiOffset > 0) ? 
			((char) (((charValue - asciiOffset) + RotateBy) % 26 + asciiOffset)) :
			(inChar));

}

/* ********************************************************************* */
char Uppercase::transform (const char inChar)
{
	return((char)toupper((int)inChar));
}
/* ********************************************************************* */

Cipher::Cipher(int _RotateBy) 
{
	wordCounter = 0;
	lineCounter = 0;
	RotateBy=_RotateBy;
}

void Cipher::doFilter(std::istream &in, std::ostream &out)
{
	char inputChar;

	while ( in.get(inputChar))
	{
		if ((int) inputChar <= 32 || (int)inputChar == 127) {
			continue; // Discard control characters, whitespace, and Delete
			// Keeping punctuation for now, pending reply to a question on Canvas
		}
		out.put(transform(inputChar));
		wordCounter++;
		lineCounter++;
		if (wordCounter >4)
		{
			if ( lineCounter > 74 )
			{
				out.put(10); // Line Feed
			 	lineCounter = 0;
			}
			else
			{
				out.put(' ');
			}
			wordCounter = 0;
		}
	}
}

void Cipher::doFilter(std::ifstream &in, std::ofstream &out)
{
	char inputChar;

	while ( in.get(inputChar))
	{
		if ((int) inputChar <= 32 || (int)inputChar == 127) {
			continue; // Discard control characters, whitespace, and Delete
			// Keeping punctuation for now, pending reply to a question on Canvas
		}
		out.put(transform(inputChar));
		wordCounter++;
		lineCounter++;
		if (wordCounter >4)
		{
			if ( lineCounter > 74 )
			{
				out.put(10); // Line Feed
			 	lineCounter = 0;
			}
			else 
			{
				out.put(' ');
			}
			wordCounter = 0;
		}
	}
}

char Cipher::transform(const char inChar)
{
	int charValue = (int) inChar;
	int asciiOffset = 0;

  if (charValue >=65 && charValue <= 90) {
		asciiOffset = 65;
	}
	else if (charValue >=97 && charValue <= 122) {
		asciiOffset = 97;
	}

	return(
		(asciiOffset > 0) ? 
			((char)toupper(((charValue - asciiOffset) + RotateBy) % 26 + asciiOffset)) :
			(char)toupper((int)(inChar)));

}
