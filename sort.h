#pragma once

#include "database.h"

void sort(int* arr, unsigned int size, int compare(int a, int b, int direction), int direction, database* db, char val);