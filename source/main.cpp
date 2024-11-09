#include "Lists_dump.hpp"
#include "Lists.hpp"

int main() {

	ListStatusCode list_status = LIST_NO_ERROR;

	INIT_LIST(list);

	LIST_CTOR(&list);

	Indexes_t j = 0;
	for (Data_t i = 10; i < 100 && j < (Indexes_t)list.capacity; i += 10, j++)
		LIST_INSERT_AFTER(&list, i, j);

	Data_t x = 0;
	LIST_OUTSERT(&list, &x, 5);
	LIST_OUTSERT(&list, &x, 6);

	LIST_INSERT_AFTER(&list, 333, 0);

	INIT_LIST(list2);

	LIST_CTOR(&list2);

	j = 0;
	for (Data_t i = 10; i < 100 && j < (Indexes_t)list.capacity; i += 10, j++)
		LIST_INSERT_AFTER(&list2, (-1) * i, j);

	LIST_INSERT_AFTER(&list, 999, 4);

	LIST_DTOR(&list);

	LIST_OUTSERT(&list2, &x, 5);

	LIST_DTOR(&list2);

#ifdef OPEN_HTML_FILE
	system(OPEN HTML_FILE_);
#endif

	return 0;
}
