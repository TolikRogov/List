#include "Lists_errors.hpp"

const char* ListErrorsMessenger(ListStatusCode status) {
	switch (status) {
		case LIST_NO_ERROR:						return "LIST ERROR - NO ERROR";

		case LIST_ALLOC_ERROR:					return "LIST ERROR - MEMORY ALLOCATION ERROR";

		default: 								return "LIST ERROR - UNDEFINED ERROR";
	}
}