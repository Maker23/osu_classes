// vi:ts=2

#include <iostream>
#include <cstdlib>


void sortIntegers(int *a, int *b, int *c);

int main ()
{
	int intA=15;
	int intB=-6;
	int intC=3;

  std::cout << "Before sorting:" << std::endl
		<< "A = " << intA << std::endl
		<< "B = " << intB << std::endl
		<< "C = " << intC << std::endl;

  sortIntegers(&intA,&intB,&intC);

  std::cout << "After sorting:" << std::endl
		<< "A = " << intA << std::endl
		<< "B = " << intB << std::endl
		<< "C = " << intC << std::endl;
}

void sortIntegers(int *argA, int *argB, int *argC)
{
	int tmp=0;

	if ( *argA > *argC ) {
		tmp=*argA;
		*argA=*argC;
		*argC=tmp;
	}
	if ( *argB > *argC ) {
		tmp=*argB;
		*argB=*argC;
		*argC=tmp;
	}
	if ( *argA > *argB ) {
		tmp=*argA;
		*argA=*argB;
		*argB=tmp;
	}
}
