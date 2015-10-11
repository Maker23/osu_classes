/* CS261- Assignment 1 - Q.1  */
/* Name: Shoshana Abrass, abrasss@oregonstate.edu
 * Date: 2015-10-07
 */
 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define DEBUG 0

#define NUMSTUDENTS 10

struct student{
	int id;
	int score;
};

struct student* allocate(){

  /*Allocate memory for ten students*/
	struct student* studentArray = malloc(NUMSTUDENTS * sizeof(struct student));

  /*return the pointer*/
  return studentArray;
}

void printStudent (struct student* student){
	printf(" %d\t%d\n", student->id, student->score);
}

void generate(struct student* students){
     /*Generate random ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/

   int i;
	 int IDs[10] = {0};
	 int tmpID = 0;
	 int tmpScore;

	 for (i=0; i<NUMSTUDENTS; i++)
	 {
		 do
		 {
	 	  	tmpID = rand() % NUMSTUDENTS + 1; 
		 }
	 	 while (IDs[tmpID] == 1 ) ;

		 IDs[tmpID] = 1; // This ID is being used;

	 	 tmpScore = rand() % 101;

		 students[i].id = tmpID;
		 students[i].score = tmpScore;

		 if (DEBUG) printStudent(&(students[i]));
	 }

}

void output(struct student* students){
	 int i;

	 printf("\n ID\tScore\n");
	 for (i=0; i<NUMSTUDENTS; i++)
	 {
		 printStudent(&(students[i]));
	 }
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
	 int i;
   int minScore = 101;
	 int maxScore = -1;

	 float sumScore = 0.0;
     
	 for (i=0; i<NUMSTUDENTS; i++) {
	   if ( students[i].score < minScore )  minScore = students[i].score;
		 if ( students[i].score > maxScore )  maxScore = students[i].score;

		 sumScore += students[i].score;
	 }

	 printf ("\nmin: %d\tmax: %d\tavg: %3.1f\n",
	 	minScore,
		maxScore,
		sumScore/(float)NUMSTUDENTS);
}

void deallocate(struct student* stud){
  /*Deallocate memory from stud*/
  if (stud != 0 ) free (stud);
}

int main(){
  struct student* stud = NULL;
    
  /*call allocate*/
	stud = allocate();

  /*call generate*/
  generate(stud);

  /*call output*/
	output(stud);
    
  /*call summary*/
	summary(stud);
    
  /*call deallocate*/
	deallocate (stud);

  return 0;
}
