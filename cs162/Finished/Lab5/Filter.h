#ifndef FILTER_H
#define FILTER_H

#include <iostream>
#include <fstream>

#ifdef DEBUG
#define LIB_DEBUG DEBUG
#else
#define LIB_DEBUG false
#endif // ifdef DEBUG


/* ********************************************** 
 *
 * Filter base class. Defines a no-op default constructor
 * and the virtual function doFilter, which will be
 * overridden in the derivative classes.
 *
 * ********************************************** */
class Filter {
private:
  virtual char transform(char const ch);

public:
  Filter() {};
	virtual void doFilter (std::ifstream &in, std::ofstream &out); // Required by the assignment
	virtual void doFilter (std::istream &in, std::ostream &out); // Useful for testing
};


/* ********************************************** 
 *
 * "Uppercase" derivative class.  Uses the base doFilter()
 * and an override for transform()
 *
 * ********************************************** */
class Uppercase:public Filter{
private:
	char transform(char const ch);
public:
	Uppercase() {};
};

/* ********************************************** 
 *
 * "Encrypt" derivative class.  Uses the base doFilter()
 * and an override for transform()
 *
 * Has a RotateBy value that sets the offset for the 
 * character substitution
 *
 * ********************************************** */
class Encrypt:public Filter{
private:
	int RotateBy;
	char transform(char const ch);
public:
	Encrypt() {};
	Encrypt(int _RotateBy);
	void setRotation(int _RotateBy) {RotateBy = _RotateBy;};
};

/* ********************************************** 
 *
 * "Cipher" derivative class.  Uses an override for transform(), 
 * and overrides for doFilter()
 *
 * Has RotateBy value that sets the offset for the character
 * substitution.
 *
 * Has wordCounter and lineCounter to break the text into 5-letter
 * chunks and 75-character lines.
 *
 * ********************************************** */
class Cipher:public Filter{
private:
	int wordCounter;
	int lineCounter;
	int RotateBy;
	char transform(char const ch);
public:
	Cipher(int _RotateBy);
	void doFilter (std::ifstream &in, std::ofstream &out); 
	void doFilter (std::istream &in, std::ostream &out);  // For testing
};

#endif   // FILTER_H
