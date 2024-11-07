#ifndef LISTS_DUMP_INCLUDE
#define LISTS_DUMP_INCLUDE

#include "Lists.hpp"

#define DUMP_DIR_ 		"dump/"
#define IMG_DIR_		"img/"

#define DOT_FILE_ 		DUMP_DIR_ "graph.dot"
#define IMG_FILE_  		IMG_DIR_ "graph"
#define HTML_FILE_ 		DUMP_DIR_ "main.html"
#define BASH_FILE_		DUMP_DIR_ "script.bash"

#define IMG_EXTENSION 	".png"

#ifdef __APPLE__
	#define OPEN	"open "
#else
	#define OPEN	"xdg-open "
#endif

ListStatusCode ListPrint(List* list);
ListStatusCode ListHtmlDumpStart();
ListStatusCode ListHtmlDumpFinish();
ListStatusCode ListGraphDump(List* list);

ListStatusCode ListGraphCaptiveCluster(List* list, FILE* dot_file);
ListStatusCode ListGraphFreeCluster(List* list, FILE* dot_file);

ListStatusCode ListBashScript(List* list);

#endif //LISTS_DUMP_INCLUDE
