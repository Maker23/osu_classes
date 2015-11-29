#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"

#define DEBUG 0


/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashLink ** hm, int tableSize)
{  
	int i;
	struct hashLink *nextLink;
	struct hashLink *tmpLink;

	for (i=0; i< tableSize; i++)
	{
		nextLink = hm[i];
		while (nextLink != NULL)
		{
			tmpLink = nextLink;
			nextLink = nextLink->next;
			free (tmpLink->key);
			free (tmpLink);
		}
	}
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht->table, ht->tableSize);
	/* free the hashMap struct */
	free(ht);
}

/* 
Resizes the hash table to be the size newTableSize 
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
	int i;
	int oldTableSize = ht->tableSize;
	struct hashLink ** oldTable;

	struct hashLink *nextLink;

	oldTable = ht->table;
	_initMap(ht, newTableSize);

	if (DEBUG) printf ("DEBUG: _setTableSize to %d\n", newTableSize);
	for (i=0; i< oldTableSize; i++)
	{
		nextLink = oldTable[i];

		while (nextLink != NULL) 
		{
			insertMap (ht, nextLink->key, nextLink->value);
			nextLink = nextLink->next;
		}
	}

	//_freeMap(oldTable, oldTableSize);

}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".
 
 ************************************************************************
 cs261  GRADER: PLEASE READ
 Although this comment states that memory for the old value should be freed, 
 this function doesn't require it -- in fact it would be a bug, because 
 hashLink->value is not a pointer.

 https://piazza.com/class/ien5yaacd923b3?cid=421
 ************************************************************************

 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.
 
 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  

	int idx;
	struct hashLink *newLink;
	struct hashLink *nextLink;
	
	// Hash the key to get the index
	if (DEBUG) printf ("DEBUG: insertMap getting hash for %s\n", k);
	if ( HASHING_FUNCTION == 1 )
		idx = abs(stringHash1(k)) % ht->tableSize;
	else
		idx = abs(stringHash2(k)) % ht->tableSize;
	
	if (DEBUG) printf ("DEBUG: insertMap hash is %d ---- \n", idx);
	nextLink = ht->table[idx];
	// Traverse the linked list to see if the key exists, and update the value
	while (nextLink != NULL)
	{
		if ( (strcmp(k, nextLink->key) ) == 0 )
		{
			nextLink->value = v;
			return;
		}
		nextLink = nextLink->next;
	}
	if (DEBUG) printf ("DEBUG: tableLoad is %f\n", tableLoad(ht));
	if (tableLoad(ht) > LOAD_FACTOR_THRESHOLD)
	{
		_setTableSize(ht, capacity(ht) * 2 ); // double the number of buckets
	}

	// Create a new Link with the Key/Value
	newLink = malloc (sizeof (struct hashLink));
	newLink->key = malloc ((strlen(k)+1) * sizeof (char));
	assert ((newLink != NULL) && (newLink->key != NULL));

	strncpy(newLink->key, k, strlen(k));
	newLink->key[strlen(k)] = '\0';
	newLink->value = v;
	newLink->next = ht->table[idx];
	ht->table[idx] = newLink;
	ht->count++;
}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.
 
 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.
 
 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{ 
	int idx;
	struct hashLink * nextLink;

	if ( HASHING_FUNCTION == 1 )
		idx = abs(stringHash1(k)) % ht->tableSize;
	else
		idx = abs(stringHash2(k)) % ht->tableSize;

	nextLink = ht->table[idx];
	while (nextLink != NULL)
	{
		if ( (strcmp(k, nextLink->key) ) == 0 )
		{
			return ( &(nextLink->value));
		}
		nextLink = nextLink->next;
	}
	return NULL;
}

/*
 a simple yes/no if the key is in the hashtable. 
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{  
	int idx;
	struct hashLink * nextLink;

	if ( HASHING_FUNCTION == 1 )
		idx = abs(stringHash1(k)) % ht->tableSize;
	else
		idx = abs(stringHash2(k)) % ht->tableSize;

	nextLink = ht->table[idx];
	while (nextLink != NULL)
	{
		if ( (strcmp(k, nextLink->key) ) == 0 )
		{
			return 1;
		}
		nextLink = nextLink->next;
	}
	return 0;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{  
	int idx;
	struct hashLink * nextLink;
	struct hashLink * prevLink = NULL;

	if ( HASHING_FUNCTION == 1 )
		idx = abs(stringHash1(k)) % ht->tableSize;
	else
		idx = abs(stringHash2(k)) % ht->tableSize;

	nextLink = ht->table[idx];
	while (nextLink != NULL)
	{
		if ( (strcmp(k, nextLink->key) ) == 0 )
		{
			// Found it, remove it
			if (prevLink == NULL)
				ht->table[idx] = nextLink->next;
			else
				prevLink->next = nextLink->next;
			free (nextLink->key);
			free (nextLink);
			return;
		}
		prevLink = nextLink;
		nextLink = nextLink->next;
	}
	// key not found
}

/*
 returns the number of hashLinks in the table
 */
int size(struct hashMap *ht)
{  
	return ht->count;
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{  
	return ht->tableSize;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{  
	int i;
	int emptyBuckets=0;
	int totalBuckets = capacity(ht);

	for (i = 0; i < totalBuckets; i++)
	{
		if (ht->table[i] == NULL)
			emptyBuckets ++;
	}
	return emptyBuckets;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)
 
 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{  
	int numLinks = size(ht);
	int numBuckets = capacity(ht);

	if (numBuckets == 0) // don't divide by zero...
		return 0; 
	return ((float)numLinks / (float)numBuckets);
}
void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;	

	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {		
			printf("\nBucket Index %d -> ", i);		
		}
		while(temp != 0){			
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;			
		}		
	}
}


/*  Written questions

1. Give an example of two words that would hash to the same value using
	 stringHash1() but would not using stringHash2().  

	 A: With stringHash1,  "ate", "eat", and "tea" would hash to the
	 same value, but would not with stringHash2.

2. Why does the above make stringHash2() superior to stringHash1()?
   
	 A: There will be fewer collisions since different words are more
	 likely to produce a different hash.

3. When you run your program on the same input file but one run using
   stringHash1() and on the other run using stringHash2(). Is it possible
   for your size() function to return different values?  

	 A: The size() will be the same, since this is equal to the number
	 of unique keys in the input data.

4. When you run your program on the same input file using stringHash1
   () on one run and using stringHash2() on another, is it possible for
   your tableLoad() function to return different values?

	 A: tableLoad() will be the same, since it doesn't take into account
	 how many collisions have occurred - only the ratio of keys to buckets.

5. When you run your program on the same input file with one run using
   stringHash1() and the other run using stringHash2(), is it possible
   for your emptyBuckets() function to return different values?

	 A: emptyBuckets() can be different, since the strings will be
	 spread differently across the buckets with a different hash function.

6. Is there any difference in the number of 'empty buckets' when you
   change the table size from an even number, like 1000 to a prime 
	 like 997 ?

	 A: There should be fewer empty buckets. Using a prime table size 
	 should cause the hashed values to distribute more evenly across
	 all the buckets.
	 http://stackoverflow.com/questions/1145217/why-should-hash-functions-use-a-prime-number-modulus

7. Using the timing code provided to you. Run you code on different
   size hash tables. How does affecting the hash table size change your
   performance?  

	 A: for this question I ran the program on my local computer
	 and added timing to the "delete keys" section of main(), since
	 delete has to search the data before it can remove the key.
	 The search+delete ran in constant time for all sizes of table.
	 That is pretty cool!

	 	                                     concordance      delete
                     size:     capacity:     ran in:      ran in:
	 dictionary.txt:   109,582     163,840     .285918      .000005
   whatis:             4,630      10,240     .023029      .000005
	 input2.txt:           908       1,280     .003064	    .000004
	 input1.txt:            68         160     .000431	    .000003
    


*/
