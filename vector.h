#pragma once

typedef struct vector
{
	char* arr;
	int size;
	int capacity;
}vector;

int push(vector* v, int val)
{
	if(v->size == v->capacity)
	{
		v->capacity *= 2;
		char* newArr = malloc(sizeof(char)*v->capacity);
		for(int i=0; i<v->size; i++)
			newArr[i] = v->arr[i];

		free(v->arr);
		v->arr = newArr;
	}

	v->arr[v->size] = val;
	v->size++;
}

int contains(vector* v, char val)
{
	for(int i=0; i<v->size; i++)
		if(v->arr[i] == val)
			return 1;

	return 0;
}