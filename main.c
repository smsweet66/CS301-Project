#include "database.h"

int main()
{
	database db = readDocuments();

	for(int i=0; i<db.size; i++)
	{
		for(int j=0; j<24; j++)
			if(db.documents[i].fieldNames[j] != 0)
				printf("%c: %d ", db.documents[i].fieldNames[j], db.documents[i].fieldValues[j]);

		printf("\n");
	}

	free(db.documents);

	return 0;
}
