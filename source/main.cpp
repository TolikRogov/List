#include "Lists_dump.hpp"
#include "Lists.hpp"

int main() {

	ListStatusCode list_status = LIST_NO_ERROR;

	List list = {};

	LIST_CTOR(&list);

	for (size_t i = 10, j = 0; i < 100 && j < list.capacity; i += 10, j++)
		LIST_INSERT_AFTER(&list, i, j);

	list_status = ListGraphDump(&list);
	LIST_ERROR_CHECK(list_status);

	LIST_DTOR(&list);

	return 0;
}
