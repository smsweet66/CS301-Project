#include <stdio.h>
#include <string.h>
#include <malloc.h>

#pragma once

typedef struct document
{
	char fieldNames[24];
	int fieldValues[24];
} document;

typedef struct database
{
	document* documents;
	unsigned int size;
} database;

database readDocuments()
{
	FILE *input = fopen("data.txt", "r");
	char buf[200];
	int numLines = 0;
	while(fgets(buf, 200, input) != NULL)
	{
		if(strcmp(buf, "\n") == 0)
			break;

		numLines++;
	}

	fclose(input);
	input = fopen("data.txt", "r");
	database db = {malloc(sizeof(document)*numLines), numLines};
	for(int i=0; i<numLines; i++)
		for(int j=1; j<24; j++)
			db.documents[i].fieldNames[j] = 0;

	for(int i=0; i<numLines; i++)
	{
		fgets(buf, 200, input);
		db.documents[i].fieldNames[0] = 'A';
		db.documents[i].fieldValues[0] = i;

		for(int j=0; buf[j] != 0 && j < 200; j++)
		{
			unsigned char index;
			if(buf[j] == ':')
			{
				index = buf[j-1];
				if(index == 'Y')
					index = index - 1 - 'A';
				else
					index -= 'A';

				db.documents[i].fieldNames[index] = buf[j-1];
				j += 2;
				int fieldVal = 0;
				if(buf[j] == '-')
				{
					while(buf[j] >= '0' && buf[j] <= '9')
					{
						fieldVal *= 10;
						fieldVal -= buf[j] - '0';
						j++;
					}
				}
				else
				{
					while(buf[j] >= '0' && buf[j] <= '9')
					{
						fieldVal *= 10;
						fieldVal += buf[j] - '0';
						j++;
					}
				}

				db.documents[i].fieldValues[index] = fieldVal;
			}
		}
	}

	fclose(input);
	return db;
}

typedef struct matches
{
	int* matchingIndexes;
	unsigned int size;
} matches;

matches security(database db, int securityLevel)
{
	int initMatches[db.size];
	for(int i=0; i< db.size; i++)
		initMatches[i] = i;

	unsigned int numMatches = db.size;
	for(int i=0; i<db.size; i++)
	{
		if(db.documents[i].fieldValues[23] > securityLevel)
		{
			initMatches[i] = -1;
			numMatches--;
		}
	}

	matches match = {malloc(sizeof(int)*numMatches), numMatches};
	int matchesIter = 0;
	for(int i=0; i<db.size; i++)
	{
		if(initMatches[i] != -1)
		{
			match.matchingIndexes[matchesIter] = initMatches[i];
			matchesIter++;
		}
	}

	return match;
}

int compare(int a, char op, int b)
{
	switch(op)
	{
	case '<':
		return a < b;

	case '=':
		return a == b;

	case '>':
		return a > b;

	default:
		return 0;
	}
}

matches getMatches(database db, char fieldName, char op, int value, matches currentMatches)
{
	if(currentMatches.matchingIndexes == NULL)
	{
		currentMatches.matchingIndexes = malloc(sizeof(int)*db.size);
		currentMatches.size = db.size;
		for(int i=0; i<db.size; i++)
			currentMatches.matchingIndexes[i] = i;
	}

	unsigned int totalMatches = currentMatches.size;
	for(int i=0; i<currentMatches.size; i++)
	{
		if(db.documents[currentMatches.matchingIndexes[i]].fieldNames[fieldName - 'A'] == 0
		|| !compare(db.documents[currentMatches.matchingIndexes[i]].fieldValues[fieldName - 'A'], op, value))
		{
			currentMatches.matchingIndexes[i] = -1;
			totalMatches--;
		}
	}

	matches newMatches = {malloc(sizeof(int)*totalMatches), totalMatches};
	unsigned int newMatchesIter = 0;
	for(unsigned int i=0; i<currentMatches.size && newMatchesIter < newMatches.size; i++)
	{
		if(currentMatches.matchingIndexes[i] != -1)
		{
			newMatches.matchingIndexes[newMatchesIter] = currentMatches.matchingIndexes[i];
			newMatchesIter++;
		}
	}

	free(currentMatches.matchingIndexes);
	return newMatches;
}