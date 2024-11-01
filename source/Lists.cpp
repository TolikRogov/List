#include "Lists.hpp"

ListStatusCode ListCtor(List* list) {

	list->head = 0;
	list->tail = 1;

	list->capacity = LIST_DEFAULT_DATA_CAPACITY;

	list->elems = (Data_elem*)calloc(list->capacity, sizeof(Data_elem));
	if (!list->elems)
		LIST_ERROR_CHECK(LIST_ALLOC_ERROR);

	for (size_t i = 1; i < list->capacity; i++)
		list->elems[i].next = list->elems[i].prev = -1;

	for (size_t i = 1; i < list->capacity; i++)
		list->elems[i].data = LIST_POISON;

	return LIST_NO_ERROR;
}

ListStatusCode FindFree(List* list) {

	for (size_t i = 0; i < list->capacity; i++) {
		if (list->elems[i].prev == -1) {
			list->free = i;
			return LIST_NO_ERROR;
		}
	}

	return LIST_FULL_LIST;
}

ListStatusCode ListInsertAfter(List* list, Data_t element, Indexes_t pos) {

	ListStatusCode list_status = LIST_NO_ERROR;

	list_status = FindFree(list);
	LIST_ERROR_CHECK(list_status);

	//NOTE: Случай, когда вставляем в пустой список (ещё нет head)
	if (list->head == 0) {
		list->elems[list->free].data = element;

		list->elems[list->free].next = 0;
		list->elems[pos].next = list->free;

		list->elems[list->free].prev = pos;

		list->size++;
		list->head = 1;

		return LIST_NO_ERROR;
	}

	//NOTE: Случай, когда добавляем в конец списка (после tail)
	if (list->tail == pos) {
		list->elems[list->free].data = element;

		list->elems[list->free].next = list->elems[pos].next;
		list->elems[pos].next = list->free;

		list->elems[list->free].prev = pos;

		list->size++;
		list->tail = list->free;

		return LIST_NO_ERROR;
	}

	//NOTE: Случай, когда добавляем перед первым (перед head)
	if (pos <= list->head) {
		list->elems[list->free].data = element;

		list->elems[list->free].next = list->head;
		list->elems[pos].next = 0;

		list->elems[list->free].prev = pos;
		list->elems[list->elems[list->free].next].prev = list->free;

		list->size++;
		list->head = list->free;

		return LIST_NO_ERROR;
	}

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

	*var_addr = list->elems[pos].data;
	list->elems[pos].data = LIST_POISON;

	list->elems[list->elems[pos].prev].next = list->elems[pos].next;
	list->elems[list->elems[pos].next].prev = list->elems[pos].prev;

	list->elems[pos].next = list->elems[pos].prev = -1;

	list->size--;

	return LIST_NO_ERROR;
}

ListStatusCode ListDtor(List* list) {

	list->head = list->tail = list->free = LIST_TRASH;

	if (list->elems) {
		free(list->elems);
		list->elems = NULL;
	}

	return LIST_NO_ERROR;
}
