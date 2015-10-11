/* CS261- Assignment 1 - Q.5*/
/* Name: Shoshana Abrass, abrasss@oregonstate.edu
 * Date: 2015-10-07
 */
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
  return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
  return ch-'A'+'a';
}

void sticky(char* word){
	/* Convert to sticky caps alternately */
	/* Ignore punctuation and other non-letters */
	int l=0;

	while (word[l] != '\0')
	{
		if ( l%2 == 0 )
		{
			/* Uppercase the letter if it's a lowercase letter */
			if (word[l] < 'z' && word[l] > 'a')
				word[l] = toUpperCase(word[l]);
		}
		else
		{
			/* Lowercase the letter if t's an uppercase letter */
			if (word[l] < 'Z' && word[l] > 'A')
				word[l] = toLowerCase(word[l]);
		}

		l++;
	}
}

/* I wrote this before I understood that stickcaps was supposed to
 * alternate lower and uppercase */
void stickyRand(char* word){
	/*Convert to sticky caps randomly */
	int l=0;

	while (word[l] != '\0')
	{
		if ( (rand() % 2) == 0 )  /* 50% chance of capitals */
		{
			/* Uppercase the letter if it's a lowercase letter */
			if (word[l] < 'z' && word[l] > 'a')
				word[l] = toUpperCase(word[l]);
		}
		else
		{
			/* Lowercase the letter if t's an uppercase letter */
			if (word[l] < 'Z' && word[l] > 'A')
				word[l] = toLowerCase(word[l]);
		}

		l++;
	}
}

int main(){

	char myString[2048];  // seems legit

  /*Read word from the keyboard using scanf*/
	printf ("Type a single word: ");
	scanf ( "%s", myString);

	printf ("You entered the word:  \"%s\"\n", myString);

  /*Call sticky*/
	sticky(myString);
    
  /*Print the new word*/
	printf ("STicKy CaPS your word: \"%s\"\n", myString);
    
    return 0;
}
