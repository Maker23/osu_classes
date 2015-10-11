/* CS261- Assignment 1 - Q.2 */
/* Name:Shoshana Abrass, abrasss@oregonstate.edu
 * Date: 2015-10-07
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){

    /*Set a to double its original value*/
		*a = 2 * *a;
    
    /*Set b to half its original value*/
		*b = *b / 2;
    
    /*Assign a+b to c*/
		c = *a + *b;
    
    /*Return c*/
		return (c);
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
		int f;
		int x = 5,y = 6,z=7;

    /*Print the values of x, y and z*/
		printf ("x = %d, y = %d, z = %d\n", x, y, z);

    /*Call foo() appropriately, passing x,y,z as parameters*/
		f = foo (&x, &y, z);
    
    /*Print the value returned by foo*/
		printf ("foo() return value was %d\n", f);
    
    /*Print the values of x, y and z again*/
		printf ("x = %d, y = %d, z = %d\n", x, y, z);
 
    return 0;
}
    
    
/*Is the return value different than the value of z?  Why?*/
		/*
		 *  When z is passed to foo(), a local copy is made in "c".
		 *  The value of c  can change inside foo(), but the value of z
		 *  outside foo() is not affected.  This is referred to in the 
		 *  video lecture as "pass by value"
		 *
		 *  The scope of "int c" is limited to foo()
		 */
