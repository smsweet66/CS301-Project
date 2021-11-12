#pragma once

typedef struct node
{
	char val;
	struct node* next;
}node;

node* createNode(node* current, char v)
{
	current->next = malloc(sizeof(node));
	current->next->val = v;
	current->next->next = NULL;
}

void deleteList(node* head)
{
	node* iter = head->next;
	while(head != NULL)
	{
		free(head);
		head = iter;
		if(head != NULL)
			iter = head->next;
	}
}