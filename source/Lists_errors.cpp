#include "Lists_errors.hpp"

const char* ListErrorsMessenger(ListStatusCode status) {
	switch (status) {
		case LIST_NO_ERROR:						return "LIST ERROR - NO ERROR";

		case LIST_ALLOC_ERROR:					return "LIST ERROR - MEMORY ALLOCATION ERROR";

		case LIST_FULL_LIST:					return "LIST ERROR - LIST IS FULL";
		case LIST_SIZE_ABOVE_CAPACITY:			return "LIST ERROR - LIST SIZE ABOVE THAN CAPACITY";

		case LIST_WRONG_FREE_ELEMENT:			return "LIST ERROR - FOUNDED FREE ELEMENT IS NOT FREE";
		case LIST_WRONG_ELEMENT_POSITION:		return "LIST ERROR - DECLARED POSITION OF ELEMENT IS NO VALID";

		default: 								return "LIST ERROR - UNDEFINED ERROR";
	}
}
