#include <stdio.h>
#include <string.h>

typedef struct field
{
	char fieldName;
	int fieldValue;
} field;

typedef struct document
{
	field fields[24];
} document;

int main()
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
	document documents[numLines];
	for(int i=0; i<numLines; i++)
		for(int j=1; j<24; j++)
			documents[i].fields[j].fieldName = 0;

	for(int i=0; i<numLines; i++)
	{
		fgets(buf, 200, input);
		documents[i].fields[0].fieldName = 'A';
		documents[i].fields[0].fieldValue = i;

		//do some stuff with splitting the string to get the document information;
	}

	return 0;
}
