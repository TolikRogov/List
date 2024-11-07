#include "Lists.hpp"

ListStatusCode ListCtor(List* list) {

	list->size = 1;
	list->free = 0;

	list->capacity = LIST_DEFAULT_DATA_CAPACITY;

	list->elems = (Data_elem*)calloc(list->capacity, sizeof(Data_elem));
	if (!list->elems)
		LIST_ERROR_CHECK(LIST_ALLOC_ERROR);

	for (size_t i = 1; i < list->capacity; i++) {
		list->elems[i].next = list->elems[i].prev = -1;
		list->elems[i].data = LIST_POISON;
	}

	return LIST_NO_ERROR;
}

ListStatusCode ListVerify(List* list, Indexes_t pos) {

	ListStatusCode list_status = LIST_NO_ERROR;

	if (list->size > list->capacity)
		return LIST_SIZE_ABOVE_CAPACITY;

	if (list->size == list->capacity) {
		list_status = ListRealloc(list);
		LIST_ERROR_CHECK(list_status);
	}

	list_status = FindFree(list);
	LIST_ERROR_CHECK(list_status);

	if (list->elems[list->free].prev != -1)
		return LIST_WRONG_FREE_ELEMENT;

	if (pos < 0 || pos > (int)list->capacity || pos > list->free + 1)
		return LIST_WRONG_ELEMENT_POSITION;

	return LIST_NO_ERROR;
}

ListStatusCode ListRealloc(List* list) {

	if (list->size < list->capacity)
		return LIST_NO_ERROR;

	list->elems = (Data_elem*)realloc(list->elems, (list->capacity *= REALLOC_INDEX) * sizeof(Data_elem));
	if (!list->elems)
		return LIST_ALLOC_ERROR;

	for (size_t i = list->capacity / REALLOC_INDEX; i < list->capacity; i++) {
		list->elems[i].next = list->elems[i].prev = -1;
		list->elems[i].data = LIST_POISON;
	}

	return LIST_NO_ERROR;
}

ListStatusCode FindFree(List* list) {

	for (size_t i = 0; i < list->capacity; i++) {
		if (list->elems[i].prev == -1) {
			list->free = (int)i;
			return LIST_NO_ERROR;
		}
	}

	list->free = -1;

	return LIST_FULL_LIST;
}

Indexes_t ListGetHead(List* list) {
	return list->elems[0].next;
}

Indexes_t ListGetTail(List* list) {
	return list->elems[0].prev;
}
//TODO: ListInsertBefore
ListStatusCode ListInsertAfter(List* list, Data_t element, Indexes_t pos) {

	ListStatusCode list_status = LIST_NO_ERROR;

	LIST_VERIFY(list, pos);

	list->elems[list->free].data = element;

	list->elems[list->free].next = list->elems[pos].next;
	list->elems[pos].next = list->free;

	list->elems[list->free].prev = pos;
	list->elems[list->elems[list->free].next].prev = list->free;

	list->size++;

	return LIST_NO_ERROR;
}

ListStatusCode ListOutsert(List* list, Data_t* var_addr, Indexes_t pos) {

	ListStatusCode list_status = LIST_NO_ERROR;

	LIST_VERIFY(list, pos);

	*var_addr = list->elems[pos].data;
	list->elems[pos].data = LIST_POISON;

	list->elems[list->elems[pos].prev].next = list->elems[pos].next;
	list->elems[list->elems[pos].next].prev = list->elems[pos].prev;

	list->elems[pos].next = list->elems[pos].prev = -1;

	list->size--;

	list_status = FindFree(list);
	LIST_ERROR_CHECK(list_status);

	return LIST_NO_ERROR;
}

ListStatusCode ListDtor(List* list) {

	list->free 		= LIST_TRASH;
	list->size 		= LIST_TRASH;
	list->capacity 	= LIST_TRASH;

	if (list->elems) {
		free(list->elems);
		list->elems = NULL;
	}

	return LIST_NO_ERROR;
}
