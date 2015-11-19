#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"

#define FILENAME "todo.txt"


int main (int argc, const char * argv[])
{
  char cmd = ' ';
	char gbg;
	char tmpDesc[TASK_DESC_SIZE];
	char tmpPrioStr[32];
	int tmpPrio;
	FILE *fp;
  DynArr* mainList = createDynArr(10);
	TYPE tmpTask;

 
  /* ***************************************************** 
	 *
	 * The UI is better if the program automatically reads and
	 * prints the file.  Commented out for the assignment.
	 */
  /*
  fp=fopen(FILENAME, "r");
	loadList(mainList, fp);
	fclose(fp);
	printDynArr(mainList, print_type);
	printList(mainList);
	*/
  /* ***************************************************** */
  printf("\n\n** TO-DO LIST APPLICATION **\n\n");

  do
    {
      printf("\nPress:\n"
             "'l' to load to-do list from a file\n"
             "'s' to save to-do list to a file\n"
             "'a' to add a new task\n"
             "'g' to get the first task\n"
             "'r' to remove the first task\n"
             "'p' to print the list\n"
             "'e' to exit the program\n\n"
						 ">> "
             );
      /* get input command (from the keyboard) */
      cmd = getchar();
      /* clear the trailing newline character */
      while (getchar() != '\n');

			switch (cmd)
			{
				case 'l':
					fp = fopen(FILENAME, "r");
					if (fp == NULL )
						printf ("couldn't open file %s for read\n", FILENAME);
					else
						loadList(mainList, fp);
					fclose(fp);
					break;
				case 's':
					fp = fopen(FILENAME, "w");
					if (fp == NULL )
						printf ("couldn't open file %s for overwrite\n", FILENAME);
					else
						saveList(mainList, fp);
					fclose(fp);
					break;
				case 'a':
					printf ("Description of the task: ");
					scanf("%127[^\n]s", tmpDesc);
					gbg = getchar();
					printf ("Priority for the task: ");
					scanf("%32[^\n]s", tmpPrioStr);
					gbg = getchar();
					tmpPrio = atoi(tmpPrioStr); // Har.. no way to check atoi return vals
					tmpTask = createTask (tmpPrio, tmpDesc);
					addHeap(mainList, tmpTask, compare);
					break;
				case 'g':
					if (sizeDynArr(mainList) > 0 )
					{
						print_type(getMinHeap(mainList));
					}
					else
						printf ("Your to-do list is empty.\n");
					break;
				case 'r':
					if (sizeDynArr(mainList) > 0 )
					{
						printf ("Removing the top priority item from the list\n");
						removeMinHeap(mainList, compare);
					}
					else
						printf ("Your to-do list is empty.\n");
					break;
				case 'p':
					if (sizeDynArr(mainList) > 0 )
					{
						printList(mainList);
					}
					else
						printf("Your to-do list is empty.\n");
					break;
				case 'e':
				case 'q':
					/* Just fall through */
					break;
				default:
					printf ("Unrecognized command \"%c\"\n", cmd);
					break;
			}

    }
  while(cmd != 'e' && cmd != 'q');
  /* delete the list */
  deleteDynArr(mainList);

  return 0;
}
