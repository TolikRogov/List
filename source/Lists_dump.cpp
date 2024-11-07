#include "Lists_dump.hpp"

ListStatusCode ListHtmlDumpStart() {

	ListStatusCode list_status = LIST_NO_ERROR;

	list_status = ListCreateDumpDir();
	LIST_ERROR_CHECK(list_status);

	FILE* html_file = fopen(HTML_FILE_, "w");
	if (!html_file)
		LIST_ERROR_CHECK(LIST_FILE_OPEN_ERROR);

	list_status = ListCssFile();
	LIST_ERROR_CHECK(list_status);

#define HTML_PRINTF(...) fprintf(html_file, __VA_ARGS__);

	HTML_PRINTF("<!DOCTYPE HTML PUBLIC>\n");
	HTML_PRINTF("<html lang=\"ru\">\n");

	HTML_PRINTF("\t<head>\n");
	HTML_PRINTF("\t\t<title>List Dump</title>\n");
	HTML_PRINTF("\t\t<meta charset=\"utf-8\" />\n");
	HTML_PRINTF("\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"styles.css\" />\n");
	HTML_PRINTF("\t</head>\n");

	HTML_PRINTF("\t<body><tt><pre>\n");
	HTML_PRINTF("\t\t\t\t\t\t\t\t\t\t\t<a class='head'>MEGA DUMP</a><br>\n");

#undef HTML_PRINTF

	if (fclose(html_file))
		LIST_ERROR_CHECK(LIST_FILE_CLOSE_ERROR);

	return LIST_NO_ERROR;
}

ListStatusCode ListCssFile() {

	FILE* css_file = fopen(CSS_FILE_, "w");
	if (!css_file)
		LIST_ERROR_CHECK(LIST_FILE_OPEN_ERROR);

#define CSS_PRINTF(...) fprintf(css_file, __VA_ARGS__);

	CSS_PRINTF("body {\n"\
			   "\tbackground-color: #FFFAFA;\n"\
			   "}\n");

	CSS_PRINTF("h1 {\n"\
			   "\ttext-align: center;\n"\
			   "}\n");

	CSS_PRINTF("b {\n"\
			   "\ttext-decoration: underline;\n"\
			   "}\n");

	CSS_PRINTF(".head {\n"\
			   "\tfont-size: 2em;\n"\
    		   "\tfont-weight: bold;\n"\
			   "}\n");

	CSS_PRINTF(".addr {\n"\
			   "\tcolor: #4B0082;\n"\
			   "}\n");

	CSS_PRINTF(".path {\n"\
			   "\tcolor: #FFA500;\n"\
			   "}\n");

	CSS_PRINTF(".line {\n"\
			   "\tcolor: #20B2AA;\n"\
			   "}\n");

	CSS_PRINTF(".name {\n"\
			   "\tcolor: #7B68EE;\n"\
			   "}\n");

	CSS_PRINTF(".dump {\n"\
			   "\tbackground-color: #F7F7F7;\n"\
			   "\tborder: 1px solid #C6C1C1;\n"\
			   "\tborder-radius: 20px;\n"\
			   "\tpadding: 25px 0px;\n"\
			   "\tmargin: 20px 0px;\n"\
			   "\twidth: 90%%;"\
			   "\tdisplay: inline-block;\n"\
			   "}\n");

	CSS_PRINTF(".num {\n"\
			   "\tcolor: #BDB76B;\n"\
			   "}\n");

	CSS_PRINTF(".func {\n"\
			   "\tcolor: #8B008B;"\
			   "}\n");

	CSS_PRINTF(".img {\n"\
			   "\twidth: 90%%;\n"\
			   "\theight: 70%%;\n"\
			   "\tobject-fit: contain;\n"\
			   "}\n");

#undef CSS_PRINTF

	if (fclose(css_file))
		LIST_ERROR_CHECK(LIST_FILE_CLOSE_ERROR);

	return LIST_NO_ERROR;
}

ListStatusCode ListCreateDumpDir() {

	DIR* dump_dir = opendir(DUMP_DIR_);
	if (dump_dir) {
		if (closedir(dump_dir))
			LIST_ERROR_CHECK(LIST_DIR_CLOSE_ERROR);
		system("rm -rf " DUMP_DIR_);
	}
	system("mkdir " DUMP_DIR_);

	DIR* img_dir = opendir(DUMP_DIR_ IMG_DIR_);
	if (!img_dir)
		system("mkdir " DUMP_DIR_ IMG_DIR_);
	else {
		if (closedir(img_dir))
			LIST_ERROR_CHECK(LIST_DIR_CLOSE_ERROR);
	}

	return LIST_NO_ERROR;
}

ListStatusCode ListHtmlDumpFinish() {

	FILE* html_file = fopen(HTML_FILE_, "a");
	if (!html_file)
		LIST_ERROR_CHECK(LIST_FILE_OPEN_ERROR);

#define HTML_PRINTF(...) fprintf(html_file, __VA_ARGS__);

	HTML_PRINTF("\t</pre></tt></body>\n");
	HTML_PRINTF("</html>\n");

#undef HTML_PRINTF

	if (fclose(html_file))
		LIST_ERROR_CHECK(LIST_FILE_CLOSE_ERROR);

#ifdef OPEN_HTML_FILE
	system(OPEN HTML_FILE_);
#endif

	return LIST_NO_ERROR;
}

ListStatusCode ListBashScript(List* list, DumpLogInfo dump_info) {

	static size_t script_num = 1;
	static struct PrevLogInfo {
		const char* file_name;
		size_t line;
		const char* var_name;
	} prev_info;

	FILE* bash_script = fopen(BASH_FILE_, "w");
	if (!bash_script)
		LIST_ERROR_CHECK(LIST_FILE_OPEN_ERROR);

#define BASH_PRINTF(...) fprintf(bash_script, __VA_ARGS__);

	BASH_PRINTF("#!/bin/bash\n");

	BASH_PRINTF("script_num=%zu;\\\n", script_num);
	BASH_PRINTF("dot " DOT_FILE_ " -Tpng -o " DUMP_DIR_ IMG_FILE_ "$script_num" IMG_EXTENSION ";\n");

#undef BASH_PRINTF

	if (fclose(bash_script))
		LIST_ERROR_CHECK(LIST_FILE_CLOSE_ERROR);

	system("chmod +x " BASH_FILE_ "; ./" BASH_FILE_);

	FILE* html_file = fopen(HTML_FILE_, "a");
	if (!html_file)
		LIST_ERROR_CHECK(LIST_FILE_OPEN_ERROR);

#define HTML_PRINTF(...) fprintf(html_file, __VA_ARGS__);

	if (StrCmp(prev_info.file_name, list->info.file_name) != 0 && prev_info.line != list->info.line && StrCmp(prev_info.var_name, list->info.name) != 0)
		HTML_PRINTF("\t\t\t\t\t\t<b>List[%p] born at \"%s\": %zu, name '%s'</b>\n", \
					list, (prev_info.file_name = list->info.file_name), (prev_info.line = (size_t)list->info.line), (prev_info.var_name = list->info.name));

	HTML_PRINTF("\t<div class='dump'>\n");
	HTML_PRINTF("\tDUMP #%zu: function %s was called from %s: %zu\n", script_num, dump_info.func, dump_info.file, dump_info.line);
	HTML_PRINTF("\t<img src='%s%zu%s' class='img'></div>\n\n", IMG_FILE_, script_num++, IMG_EXTENSION);

#undef HTML_PRINTF

	if (fclose(html_file))
		LIST_ERROR_CHECK(LIST_FILE_CLOSE_ERROR);

	return LIST_NO_ERROR;
}

ListStatusCode ListGraphDump(List* list, DumpLogInfo dump_info) {

	ListStatusCode list_status = LIST_NO_ERROR;

	FILE* dot_file = fopen(DOT_FILE_, "w");
	if (!dot_file)
		LIST_ERROR_CHECK(LIST_FILE_OPEN_ERROR);

	fprintf(dot_file, "digraph {\n");

	fprintf(dot_file, "\trankdir = LR;\n");
	fprintf(dot_file, "\tfontname = \"UbuntuMono\";\n");
	fprintf(dot_file, "\tbgcolor = \"#F1D1D1\";\n");

	ListGraphFreeCluster(list, dot_file);
	ListGraphCaptiveCluster(list, dot_file);

	fprintf(dot_file, "}\n");

	if (fclose(dot_file))
		LIST_ERROR_CHECK(LIST_FILE_CLOSE_ERROR);

	list_status = ListBashScript(list, dump_info);
	LIST_ERROR_CHECK(list_status);

	return LIST_NO_ERROR;
}

ListStatusCode ListGraphCaptiveCluster(List* list, FILE* dot_file) {

	struct Colors {
		const char* bg 				= "\"#FBC4AB\"";
		const char* edge 			= "\"#F4978E\"";
		const char* edge_border 	= "\"#B55757\"";
		const char* cluster_border 	= "\"#966156\"";
		const char* prev_arrows		= "\"#228B22\"";
		const char* next_arrows 	= "\"#DC143C\"";
		const char* head 			= "\"#088F41\"";
		const char* head_border 	= "\"#014920\"";
		const char* tail 			= "\"#9B5170\"";
		const char* tail_border 	= "\"#56243C\"";
		const char* hat_arrows 		= "\"violet\"";
	} captive_colors;

#define DOT_PRINTF(...) fprintf(dot_file, __VA_ARGS__);

	DOT_PRINTF("\n");

	DOT_PRINTF("\tsubgraph cluster_captive {\n");
	DOT_PRINTF("\t\tbgcolor = %s;\n", captive_colors.bg);
	DOT_PRINTF("\t\tcolor = %s;\n", captive_colors.cluster_border);
	DOT_PRINTF("\t\tlabel = <<B>Occupied cells</B>>;\n");
	DOT_PRINTF("\t\tfontcolor = \"#2F4858\";\n");
	DOT_PRINTF("\t\tfontsize = \"20px\";\n\n");

	DOT_PRINTF("\t\tsubgraph cluster_HeadAndTail {\n");
	DOT_PRINTF("\t\t\tperipheries = 0\n");
	DOT_PRINTF("\t\t\tlabel = \"\";\n");
	DOT_PRINTF("\t\t\tnodeHead [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; fontcolor = \"white\"; label = \"HEAD\"; ];\n",
				captive_colors.head, captive_colors.head_border);
	DOT_PRINTF("\t\t\tnodeTail [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; fontcolor = \"white\"; label = \"TAIL\"; ];\n",
				captive_colors.tail, captive_colors.tail_border);
	DOT_PRINTF("\t\t\tnodeHead -> nodeTail [ color = %s; ];\n", captive_colors.bg);
	DOT_PRINTF("\t\t}\n\n");

	DOT_PRINTF("\t\tsubgraph cluster_occupied {\n");
	DOT_PRINTF("\t\t\tperipheries = 0\n");
	DOT_PRINTF("\t\t\tlabel = \"\";\n");

	for (size_t i = 0; i < list->capacity; i++) {
		if (list->elems[i].prev == -1)
			continue;

		DOT_PRINTF("\t\t\tnode%.3zu [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; label = \" %.3zu | data = %d | next = %d | prev = %d \"; ];\n",
						 i, captive_colors.edge, captive_colors.edge_border, i, list->elems[i].data, list->elems[i].next, list->elems[i].prev);
	}

	DOT_PRINTF("\n");

	for (size_t i = 0; i < list->capacity; i++) {
		if (list->elems[i].prev == -1)
			continue;

		if (list->elems[0].next == (int)i)
			DOT_PRINTF("\t\t\tnodeHead -> node%.3d [ color = %s; ];\n", list->elems[0].next, captive_colors.hat_arrows);

		if (list->elems[0].prev == (int)i)
			DOT_PRINTF("\t\t\tnodeTail -> node%.3d [ color = %s; ];\n", list->elems[0].prev, captive_colors.hat_arrows);

		DOT_PRINTF("\t\t\tnode%.3zu -> node%.3d [ color = %s; ];\n", i, list->elems[i].next, captive_colors.next_arrows);
		DOT_PRINTF("\t\t\tnode%.3zu -> node%.3d [ color = %s; ];\n", i, list->elems[i].prev, captive_colors.prev_arrows);
	}
	DOT_PRINTF("\t\t}\n\n");

	DOT_PRINTF("\t}\n");

	DOT_PRINTF("\n");

#undef DOT_PRINTF

	return LIST_NO_ERROR;
}

ListStatusCode ListGraphFreeCluster(List* list, FILE* dot_file) {

	struct Colors {
		const char* bg 				= "\"#DCEAB2\"";
		const char* edge 			= "\"#5F9A9D\"";
		const char* edge_border 	= "\"#3B6874\"";
		const char* cluster_border	= "\"#b1c274\"";
		const char* free 			= "\"#D1D1D5\"";
		const char* free_border 	= "\"#C1C1C5\"";
		const char* free_arrow 		= "\"#34AB34\"";
	} free_colors;

#define DOT_PRINTF(...) fprintf(dot_file, __VA_ARGS__);

	DOT_PRINTF("\n");

	DOT_PRINTF("\tsubgraph cluster_free {\n");
	DOT_PRINTF("\t\tbgcolor = %s;\n", free_colors.bg);
	DOT_PRINTF("\t\tcolor = %s;\n", free_colors.cluster_border);
	DOT_PRINTF("\t\tlabel = <<B>Free cells</B>>;\n");
	DOT_PRINTF("\t\tfontcolor = \"#2F4858\";\n");
	DOT_PRINTF("\t\tfontsize = \"20px\";\n\n");

	DOT_PRINTF("\t\tsubgraph cluster_Free {\n");
	DOT_PRINTF("\t\t\tperipheries = 0\n");
	DOT_PRINTF("\t\t\tlabel = \"\";\n");
	DOT_PRINTF("\t\t\tnodeFree [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; fontcolor = \"black\"; label = \"FREE\"; ];\n",
				free_colors.free, free_colors.free_border);
	DOT_PRINTF("\t\t}\n\n");

	DOT_PRINTF("\t\tsubgraph cluster_free {\n");
	DOT_PRINTF("\t\t\tperipheries = 0\n");
	DOT_PRINTF("\t\t\tlabel = \"\";\n");
	for (size_t i = 0; i < list->capacity; i++) {
		if (list->elems[i].prev != -1)
			continue;

		DOT_PRINTF("\t\t\tnode%.3zu [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; label = \" %.3zu | data = %d | next = %d | prev = %d \" ];\n",
					i, free_colors.edge, free_colors.edge_border, i, list->elems[i].data, list->elems[i].next, list->elems[i].prev);
	}

	fprintf(dot_file, "\n");

	Indexes_t free = 0;
	DOT_PRINTF("\t\t\tsubgraph cluster_free%.3d {\n", 0);
	DOT_PRINTF("\t\t\t\tperipheries = 0\n");
	DOT_PRINTF("\t\t\t\tlabel = \"\";\n");
	for (size_t i = 0, cnt = 0; i < list->capacity; i++) {
		if (list->elems[i].prev != -1)
			continue;

		if (cnt == 0 && (free = (int)i)) {
			cnt++;
			continue;
		}

		if (cnt++ % GRAPH_DUMP_INDEX == 0) {
			DOT_PRINTF("\t\t\t}\n\n");
			DOT_PRINTF("\t\t\tsubgraph cluster_free%.3zu {\n", cnt / GRAPH_DUMP_INDEX);
			DOT_PRINTF("\t\t\t\tperipheries = 0\n");
			DOT_PRINTF("\t\t\t\tlabel = \"\";\n");
		}
		else {

			DOT_PRINTF("\t\t\t\tnode%.3d -> node%.3zu [ weight = 1000; color = %s; ];\n", free, i, free_colors.bg);
		}
		free = (int)i;
	}
	DOT_PRINTF("\t\t\t}\n\n");

	FindFree(list);
	if (list->free != -1)
		DOT_PRINTF("\t\t\tnodeFree -> node%.3d [ weight = 1000; color = %s; ];\n\n", list->free, free_colors.free_arrow);

	DOT_PRINTF("\t\t}\n");

	DOT_PRINTF("\t}\n\n");

#undef DOT_PRINTF

	return LIST_NO_ERROR;
}

ListStatusCode ListPrint(List* list) {

	for (size_t i = 0; i < 150; i++)
		printf("-");
	printf("\n");

	printf("capacity = %zu\n", list->capacity);
	printf("size = %zu\n", list->size);

	printf("\t");
	for (size_t i = 0; i < list->capacity; i++)
		printf("%4zu ", i);
	printf("\n");

	printf("%8s", "prev: ");
	for (size_t i = 0; i < list->capacity; i++)
		printf("%4d ", list->elems[i].prev);
	printf("\n");

	printf("%8s", "data: ");
	for (size_t i = 0; i < list->capacity; i++)
		printf("%4d ", list->elems[i].data);
	printf("\n");

	printf("%8s", "next: ");
	for (size_t i = 0; i < list->capacity; i++)
		printf("%4d ", list->elems[i].next);
	printf("\n");
	printf("\n");

	FindFree(list);

	printf("free = %d\n", list->free);
	printf("head = %d\n", ListGetHead(list));
	printf("tail = %d\n", ListGetTail(list));

	printf("\nLogical order of list:\n");
	Indexes_t index = ListGetHead(list);
	while (index != 0) {
		printf("%d ", list->elems[index].data);
		index = list->elems[index].next;
	}
	printf("\n");

	for (size_t i = 0; i < 150; i++)
		printf("-");
	printf("\n");

	getchar();

	return LIST_NO_ERROR;
}
