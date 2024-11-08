#ifndef LISTS_INCLUDE
#define LISTS_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "Lists_errors.hpp"

typedef int Data_t;
typedef int Indexes_t;

#define INIT_LIST(list) List list = { .info = {#list, __FILE__, __LINE__}}

#ifdef LIST_CONSOLE_DUMP
	#define LST_CON_DUMP_(list)	{			\
		list_status = ListPrint(list);		\
		LIST_ERROR_CHECK(list_status);		\
	}
#else
	#define LST_CON_DUMP_(list)
#endif

#define LIST_HTML_DUMP_START() {					 	 \
	list_status = ListHtmlDumpStart();					\
	LIST_ERROR_CHECK(list_status);						\
}

#define LIST_HTML_DUMP_FINISH() {					 	 \
	list_status = ListHtmlDumpFinish();					\
	LIST_ERROR_CHECK(list_status);						\
}

#define LIST_GRAPH_DUMP(list, func_name) {							 								 \
	list_status = ListGraphDump(list, {.file = __FILE__, .line = __LINE__, .func = func_name}); 	 \
	LIST_ERROR_CHECK(list_status);																	\
}

#define LIST_CTOR(list) {								 \
	list_status = ListCtor(list);						\
	LIST_ERROR_CHECK(list_status);						\
	LST_CON_DUMP_(list);								\
}

#define LIST_VERIFY(list, ...) {						 \
	list_status = ListVerify(list, __VA_ARGS__);		\
	LIST_ERROR_CHECK(list_status);						\
}

#define LIST_INSERT_AFTER(list, ...) {					 \
	list_status = ListInsertAfter(list, __VA_ARGS__); 	\
	LIST_ERROR_CHECK(list_status);						\
	LST_CON_DUMP_(list);								\
	LIST_GRAPH_DUMP(list, "INSERT_AFTER");				\
}

#define LIST_OUTSERT(list, ...) {						 \
	list_status = ListOutsert(list, __VA_ARGS__); 		\
	LIST_ERROR_CHECK(list_status);						\
	LST_CON_DUMP_(list);								\
	LIST_GRAPH_DUMP(list, "OUTSERT");					\
}

#define LIST_DTOR(list) {								 \
	LIST_HTML_DUMP_FINISH();							\
	list_status = ListDtor(list);						\
	LIST_ERROR_CHECK(list_status);						\
}

struct ListLogInfo {
	const char* name;
	const char* file_name;
	const size_t line;
};

struct Data_elem {
	Indexes_t prev;
	Data_t data;
	Indexes_t next;
};

struct List {
	Indexes_t free;

	size_t capacity;
	size_t size;
	Data_elem* elems;

	ListLogInfo info;
};

enum DumpCheck {
	FIRST_RUN 	= 1,
	SECOND_RUN 	= 2,
	ALREADY_ON	= 3,
};

const size_t LIST_DEFAULT_DATA_CAPACITY = 20;

const size_t LIST_TRASH = 0xDED104;

const Data_t LIST_POISON = -666;

const size_t REALLOC_INDEX = 2;

const size_t GRAPH_DUMP_INDEX = 10;

ListStatusCode ListCtor(List* list);
ListStatusCode ListHtmlDumpStart();

ListStatusCode ListPrint(List* list);

ListStatusCode ListHtmlDumpFinish();
ListStatusCode ListDtor(List* list);

ListStatusCode ListVerify(List* list, Indexes_t pos);
ListStatusCode ListRealloc(List* list);

Indexes_t ListGetHead(List* list);
Indexes_t ListGetTail(List* list);

ListStatusCode ListInsertAfter(List* list, Data_t element, Indexes_t pos);

ListStatusCode ListOutsert(List* list, Data_t* var_addr, Indexes_t pos);

#endif //LISTS_INCLUDE
