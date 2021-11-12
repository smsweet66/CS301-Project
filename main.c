#include "database.h"
#include "linkedList.h"

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
			int securityLevel = 0;
			token = strtok(NULL, " \n");
			if(token != NULL)
			{
				for(unsigned int i = 0; token[i] >= '0' && token[i] <= '9'; i++)
				{
					securityLevel *= 10;
					securityLevel += token[i] - '0';
					i++;
				}

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
					int value = 0;
					if(token[0] == '-')
					{
						for(unsigned int i=1; token[i] >= '0' && token[i] <= '9'; i++)
						{
							value *= 10;
							value = value - token[i] - '0';
						}
					}
					else
					{
						for(unsigned int i = 0; token[i] >= '0' && token[i] <= '9'; i++)
						{
							value *= 10;
							value += token[i] - '0';
						}
					}

					match = getMatches(db, name, op, value, match);
				}
			}

			node* projection = malloc(sizeof(node));
			projection->val = strtok(buf, " \n")[0];
			projection->next = NULL;
			for(node* iter = projection; (token = strtok(NULL, " \n"))[0] != ';'; iter = iter->next)
				createNode(iter, token[0]);

			if(projection->val == 'X')
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
			else
			{
				for(int i=0; i<match.size; i++)
				{
					int hasProjection = 0;
					for(node *iter = projection; iter != NULL; iter = iter->next)
					{
						if(iter->val == 'Y')
							iter->val--;

						char fieldName = db.documents[match.matchingIndexes[i]].fieldNames[iter->val - 'A'];
						int fieldVal = db.documents[match.matchingIndexes[i]].fieldValues[iter->val - 'A'];
						if(fieldName != 0)
						{
							printf("%c: %d ", fieldName, fieldVal);
							hasProjection++;
						}
					}

					if(hasProjection > 0)
						printf("\n");
				}
			}

			deleteList(projection);
		}
		else if(strstr(buf, "SORT") != NULL)
		{

		}

		if(match.matchingIndexes != NULL)
			free(match.matchingIndexes);
	}

	free(db.documents);

	return 0;
}