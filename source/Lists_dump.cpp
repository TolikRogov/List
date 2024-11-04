#include "Lists_dump.hpp"

ListStatusCode ListHtmlDump(List* list) {

	ListStatusCode list_status = LIST_NO_ERROR;

	FILE* html_file = fopen(HTML_FILE_, "w");
	if (!html_file)
		LIST_ERROR_CHECK(LIST_FILE_OPEN_ERROR);

	LIST_GRAPH_DUMP(list);

	fprintf(html_file, "<!DOCTYPE HTML PUBLIC>\n");
	fprintf(html_file, "<html>\n");

	fprintf(html_file, "\t<head>\n");
	fprintf(html_file, "\t\t<title>Stack Dump</title>\n");
	fprintf(html_file, "\t</head>\n");

	fprintf(html_file, "\t<body style='background-color: #F1F1F1'>\n");

	fprintf(html_file, "\t\t<pre>\n");
	fprintf(html_file, "\t\t<tt>\n");

	fprintf(html_file, "\t\t<h1 align='center'>MEGA DUMP</h1>\n");
	fprintf(html_file, "\t\t<h2 style='text-decoration: underline'><p style='text-align: center'>"
					"List[<span style='color: #4B0082;'>%p</span>] "
					"born at <span style='color: #FFA500;'>%s</span>: <span style='color: #20B2AA;'>%zu</span>, "
					"name '<span style='color: #7B68EE;'>%s</span>'</p></h2>\n",
					list, list->info.file_name, list->info.line, list->info.name);
	fprintf(html_file, "\t\t<img src='%s' style='width: 80%%'>\n", IMG_PNG_);

	fprintf(html_file, "\t\t</tt>\n");
	fprintf(html_file, "\t\t</pre>\n");

	fprintf(html_file, "\t</body>\n");
	fprintf(html_file, "</html>\n");

	if (fclose(html_file))
		LIST_ERROR_CHECK(LIST_FILE_CLOSE_ERROR);

	system(OPEN HTML_FILE_);

	return LIST_NO_ERROR;
}

ListStatusCode ListGraphDump(List* list) {

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

	system("dot " DOT_FILE_ " -Tpng -o " IMG_PNG_);

	return LIST_NO_ERROR;
}

ListStatusCode ListGraphCaptiveCluster(List* list, FILE* dot_file) {

	const char* BG_COLOR = "\"#FBC4AB\"";
	const char* EDGE_COLOR = "\"#F4978E\"";
	const char* EDGE_BORDER_COLOR = "\"#B55757\"";
	const char* CLUSTER_BORDER_COLOR = "\"#966156\"";
	const char* PREV_ARROWS_COLOR = "\"#228B22\"";
	const char* NEXT_ARROWS_COLOR = "\"#DC143C\"";
	const char* HEAD_COLOR = "\"#222B22\"";
	const char* HEAD_BORDER_COLOR = "\"#262B22\"";
	const char* TAIL_COLOR = "\"#562439\"";
	const char* TAIL_BORDER_COLOR = "\"#56243C\"";
	const char* HEAD_AND_TAIL_ARROWs = "\"violet\"";

	fprintf(dot_file, "\n");

	fprintf(dot_file, "\tsubgraph cluster_captive {\n");
	fprintf(dot_file, "\t\tbgcolor = %s;\n", BG_COLOR);
	fprintf(dot_file, "\t\tcolor = %s;\n", CLUSTER_BORDER_COLOR);
	fprintf(dot_file, "\t\tlabel = <<B>Occupied cells</B>>;\n");
	fprintf(dot_file, "\t\tfontcolor = \"#2F4858\";\n");
	fprintf(dot_file, "\t\tfontsize = \"20px\";\n\n");

	fprintf(dot_file, "\t\tsubgraph cluster_HeadAndTail {\n");
	fprintf(dot_file, "\t\t\tperipheries = 0\n");
	fprintf(dot_file, "\t\t\tlabel = \"\";\n");
	fprintf(dot_file, "\t\t\tnodeHead [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; fontcolor = \"white\"; label = \"HEAD\"; ];\n", HEAD_COLOR, HEAD_BORDER_COLOR);
	fprintf(dot_file, "\t\t\tnodeTail [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; fontcolor = \"white\"; label = \"TAIL\"; ];\n", TAIL_COLOR, TAIL_BORDER_COLOR);
	fprintf(dot_file, "\t\t\tnodeHead -> nodeTail [ color = %s; ];\n", BG_COLOR);
	fprintf(dot_file, "\t\t}\n\n");

	fprintf(dot_file, "\t\tsubgraph cluster_occupied {\n");
	fprintf(dot_file, "\t\t\tperipheries = 0\n");
	fprintf(dot_file, "\t\t\tlabel = \"\";\n");

	for (size_t i = 0; i < list->capacity; i++) {
		if (list->elems[i].prev == -1)
			continue;

		fprintf(dot_file, "\t\t\tnode%.3zu [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; label = \" %.3zu | data = %d | next = %d | prev = %d \"; ];\n",
						 i, EDGE_COLOR, EDGE_BORDER_COLOR, i, list->elems[i].data, list->elems[i].next, list->elems[i].prev);
	}

	fprintf(dot_file, "\n");

	for (size_t i = 0, cnt = 0; i < list->capacity; i++) {
		if (list->elems[i].prev == -1)
			continue;

		if (list->elems[0].next == i)
			fprintf(dot_file, "\t\t\tnodeHead -> node%.3d [ color = %s; ];\n", list->elems[0].next, HEAD_AND_TAIL_ARROWs);

		if (list->elems[0].prev == i)
			fprintf(dot_file, "\t\t\tnodeTail -> node%.3d [ color = %s; ];\n", list->elems[0].prev, HEAD_AND_TAIL_ARROWs);

		fprintf(dot_file, "\t\t\tnode%.3zu -> node%.3d [ color = %s; ];\n", i, list->elems[i].next, NEXT_ARROWS_COLOR);
		fprintf(dot_file, "\t\t\tnode%.3zu -> node%.3d [ color = %s; ];\n", i, list->elems[i].prev, PREV_ARROWS_COLOR);
	}
	fprintf(dot_file, "\t\t}\n\n");

	fprintf(dot_file, "\t}\n");

	fprintf(dot_file, "\n");

	return LIST_NO_ERROR;
}

ListStatusCode ListGraphFreeCluster(List* list, FILE* dot_file) {

	const char* BG_COLOR = "\"#DCEAB2\"";
	const char* EDGE_COLOR = "\"#5F9A9D\"";
	const char* EDGE_BORDER_COLOR = "\"#3B6874\"";
	const char* CLUSTER_BORDER_COLOR = "\"#b1c274\"";
	const char* FREE_COLOR = "\"#D1D1D5\"";
	const char* FREE_BORDER_COLOR = "\"#C1C1C5\"";
	const char* FREE_ARROW_COLOR = "\"#34AB34\"";

	fprintf(dot_file, "\n");

	fprintf(dot_file, "\tsubgraph cluster_free {\n");
	fprintf(dot_file, "\t\tbgcolor = %s;\n", BG_COLOR);
	fprintf(dot_file, "\t\tcolor = %s;\n", CLUSTER_BORDER_COLOR);
	fprintf(dot_file, "\t\tlabel = <<B>Free cells</B>>;\n");
	fprintf(dot_file, "\t\tfontcolor = \"#2F4858\";\n");
	fprintf(dot_file, "\t\tfontsize = \"20px\";\n\n");

	fprintf(dot_file, "\t\tsubgraph cluster_Free {\n");
	fprintf(dot_file, "\t\t\tperipheries = 0\n");
	fprintf(dot_file, "\t\t\tlabel = \"\";\n");
	fprintf(dot_file, "\t\t\tnodeFree [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; fontcolor = \"black\"; label = \"FREE\"; ];\n", FREE_COLOR, FREE_BORDER_COLOR);
	fprintf(dot_file, "\t\t}\n\n");

	fprintf(dot_file, "\t\tsubgraph cluster_free {\n");
	fprintf(dot_file, "\t\t\tperipheries = 0\n");
	fprintf(dot_file, "\t\t\tlabel = \"\";\n");
	for (size_t i = 0; i < list->capacity; i++) {
		if (list->elems[i].prev != -1)
			continue;

		fprintf(dot_file, "\t\t\tnode%.3zu [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; label = \" %.3zu | data = %d | next = %d | prev = %d \" ];\n",
						 i, EDGE_COLOR, EDGE_BORDER_COLOR, i, list->elems[i].data, list->elems[i].next, list->elems[i].prev);
	}

	fprintf(dot_file, "\n");

	Indexes_t free = 0;
	fprintf(dot_file, "\t\t\tsubgraph cluster_free%.3d {\n", 0);
	fprintf(dot_file, "\t\t\t\tperipheries = 0\n");
	fprintf(dot_file, "\t\t\t\tlabel = \"\";\n");
	for (size_t i = 0, cnt = 0; i < list->capacity; i++) {
		if (list->elems[i].prev != -1)
			continue;

		if (cnt == 0 && (free = i)) {
			cnt++;
			continue;
		}

		if (cnt++ % GRAPH_DUMP_INDEX == 0) {
			fprintf(dot_file, "\t\t\t}\n\n");
			fprintf(dot_file, "\t\t\tsubgraph cluster_free%.3zu {\n", cnt / GRAPH_DUMP_INDEX);
			fprintf(dot_file, "\t\t\t\tperipheries = 0\n");
			fprintf(dot_file, "\t\t\t\tlabel = \"\";\n");
		}
		else {

			fprintf(dot_file, "\t\t\t\tnode%.3d -> node%.3zu [ weight = 1000; color = %s; ];\n", free, i, BG_COLOR);
		}
		free = i;
	}
	fprintf(dot_file, "\t\t\t}\n\n");

	fprintf(dot_file, "\t\t\tnodeFree -> node%.3d [ weight = 1000; color = %s; ];\n", list->free, FREE_ARROW_COLOR);

	fprintf(dot_file, "\n");

	fprintf(dot_file, "\t\t}\n");

	fprintf(dot_file, "\t}\n");

	fprintf(dot_file, "\n");

	return LIST_NO_ERROR;
}

ListStatusCode ListPrint(List* list) {

	ListStatusCode list_status = LIST_NO_ERROR;

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

	list_status = FindFree(list);

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
