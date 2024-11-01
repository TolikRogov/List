#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "Lists_errors.hpp"

typedef int Data_t;
typedef int Indexes_t;

#ifdef LIST_CONSOLE_DUMP
	#define LST_CON_DUMP_(list)	{			\
		list_status = ListPrint(list);		\
		LIST_ERROR_CHECK(list_status);		\
	}
#else
	#define LST_CON_DUMP_(list)
#endif

#define LIST_CTOR(list, ...) {							\
	list_status = ListCtor(list __VA_ARGS__);			\
	LIST_ERROR_CHECK(list_status);						\
	LST_CON_DUMP_(list);								\
}

#define LIST_INSERT_AFTER(list, ...) {					\
	list_status = ListInsertAfter(list, __VA_ARGS__); 	\
	LIST_ERROR_CHECK(list_status);						\
	LST_CON_DUMP_(list);								\
}

#define LIST_OUTSERT(list, ...) {						\
	list_status = ListOutsert(list, __VA_ARGS__); 		\
	LIST_ERROR_CHECK(list_status);						\
	LST_CON_DUMP_(list);								\
}

#define LIST_DTOR(list, ...) {							\
	list_status = ListDtor(list __VA_ARGS__);			\
	LIST_ERROR_CHECK(list_status);						\
}

struct Data_elem {
	Indexes_t prev;
	Data_t data;
	Indexes_t next;
};

struct List {
	Indexes_t head;
	Indexes_t tail;
	Indexes_t free;

	size_t capacity;
	size_t size;
	Data_elem* elems;
};

const size_t LIST_DEFAULT_DATA_CAPACITY = 20;

const size_t LIST_TRASH = 0xDED104;

const Data_t LIST_POISON = -666;

ListStatusCode ListCtor(List* list);
ListStatusCode ListDtor(List* list);

ListStatusCode FindFree(List* list);

ListStatusCode ListInsertAfter(List* list, Data_t element, Indexes_t pos);

ListStatusCode ListOutsert(List* list, Data_t* var_addr, Indexes_t pos);
