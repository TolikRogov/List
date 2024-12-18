#ifndef LISTS_DUMP_INCLUDE
#define LISTS_DUMP_INCLUDE

#include "Lists.hpp"

#define DUMP_DIR_ 		"dump/"
#define IMG_DIR_		"img/"

#define DOT_FILE_ 		DUMP_DIR_ "graph.dot"
#define IMG_FILE_  		IMG_DIR_  "graph"
#define HTML_FILE_ 		DUMP_DIR_ "list.html"
#define CSS_FILE_		DUMP_DIR_ "styles.css"
#define BASH_FILE_		DUMP_DIR_ "script.bash"

#define IMG_EXTENSION 	".png"

#ifdef __APPLE__
	#define OPEN	"open "
#else
	#define OPEN	"xdg-open "
#endif

struct DumpLogInfo {
	const char* file;
	const size_t line;
	const char* func;
	const Indexes_t pos;
};

ListStatusCode ListCreateDumpDir();
ListStatusCode ListCssFile();

ListStatusCode ListGraphDump(List* list, DumpLogInfo dump_info);

ListStatusCode ListBashScript(List* list, DumpLogInfo dump_info);

#endif //LISTS_DUMP_INCLUDE
