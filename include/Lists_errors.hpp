#ifndef LISTS_ERRORS_INCLUDE
#define LISTS_ERRORS_INCLUDE

#include <stdio.h>

#define RED(str) 		"\033[31;1m" str "\033[0m"
#define YELLOW(str) 	"\033[33;4m" str "\033[0m"
#define GREEN(str) 		"\033[32;6m" str "\033[0m"

#define LIST_ERROR_CHECK(status) {																					 \
	if (status != LIST_NO_ERROR) {																					\
		fprintf(stderr, "\n\n" RED("Error (code %d): %s, ") YELLOW("File: %s, Function: %s, Line: %d\n\n"),   		\
					status, ListErrorsMessenger(status), __FILE__, __PRETTY_FUNCTION__, __LINE__);					\
		fclose(stderr);																								\
		return status;																								\
	}																												\
}

enum ListStatusCode {
	LIST_NO_ERROR,

	LIST_ALLOC_ERROR,
	LIST_NULL_POINTER,

	LIST_FULL_LIST,
	LIST_SIZE_ABOVE_CAPACITY,

	LIST_WRONG_FREE_ELEMENT,
	LIST_WRONG_ELEMENT_POSITION,

	LIST_FILE_OPEN_ERROR,
	LIST_FILE_CLOSE_ERROR,

	LIST_DIR_CLOSE_ERROR,

	LIST_LOOP_ERROR,
	LIST_INSERT_AFTER_FREE,
	LIST_OUTSIDE_INTERFERENCE,
};

const char* ListErrorsMessenger(ListStatusCode status);
int StrCmp(const char* str1, const char* str2);

#endif //LISTS_ERRORS_INCLUDE
