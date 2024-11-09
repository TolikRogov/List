#include "Lists_errors.hpp"

const char* ListErrorsMessenger(ListStatusCode status) {
	switch (status) {
		case LIST_NO_ERROR:						return "LIST ERROR - NO ERROR";

		case LIST_ALLOC_ERROR:					return "LIST ERROR - MEMORY ALLOCATION ERROR";
		case LIST_NULL_POINTER:					return "LIST ERROR - POINTER IS NULL";

		case LIST_FULL_LIST:					return "LIST ERROR - LIST IS FULL";
		case LIST_SIZE_ABOVE_CAPACITY:			return "LIST ERROR - LIST SIZE ABOVE THAN CAPACITY";

		case LIST_WRONG_FREE_ELEMENT:			return "LIST ERROR - FOUNDED FREE ELEMENT IS NOT FREE";
		case LIST_WRONG_ELEMENT_POSITION:		return "LIST ERROR - DECLARED POSITION OF ELEMENT IS NO VALID";

		case LIST_FILE_OPEN_ERROR:				return "LIST ERROR - FILE WAS NOT OPENED";
		case LIST_FILE_CLOSE_ERROR:				return "LIST ERROR - FILE WAS NOT CLOSED";

		case LIST_DIR_CLOSE_ERROR:				return "LIST ERROR - DIRECTORY WAS NOT CLOSED";

		case LIST_LOOP_ERROR:					return "LIST ERROR - LIST PENETRATION GETS MORE ELEMENTS THAN IN REAL";
		case LIST_INSERT_AFTER_FREE:			return "LIST ERROR - TRYING TO INSERT NEW ELEMENT AFTER INVALID ONE";
		case LIST_OUTSIDE_INTERFERENCE:			return "LIST ERROR - LIST WAS CHANGED BY OUTSIDE INTERFERENCE";

		default: 								return "LIST ERROR - UNDEFINED ERROR";
	}
}

int StrCmp(const char* str1, const char* str2) {

	if (!str1 || !str2)
		return -1;

	size_t i = 0;
	for (; *(str1 + i) != '\0' && *(str2 + i) != '\0'; i++) {
		if (*(str1 + i) != *(str2 + i))
			break;
	}
	return (*(str1 + i) - *(str2 + i));
}
