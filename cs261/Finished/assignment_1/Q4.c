/* CS261- Assignment 1 - Q.4*/
/* Name: Shoshana Abrass, abrasss@oregonstate.edu
 * Date: 2015-10-07
 */
 
#include <stdio.h>
#include <stdlib.h>

struct student{
	int id;
	int score;
};

void sort(struct student* Students, int n){
	/*Sort the n students based on their score*/     

	int i = 0;
	int anySwaps;
	struct student tmpStudent;

	do {
		anySwaps = 0;

		for (i=0; i <n-1; i++)
		{
			if (Students[i].score > Students[i+1].score)
			{
				tmpStudent.id = Students[i].id;
				tmpStudent.score = Students[i].score;

				Students[i].id = Students[i+1].id;
				Students[i].score = Students[i+1].score;

				Students[i+1].id = tmpStudent.id;
				Students[i+1].score = tmpStudent.score;

				anySwaps = 1;
			}
		}
	}
	while (anySwaps == 1);
}

int main(){

		int n = 10; /*Declare an integer n and assign it a value.*/
		int i, tmpID;
    
    /*Allocate memory for n students using malloc.*/
		struct student* Students = (struct student *) malloc (n * sizeof (struct student));

		int * IDs = (int *) malloc ( (n * (size_t) sizeof (int) +1));
		for (i=0; i <= n; i++)
		{
			IDs[i] = 0;
		}
    
    /*Generate random IDs and scores for the n students, using rand().*/
		for (i=0; i< n; i++)
		{
			do
			{
				tmpID = rand() % n + 1; 
			}
			while (IDs[tmpID] == 1 ) ;
			IDs[tmpID] = 1; // This ID is being used

			Students[i].id     = tmpID;
			Students[i].score  = rand() % 101; // Scores from 0 to 100
		}
    
    /*Print the contents of the array of n students.*/
		printf("\nUnsorted:\n");
		for (i=0; i< n; i++)
		{
		  printf("Student ID:  %2d\t Score:%3d\n",	Students[i].id, Students[i].score);
		}

    /*Pass this array along with n to the sort() function*/
		sort(Students, n);
    
    /*Print the contents of the array of n students.*/
		printf("\nSorted:\n");
		for (i=0; i< n; i++)
		{
		  printf("Student ID:  %2d\t Score:%3d\n",	Students[i].id, Students[i].score);
		}

		free(Students);
		free(IDs);
    
    return 0;
}
