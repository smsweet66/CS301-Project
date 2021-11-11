#include "database.h"

int main()
{
	database db = readDocuments();  //creates the database from the input file

	char buf[20];   //buffer to store user input
	while(strcmp(fgets(buf, 20, stdin), "quit\n") != 0)   //user quits
	{
		matches match = {NULL, 0};    //array for storing the indexes that match the request
		if(strstr(buf, "FIND") != NULL) //find operation
		{
			int securityLevel = 0;
			for(unsigned int i=5; buf[i] >= '0' && buf[i] <= '9'; i++)
			{
				securityLevel *= 10;
				securityLevel += buf[i] - '0';
				i++;
			}

			if(securityLevel != 0)
				match = security(db, securityLevel);

			while(1)
			{
				fgets(buf, 20, stdin);
				if(strchr(buf, 'Z') != NULL)
				{
					if(match.matchingIndexes == NULL)
					{
						match.matchingIndexes = malloc(sizeof(int)*db.size);
						match.size = db.size;
						for(int i = 0; i < db.size; i++)
							match.matchingIndexes[i] = i;
					}
				}
				else if(strchr(buf, '<') != NULL || strchr(buf, '=') != NULL || strchr(buf, '>') != NULL)
				{
					char name = buf[0];
					char op = buf[2];
					int value = 0;
					if(buf[4] == '-')
					{
						for(unsigned int i=5; buf[i] >= '0' && buf[i] <= '9'; i++)
						{
							value *= 10;
							value = value - buf[i] - '0';
						}
					}
					else
					{
						for(unsigned int i = 4; buf[i] >= '0' && buf[i] <= '9'; i++)
						{
							value *= 10;
							value += buf[i] - '0';
						}
					}

					match = getMatches(db, name, op, value, match);
				}
				else
					break;
			}

			int projectSize = (strlen(buf) - 2)/2;
			char project[projectSize];
			for(int i=0; i<strlen(buf) - 2; i += 2)
				project[i/2] = buf[i];

			if(project[0] == 'X')
			{
				for(int i=0; i<match.size; i++)
				{
					for(int j=0; j<24; j++)
					{
						char fieldName = db.documents[match.matchingIndexes[i]].fieldNames[j];
						int fieldVal = db.documents[match.matchingIndexes[i]].fieldValues[j];
						if(fieldName != 0)
							printf("%c: %d ", fieldName, fieldVal);
					}

					printf("\n");
				}
			}
		}

		if(match.matchingIndexes != NULL)
			free(match.matchingIndexes);
	}

	free(db.documents);

	return 0;
}