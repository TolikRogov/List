#include "Lists.hpp"

ListStatusCode ListCtor(List* list) {

	list->head = list->tail = 0;

	list->capacity = DEFAULT_DATA_CAPACITY;

	list->data = (Data_t*)calloc(list->capacity, sizeof(Data_t));
	if (!list->data)
		LIST_ERROR_CHECK(LIST_ALLOC_ERROR);

	list->next = (Pointers_t*)calloc(list->capacity, sizeof(Pointers_t));
	if (!list->next)
		LIST_ERROR_CHECK(LIST_ALLOC_ERROR);

	list->prev = (Pointers_t*)calloc(list->capacity, sizeof(Pointers_t));
	if (!list->prev)
		LIST_ERROR_CHECK(LIST_ALLOC_ERROR);

	return LIST_NO_ERROR;
}

ListStatusCode ListDtor(List* list) {

	list->head = list->tail = LIST_TRASH;

	if (list->data) {
		free(list->data);
		list->data = NULL;
	}

	if (list->next) {
		free(list->next);
		list->next = NULL;
	}

	if (list->prev) {
		free(list->prev);
		list->prev = NULL;
	}

	return LIST_NO_ERROR;
}
