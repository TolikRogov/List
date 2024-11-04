#ifndef LISTS_DUMP_INCLUDE
#define LISTS_DUMP_INCLUDE

#include "Lists.hpp"

#define DOT_FILE_ 	"../dump/graph.dot"
#define IMG_PNG_  	"../dump/graph.png"
#define HTML_FILE_ 	"../dump/main.html"

#ifdef __APPLE__
	#define OPEN	"open "
#else
	#define OPEN	"xdg-open "
#endif

ListStatusCode ListPrint(List* list);
ListStatusCode ListHtmlDump(List* list);
ListStatusCode ListGraphDump(List* list);

ListStatusCode ListGraphCaptiveCluster(List* list, FILE* dot_file);
ListStatusCode ListGraphFreeCluster(List* list, FILE* dot_file);

#endif //LISTS_DUMP_INCLUDE
