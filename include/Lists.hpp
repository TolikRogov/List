#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "Lists_errors.hpp"

typedef int Pointers_t;
typedef int Data_t;
typedef int Indexes_t;

struct List {
	Pointers_t head;
	Pointers_t tail;

	size_t capacity;
	size_t size;
	Data_t* data;

	Indexes_t* next;
	Indexes_t* prev;
};

const size_t DEFAULT_DATA_CAPACITY = 20;

const size_t LIST_TRASH = 0xDED104;

ListStatusCode ListCtor(List* list);
ListStatusCode ListDtor(List* list);
