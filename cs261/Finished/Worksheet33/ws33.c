#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dynArray.h"
/* *******
typedef struct DynArr DynArr;

void initDynArr(DynArr *v, int capacity);	
DynArr *newDynArr(int cap);

void freeDynArr(DynArr *v);
void deleteDynArr(DynArr *v);

int sizeDynArr(DynArr *v);

void addDynArr(DynArr *v, TYPE val);
TYPE getDynArr(DynArr *v, int pos);
void putDynArr(DynArr *v, int pos, TYPE val);
void swapDynArr(DynArr *v, int i, int  j);
void removeAtDynArr(DynArr *v, int idx);

*/

void fillTestData(struct DynArr * myArr);


int main()
{
	TYPE val;
	struct DynArr *heap;
	heap = newDynArr(24);

	fillTestData(heap);

	printDynArr(heap);

	buildHeap (heap);

	_adjustHeap(heap,sizeDynArr(heap)-1,0);
	printDynArr(heap);


  while (sizeDynArr(heap) > 0){
		val = HeapGetFirst (heap);
		printf ("======= removing least value %d =======\n", val); 
		HeapRemoveFirst (heap);
	}

	return 0;
}


void HeapRemoveFirst(struct DynArr *heap) {

	int last = sizeDynArr(heap)-1;
	/* make sure we have at least one element */
	//assert (last != 0); // really?? TODO
	if ( last > 0 )
	{
		/* Copy the last element to the first position */ 
		putDynArr(heap, 0, getDynArr(heap, last));
		/* Remove last element.*/ 
		removeAtDynArr(heap, last);
		_adjustHeap(heap, last, 0);/* Rebuild heap */
	}
	else {
		removeAtDynArr(heap, last);
	}
}



//We abstract the restoring heap property into a new routine termed adjustHeap:
//AdjustHeap can easily be written as a recursive routine:
void _adjustHeap (struct DynArr * heap, int maxInd, int currInd) 
{
	int leftChildInd = 2 * currInd + 1;
	int rghtChildInd = 2 * currInd + 2;

	int _minChildInd;

	if (DEBUG) printf("_adjust heap maxInd = %d, currInd = %d\n", maxInd, currInd);
	if (rghtChildInd < maxInd) 
	{ 
		/* we have two children */
		/* get index of smallest child */
		_minChildInd = indexSmallest (heap, leftChildInd, rghtChildInd);
	
		if (DEBUG) printf ("\tComparing %d and %d; smallest is %d [index %d]\n", getDynArr(heap,leftChildInd), getDynArr(heap,rghtChildInd), getDynArr(heap,_minChildInd), _minChildInd);
		if (getDynArr(heap, currInd) > getDynArr(heap,_minChildInd))
		{
			if (DEBUG) printf ("\t\tSwapping values %d and %d [index %d / %d]\n", getDynArr(heap,currInd),getDynArr(heap,_minChildInd), currInd, _minChildInd);
			swapDynArr(heap, currInd, _minChildInd);
			_adjustHeap (heap, maxInd, _minChildInd);
		}
	}
	else if (leftChildInd < maxInd) { 
		/* we have one child */ 
		if (DEBUG) printf ("Comparing %d and %d\n", getDynArr(heap,leftChildInd), getDynArr(heap,currInd));
		if (getDynArr(heap, currInd) > getDynArr(heap,leftChildInd))
			swapDynArr(heap, currInd, leftChildInd);
			_adjustHeap (heap, maxInd, leftChildInd);
	}

	return;
	/* else no children, done */
	
/* The process follows a path in the complete tree, and hence is O
 * (log n).  Two internal routines help in the completion of both these
 * routines. The function swap , which you wrote in an earlier worksheet
 * , will exchange two dynamic array positions. The function indexSmallest
 * takes two index values, and returns the position of the smaller
 * of the two.  
 */
}

int indexSmallest (struct DynArr * v, int i, int j) 
{ 
	/* return index of smallest element */
	if (LT(getDynArr(v, i), getDynArr(v, j)))
		return i;
	return j;
}
TYPE HeapGetFirst (struct DynArr *heap) { assert(sizeDynArr(heap) > 0);
	return getDynArr(heap, 0);
}


void heapAdd (struct DynArr * heap, TYPE newValue) 
{
	addDynArr(heap, newValue);
	/* adds to end – now need to adjust position */
}
/* ****************************************************** */
void fillTestData(struct DynArr * myArr)
{
	/* one through sixteen */
	addDynArr(myArr, 14);
	addDynArr(myArr, 3);
	addDynArr(myArr, 1);
	addDynArr(myArr, 2);
	addDynArr(myArr, 15);
	addDynArr(myArr, 8);
	addDynArr(myArr, 16);
	addDynArr(myArr, 4);
	addDynArr(myArr, 6);
	addDynArr(myArr, 7);
	addDynArr(myArr, 9);
	addDynArr(myArr, 12);
	addDynArr(myArr, 5);
	addDynArr(myArr, 13);
	addDynArr(myArr, 10);
	addDynArr(myArr, 11);
}
void buildHeap (struct DynArr *heap) {
	if (DEBUG) printf("+++++++++ Building Heap +++++++++\n");
	int max = sizeDynArr(heap); 
	int i;
	for ( i = max/2-1; i >= 0; i--)
		_adjustHeap(heap, max, i);
}
