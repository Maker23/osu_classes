#ifndef FILTER_H
#define FILTER_H

#include <iostream>
#include <fstream>

#ifdef DEBUG
#define LIB_DEBUG DEBUG
#else
#define LIB_DEBUG false
#endif // ifdef DEBUG


/* ********************************************** */
class Filter {
private:
  virtual char transform(char const ch);

public:
  Filter() {};
	virtual void doFilter (std::ifstream &in, std::ofstream &out); // Required by the assignment
	virtual void doFilter (std::istream &in, std::ostream &out); // Useful for testing
};



/* ********************************************** */
class Uppercase:public Filter{
private:
	char transform(char const ch);
public:
	Uppercase() {};
};

/* ********************************************** */
class Encrypt:public Filter{
private:
	int RotateBy;
	char transform(char const ch);
public:
	Encrypt() {};
	Encrypt(int _RotateBy);
	void setRotation(int _RotateBy) {RotateBy = _RotateBy;};
};

class Cipher:public Filter{
private:
	int charPosition;
	int RotateBy;
	char transform(char const ch);
public:
	Cipher(int _RotateBy) {charPosition = 0; RotateBy=_RotateBy;};
	void doFilter (std::ifstream &in, std::ofstream &out); 
	void doFilter (std::ifstream &in, std::ostream &out);  // For testing
};


#endif   // FILTER_H
