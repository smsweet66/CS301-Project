#include "sort.h"

#pragma once

/**
 * Merges the two sections of the array together in sorted order
 */
void merge(int *array, int high, int low, int compare(int a, int b))
{
	int arrayBLength = (high - low + 1);
	int arrayB[arrayBLength];
	int bMiddle = (arrayBLength + 1)/2;
	for(int i = 0; i < arrayBLength; i++)
		arrayB[i] = array[i + low];

	int lIterator = 0;
	int rIterator = bMiddle;
	int arrayIter = low;

	while(lIterator < bMiddle && rIterator < arrayBLength)
	{
		/*
		 * If the number on the left is less than on the right,
		 * it places the left index into the array
		 */
		if(lIterator < bMiddle && compare(arrayB[lIterator], arrayB[rIterator]))
		{
			array[arrayIter] = arrayB[lIterator];
			arrayIter++;
			lIterator++;
		}

		/*
		 * If the number on the right is less than on the left,
		 * it places the right index into the array
		 */
		if(rIterator < arrayBLength && compare(arrayB[rIterator], arrayB[lIterator]))
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
		else if(lIterator < bMiddle && rIterator == arrayBLength)
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
void split(int* arr, int high, int low, int compare(int a, int b))
{
	if(low<high)
	{
		int middle = (high+low)/2;
		split(arr, middle, low, compare);
		split (arr, high, middle + 1, compare);
		merge(arr, high, low, compare);
	}
}

void sort(int* arr, int size, int compare(int a, int b))
{ split(arr, size-1, 0, compare); }