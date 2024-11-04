#include "Lists_dump.hpp"
#include "Lists.hpp"

int main() {

	ListStatusCode list_status = LIST_NO_ERROR;

	INIT_LIST(list);

	LIST_CTOR(&list);

	for (size_t i = 10, j = 0; i < 100 && j < list.capacity; i += 10, j++)
		LIST_INSERT_AFTER(&list, i, j);

	Data_t x = 0;
	LIST_OUTSERT(&list, &x, 5);

	LIST_HTML_DUMP(&list);

	LIST_DTOR(&list);

	return 0;
}
