#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dynamicArray.h"
#include "toDoList.h"



int main(int argc, const char * argv[])
{
  	TYPE task1;
	TYPE task2;
	TYPE task3;
	TYPE task4;
	TYPE task5;
	TYPE task6;
	TYPE task7;
	TYPE task8;
	TYPE task9;
	TYPE task10;

	DynArr *mainList;
	mainList = createDynArr(10);

	/* create tasks */
	task1 = createTask(9, "First");
	task2 = createTask(3, "Second");
	task3 = createTask(2, "Third");
	task4 = createTask(4, "Fourth");
	task5 = createTask(5, "Fifth");
	task6 = createTask(7, "Sixth");
	task7 = createTask(8, "Seventh");
	task8 = createTask(6, "Eighth");
	task9 = createTask(1, "Ninth");
	task10 = createTask(0, "Tenth");

	/* add tasks to the dynamic array */
	addHeap(mainList, task1, compare);
	addHeap(mainList, task2, compare);
	addHeap(mainList, task3, compare);
	addHeap(mainList, task4, compare);
	addHeap(mainList, task5, compare);
	addHeap(mainList, task6, compare);
	addHeap(mainList, task7, compare);
	addHeap(mainList, task8, compare);
	addHeap(mainList, task9, compare);
	addHeap(mainList, task10, compare);


	printf("Before Sort Called \n");
	printDynArr(mainList, print_type);

	/* sort tasks */
	sortHeap(mainList, compare);

	printf("After Sort Called \n");

	/* print sorted tasks from the dynamic array */
        printDynArr(mainList, print_type);

	return 0;
}
