#include "Lists_dump.hpp"
#include "Colors"

long AMOUNT_OF_LAST_SYMBOLS = 0;

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

	HTML_PRINTF("\t<div class='dump'>\n");
	HTML_PRINTF("\tColors meanings: \n");
	HTML_PRINTF("\t\t<div class='circle' style='background-color: %.7s; border-color: %.7s;'>occupied node</div>", color.occupied_node + 1, color.occupied_node_border + 1);
	HTML_PRINTF("\t\t<span style='color: %.7s'>&#11153; prev arrows</span>\n", color.prev_arrows + 1);
	HTML_PRINTF("\t\t<div class='circle' style='background-color: %.7s; border-color: %.7s;'>free node</div>", color.free_node + 1, color.free_node_border + 1);
	HTML_PRINTF("\t\t\t<span style='color: %.7s'>&#11153; next arrows</span>\n", color.next_arrows + 1);
	HTML_PRINTF("\t\t<div class='circle' style='background-color: %.7s; border-color: %.7s;'>head</div>", color.head + 1, color.head_border + 1);
	HTML_PRINTF("\t\t\t\t<span style='color: %.7s'>&#11153; head arrow</span>\n", color.head_arrow + 1);
	HTML_PRINTF("\t\t<div class='circle' style='background-color: %.7s; border-color: %.7s;'>tail</div>", color.tail + 1, color.tail_border + 1);
	HTML_PRINTF("\t\t\t\t<span style='color: %.7s'>&#11153; tail arrow</span>\n", color.tail_arrow + 1);
	HTML_PRINTF("\t\t<div class='circle' style='background-color: %.7s; border-color: %.7s;'>free</div>", color.free + 1, color.free_border + 1);
	HTML_PRINTF("\t\t\t\t<span style='color: %.7s'>&#11153; free arrow</span>\n", color.free_arrow + 1);
	HTML_PRINTF("\t\t<div class='circle' style='background-color: %.7s; border-color: %.7s;'>zero node</div>", color.zero_node + 1, color.zero_node_border + 1);
	HTML_PRINTF("\t\t\t<span style='color: %.7s'>&#11153; zero next arrow</span>\n", color.zero_next_arrow + 1);
	HTML_PRINTF("\t\t<div class='circle' style='background-color: %.7s; border-color: %.7s;'>insert node</div>", color.insert_node + 1, color.insert_node_border + 1);
	HTML_PRINTF("\t\t\t<span style='color: %.7s'>&#11153; zero prev arrow</span>\n", color.zero_prev_arrow + 1);
	HTML_PRINTF("\t\t<div class='circle' style='background-color: %.7s; border-color: %.7s;'>outsert node</div>\n", color.outsert_node + 1, color.outsert_node_border + 1);
	HTML_PRINTF("\t</div>\n\n");

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

	CSS_PRINTF(".circle {\n"\
			"\tdisplay: inline-block;\n"\
			"\tborder-radius: 50%%;\n"\
			"\tborder: 1px solid;\n"\
			"\tpadding: 10px;\n"\
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

	AMOUNT_OF_LAST_SYMBOLS = 0;

#define HTML_PRINTF(...) AMOUNT_OF_LAST_SYMBOLS += fprintf(html_file, __VA_ARGS__);

	HTML_PRINTF("\t</pre></tt></body>\n");
	HTML_PRINTF("</html>\n");

#undef HTML_PRINTF

	if (fclose(html_file))
		LIST_ERROR_CHECK(LIST_FILE_CLOSE_ERROR);

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

	FILE* html_file = fopen(HTML_FILE_, "r+");
	if (!html_file)
		LIST_ERROR_CHECK(LIST_FILE_OPEN_ERROR);

	fseek(html_file, 0, SEEK_END);

#define HTML_PRINTF(...) fprintf(html_file, __VA_ARGS__);

	if (AMOUNT_OF_LAST_SYMBOLS)
		fseek(html_file, -AMOUNT_OF_LAST_SYMBOLS, SEEK_END);

	if (StrCmp(prev_info.file_name, list->info.file_name) != 0 || prev_info.line != list->info.line || StrCmp(prev_info.var_name, list->info.name) != 0)
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

#define DOT_PRINTF(...) fprintf(dot_file, __VA_ARGS__);

	DOT_PRINTF("digraph {\n");

	DOT_PRINTF("\trankdir = LR;\n");
	DOT_PRINTF("\tfontname = \"UbuntuMono\";\n");
	DOT_PRINTF("\tbgcolor = %s;\n\n", color.background);

	DOT_PRINTF("\tsubgraph cluster_nodes {\n");
	DOT_PRINTF("\t\tperipheries = 0;\n");
	DOT_PRINTF("\t\tnode000 [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; label = \" %.3d | data = %d | <next> next = %d | <prev> prev = %d \"; ];\n",
						color.zero_node, color.zero_node_border, 0, list->elems[0].data, list->elems[0].next, list->elems[0].prev);
	for (size_t i = 1; i < list->capacity; i++) {
		if (list->elems[i].prev == -1) {
			DOT_PRINTF("\t\tnode%.3zu [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; label = \" %.3zu | data = %d | <next> next = %d | <prev> prev = %d \"; ];\n",
						 i, color.free_node, color.free_node_border, i, list->elems[i].data, list->elems[i].next, list->elems[i].prev);
		}
		else {
			DOT_PRINTF("\t\tnode%.3zu [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; label = \" %.3zu | data = %d | <next> next = %d | <prev> prev = %d \"; ];\n",
						i, color.occupied_node, color.occupied_node_border, i, list->elems[i].data, list->elems[i].next, list->elems[i].prev);
		}
	}

	if (StrCmp(dump_info.func, "INSERT_AFTER") == 0) {
		Indexes_t cur_pos = list->elems[dump_info.pos].next;
		DOT_PRINTF("\t\tnode%.3d [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; label = \" %.3d | data = %d | <next> next = %d | <prev> prev = %d \"; ];\n",
					cur_pos, color.insert_node, color.insert_node_border, cur_pos,
					list->elems[cur_pos].data, list->elems[cur_pos].next, list->elems[cur_pos].prev);
	}
	if (StrCmp(dump_info.func, "OUTSERT") == 0) {
		DOT_PRINTF("\t\tnode%.3d [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; label = \" %.3d | data = %d | <next> next = %d | <prev> prev = %d \"; ];\n",
					dump_info.pos, color.outsert_node, color.outsert_node_border, dump_info.pos,
					list->elems[dump_info.pos].data, list->elems[dump_info.pos].next, list->elems[dump_info.pos].prev);
	}

	for (size_t i = 1; i < list->capacity; i++)
		DOT_PRINTF("\t\tnode%.3zu -> node%.3zu [ weight = 1000; style = \"invis\"; ];\n", i - 1, i);

	for (size_t i = 0; i < list->capacity; i++) {
		if (list->elems[i].prev == -1)
			continue;

		if (fabs((Indexes_t)i - list->elems[i].prev) > 1)
			DOT_PRINTF("\t\tnode%.3zu -> node%.3d [ color = %s; ];\n", i, list->elems[i].prev, (i == 0 ? color.zero_prev_arrow : color.prev_arrows));

		if (fabs((Indexes_t)i - list->elems[i].next) < 2 && list->elems[i].next != 0) {
			DOT_PRINTF("\t\tnode%.3zu -> node%.3d [ dir = \"both\"; color = %s; ];\n", i, list->elems[i].next, color.both_dir_arrow);
			continue;
		}

		if (list->size == 2)
			continue;

		DOT_PRINTF("\t\tnode%.3zu -> node%.3d [ color = %s; ];\n", i, list->elems[i].next, (i == 0 ? color.zero_next_arrow : color.next_arrows));
	}

	DOT_PRINTF("\t}\n\n");

	DOT_PRINTF("\tsubgraph cluster_utils {\n");
	DOT_PRINTF("\t\tperipheries = 0;\n");
	DOT_PRINTF("\t\tnodeHead [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; fontcolor = %s; label = \"HEAD | %d\"; ];\n",
				color.head, color.head_border, color.head_font, ListGetHead(list));
	DOT_PRINTF("\t\tnodeTail [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; fontcolor = %s; label = \"TAIL | %d\"; ];\n",
				color.tail, color.tail_border, color.tail_font, ListGetTail(list));
	DOT_PRINTF("\t\tnodeFree [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; fontcolor = %s; label = \"FREE | %d\"; ];\n",
				color.free, color.free_border, color.free_font, list->free);
	DOT_PRINTF("\t\tnodeHead -> nodeTail [ weight = 1000; style = \"invis\"; ];\n");
	DOT_PRINTF("\t\tnodeTail -> nodeFree [ weight = 1000; style = \"invis\"; ];\n");
	DOT_PRINTF("\t\tnodeHead -> node%.3d:<prev> [ style = \"bold\"; color = %s ];\n", ListGetHead(list), color.head_arrow);
	DOT_PRINTF("\t\tnodeTail -> node%.3d:<prev> [ style = \"bold\"; color = %s ];\n", ListGetTail(list), color.tail_arrow);
	DOT_PRINTF("\t\tnodeFree -> node%.3d:<prev> [ style = \"bold\"; color = %s ];\n", list->free, color.free_arrow);
	DOT_PRINTF("\t}\n\n");

	DOT_PRINTF("}\n");

#undef DOT_PRINTF

	if (fclose(dot_file))
		LIST_ERROR_CHECK(LIST_FILE_CLOSE_ERROR);

	list_status = ListBashScript(list, dump_info);
	LIST_ERROR_CHECK(list_status);

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
