/* CS261- Assignment 1 - Q.0  */
/* Name: Shoshana Abrass, abrasss@oregonstate.edu
 * Date: 2015-10-07
 */
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
	/*Print the value pointed to by iptr*/
	printf("The value pointed to by iptr is %i\n", *iptr);
     
	/*Print the address pointed to by iptr*/
	printf("The address pointed to by iptr is  %p\n", iptr);
     
	/*Print the address of iptr itself*/
	printf("The address of iptr itself is  %p\n", &iptr);
}

int main(int argc, char **argv){
    
	/*declare an integer x*/

	int x = 20;
    
	/*print the address of x*/
	printf("The address of x is  %p\n", (int *) &x);
    
	/*Call fooA() with the address of x*/

	fooA (&x);
    
	/*print the value of x*/
	printf("The value of x is %i\n", x);
    
	return 0;
}
