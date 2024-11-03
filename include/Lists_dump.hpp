#ifndef LISTS_DUMP_INCLUDE
#define LISTS_DUMP_INCLUDE

#include "Lists.hpp"

ListStatusCode ListPrint(List* list);
ListStatusCode ListGraphDump(List* list);

ListStatusCode ListGraphCaptiveCluster(List* list, FILE* dot_file);
ListStatusCode ListGraphFreeCluster(List* list, FILE* dot_file);

#endif //LISTS_DUMP_INCLUDE
