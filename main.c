#include "database.h"
#include "sort.h"

int main()
{
	database db = readDocuments();  //creates the database from the input file

	char buf[20];   //buffer to store user input
	while(strcmp(fgets(buf, 20, stdin), "quit\n") != 0)   //user quits
	{
		matches match = {NULL, 0};    //array for storing the indexes that match the request
		char* token = strtok(buf, " \n");
		if(strcmp(token, "FIND") == 0) //find operation
		{
			token = strtok(NULL, " \n");
			if(token != NULL)
			{
				int securityLevel = atoi(token);

				match = security(db, securityLevel);
			}

			while(1)
			{
				fgets(buf, 20, stdin);
				if(strchr(buf, ';') != NULL)
					break;
				else if(strchr(buf, 'Z') != NULL)
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
					char name = strtok(buf, " \n")[0];
					char op = strtok(NULL, " \n")[0];
					token = strtok(NULL, " \n");
					int value = atoi(token);
					match = getMatches(db, name, op, value, match);
				}
			}

			vector projection = {malloc(sizeof(char)), 0, 1};
			push(&projection, strtok(buf, " \n")[0]);
			while((token = strtok(NULL, " \n"))[0] != ';')
				push(&projection, token[0]);

			if(projection.arr[0] == 'X')
			{
				for(int i=0; i<match.size; i++)
					printDocument(&db.documents[match.matchingIndexes[i]], NULL);
			}
			else
			{
				for(int i=0; i<match.size; i++)
					printDocument(&db.documents[match.matchingIndexes[i]], &projection);
			}

			free(projection.arr);
		}
		else if(strstr(token, "SORT") != NULL)
		{
			token = strtok(NULL, " \n");
			if(token != NULL)
				match = security(db, atoi(token));

			if(match.size != 0)
			{
				fgets(buf, 20, stdin);
				token = strtok(buf, " \n");
				match = getMatches(db, token[0], 0, 0, match);
			}
		}

		if(match.matchingIndexes != NULL)
			free(match.matchingIndexes);

		match.matchingIndexes = NULL;
	}

	for(int i=0; i<db.size; i++)
		free(db.documents[i].docOrder.arr);

	free(db.documents);

	return 0;
}