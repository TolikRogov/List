#include "Lists.hpp"

int main() {

	ListStatusCode list_status = LIST_NO_ERROR;

	List list = {};

	list_status = ListCtor(&list);
	LIST_ERROR_CHECK(list_status);



	list_status = ListDtor(&list);
	LIST_ERROR_CHECK(list_status);

	return 0;
}
