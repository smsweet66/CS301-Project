#include "sort.h"

/**
 * Merges the two sections of the array together in sorted order
 */
static void merge(int *array, unsigned int high, unsigned int low, int compare(int a, int b, int direction), int direction, database* db, char val)
{
	unsigned int arrayBLength = (high - low + 1);
	int arrayB[arrayBLength];
	unsigned int bMiddle = (arrayBLength + 1)/2;
	for(int i = 0; i < arrayBLength; i++)
		arrayB[i] = array[i + low];

	unsigned int lIterator = 0;
	unsigned int rIterator = bMiddle;
	unsigned int arrayIter = low;

	while(lIterator < bMiddle && rIterator < arrayBLength)
	{
		/*
		 * If the number on the left is less than on the right,
		 * it places the left index into the array
		 */
		if(lIterator < bMiddle &&
		compare(db->documents[arrayB[lIterator]].fieldValues[val], db->documents[arrayB[rIterator]].fieldValues[val], direction))
		{
			array[arrayIter] = arrayB[lIterator];
			arrayIter++;
			lIterator++;
		}

		/*
		 * If the number on the right is less than on the left,
		 * it places the right index into the array
		 */
		if(rIterator < arrayBLength &&
		compare(db->documents[arrayB[rIterator]].fieldValues[val], db->documents[arrayB[lIterator]].fieldValues[val], direction))
		{
			array[arrayIter] = arrayB[rIterator];
			arrayIter++;
			rIterator++;
		}

		/*
		 * If the whole left side has been placed, it then places
		 * the right side into the array.
		 */
		if(lIterator == bMiddle && rIterator < arrayBLength)
		{
			while(rIterator < arrayBLength)
			{
				array[arrayIter] = arrayB[rIterator];
				arrayIter++;
				rIterator++;
			}
		}

		/*
		 * If the whole right side has been placed, it then places
		 * the left side into the array.
		 */
		if(lIterator < bMiddle && rIterator == arrayBLength)
		{
			while(lIterator < bMiddle)
			{
				array[arrayIter] = arrayB[lIterator];
				arrayIter++;
				lIterator++;
			}
		}
	}
}

/**
 * sorts the values of an array of any type
 * @param arr the array to be sorted
 * @param high the highest index
 * @param low the first index of the section to be sorted
 * @param compare a function used to compare values
 */
static void split(int* arr, unsigned int high, unsigned int low, int compare(int a, int b, int direction), int direction, database* db, char val)
{
	if(low<high)
	{
		unsigned int middle = (high+low)/2;
		split(arr, middle, low, compare, direction, db, val);
		split (arr, high, middle + 1, compare, direction, db, val);
		merge(arr, high, low, compare, direction, db, val);
	}
}

void sort(int* arr, unsigned int size, int compare(int a, int b, int direction), int direction, database* db, char val)
{ split(arr, size-1, 0, compare, direction, db, val); }