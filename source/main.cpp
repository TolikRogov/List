#include "Lists.hpp"
#include "Lists_dump.hpp"

int main() {

	ListStatusCode list_status = LIST_NO_ERROR;

	List list = {};

	LIST_CTOR(&list);

// 	for (size_t i = 10, j = 0; i < 100 && j < list.capacity; i += 10, j++)
// 		LIST_INSERT_AFTER(&list, i, j);
//
	LIST_INSERT_AFTER(&list, 25, 0);
	LIST_INSERT_AFTER(&list, 333, 1);
	LIST_INSERT_AFTER(&list, 35, 0);
//
// 	Data_t x = 0;
// 	LIST_OUTSERT(&list, &x, 6);
// 	printf("x = %d\n", x);
//
// 	LIST_INSERT_AFTER(&list, 95, 9);
// 	LIST_INSERT_AFTER(&list, 5, 0);

	LIST_DTOR(&list);

	return 0;
}
