#include <stdio.h>
#include <string.h>
#include <malloc.h>

#pragma once

typedef struct field
{
	char fieldName;
	int fieldValue;
} field;

typedef struct document
{
	field fields[24];
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
			db.documents[i].fields[j].fieldName = 0;

	for(int i=0; i<numLines; i++)
	{
		fgets(buf, 200, input);
		db.documents[i].fields[0].fieldName = 'A';
		db.documents[i].fields[0].fieldValue = i;

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

				db.documents[i].fields[index].fieldName = buf[j-1];
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

				db.documents[i].fields[index].fieldValue = fieldVal;
			}
		}
	}

	fclose(input);
	return db;
}