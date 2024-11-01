#pragma once

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

	LIST_FULL_LIST
};

const char* ListErrorsMessenger(ListStatusCode status);
