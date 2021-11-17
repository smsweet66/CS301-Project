#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "vector.h"

typedef struct document
{
	char fieldNames[24];
	int fieldValues[24];
	vector docOrder;
} document;

typedef struct database
{
	document* documents;
	unsigned int size;
} database;

typedef struct matches
{
	int* matchingIndexes;
	unsigned int size;
} matches;

database readDocuments();

matches security(database db, int securityLevel);

matches getMatches(database db, char fieldName, char op, int value, matches currentMatches);

void printDocument(document* d, vector* projection);