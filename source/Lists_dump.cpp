#include "Lists_dump.hpp"

ListStatusCode ListGraphDump(List* list) {

	FILE* dot_file = fopen("../dump/graph.dot", "w");
	if (!dot_file)
		LIST_ERROR_CHECK(LIST_FILE_OPEN_ERROR);

	fprintf(dot_file, "digraph {\n");

	fprintf(dot_file, "\trankdir = LR;\n");
	fprintf(dot_file, "\tfontname = \"UbuntuMono\";\n");

	ListGraphFreeCluster(list, dot_file);
	ListGraphCaptiveCluster(list, dot_file);

	fprintf(dot_file, "}\n");

	if (fclose(dot_file))
		LIST_ERROR_CHECK(LIST_FILE_CLOSE_ERROR);

	system("dot ../dump/graph.dot -Tpng -o ../dump/graph.png");

	return LIST_NO_ERROR;
}

ListStatusCode ListGraphCaptiveCluster(List* list, FILE* dot_file) {

	const char* BG_COLOR = "\"#FBC4AB\"";
	const char* EDGE_COLOR = "\"#F4978E\"";
	const char* EDGE_BORDER_COLOR = "\"#B55757\"";
	const char* CLUSTER_BORDER_COLOR = "\"#966156\"";
	const char* PREV_ARROWS_COLOR = "\"#228B22\"";
	const char* NEXT_ARROWS_COLOR = "\"#DC143C\"";

	fprintf(dot_file, "\n");

	fprintf(dot_file, "\tsubgraph cluster_captive {\n");
	fprintf(dot_file, "\t\tbgcolor = %s;\n", BG_COLOR);
	fprintf(dot_file, "\t\tcolor = %s;\n", CLUSTER_BORDER_COLOR);
	fprintf(dot_file, "\t\tlabel = <<B>Occupied cells</B>>;\n");
	fprintf(dot_file, "\t\tfontcolor = \"#2F4858\";\n");
	fprintf(dot_file, "\t\tfontsize = \"20px\";\n");

	for (size_t i = 0; i < list->capacity; i++) {
		if (list->elems[i].prev == -1)
			continue;

		fprintf(dot_file, "\t\tnode%.3zu [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; label = \" %.3zu | data = %d | next = %d | prev = %d \" ];\n",
						 i, EDGE_COLOR, EDGE_BORDER_COLOR, i, list->elems[i].data, list->elems[i].next, list->elems[i].prev);
	}

	fprintf(dot_file, "\n");

	fprintf(dot_file, "\t\tnode%.3d -> node%.3d [label = \"0\"; color = \"#9400D3\"; ];\n", 0, 0);

	for (size_t i = 0; i < list->capacity; i++) {
		if (list->elems[i].prev == -1)
			continue;

		fprintf(dot_file, "\t\tnode%.3zu -> node%.3d [ color = %s; ];\n", i, list->elems[i].next, NEXT_ARROWS_COLOR);
	}

	fprintf(dot_file, "\n");

	for (size_t i = 0; i < list->capacity; i++) {
		if (list->elems[i].prev == -1)
			continue;

		fprintf(dot_file, "\t\tnode%.3zu -> node%.3d [ color = %s; ];\n", i, list->elems[i].prev, PREV_ARROWS_COLOR);
	}

	fprintf(dot_file, "\t}\n");

	fprintf(dot_file, "\n");

	return LIST_NO_ERROR;
}

ListStatusCode ListGraphFreeCluster(List* list, FILE* dot_file) {

	const char* BG_COLOR = "\"#DCEAB2\"";
	const char* EDGE_COLOR = "\"#5F9A9D\"";
	const char* EDGE_BORDER_COLOR = "\"#3B6874\"";
	const char* CLUSTER_BORDER_COLOR = "\"#b1c274\"";

	fprintf(dot_file, "\n");

	fprintf(dot_file, "\tsubgraph cluster_free {\n");
	fprintf(dot_file, "\t\tbgcolor = %s;\n", BG_COLOR);
	fprintf(dot_file, "\t\tcolor = %s;\n", CLUSTER_BORDER_COLOR);
	fprintf(dot_file, "\t\tlabel = <<B>Free cells</B>>;\n");
	fprintf(dot_file, "\t\tfontcolor = \"#2F4858\";\n");
	fprintf(dot_file, "\t\tfontsize = \"20px\";\n");

	for (size_t i = 0; i < list->capacity; i++) {
		if (list->elems[i].prev != -1)
			continue;

		fprintf(dot_file, "\t\tnode%.3zu [ shape = Mrecord; style = filled; fillcolor = %s; color = %s; label = \" %.3zu | data = %d | next = %d | prev = %d \" ];\n",
						 i, EDGE_COLOR, EDGE_BORDER_COLOR, i, list->elems[i].data, list->elems[i].next, list->elems[i].prev);
	}

	fprintf(dot_file, "\n");

	Indexes_t free = 0;
	size_t new_line = 0;
	fprintf(dot_file, "\t\tsubgraph cluster_free%.3d {\n", 0);
	fprintf(dot_file, "\t\t\tperipheries = 0\n");
	fprintf(dot_file, "\t\t\tlabel = \"\";\n");
	for (size_t i = 0, cnt = 0; i < list->capacity; i++) {
		if (list->elems[i].prev != -1)
			continue;

		if (cnt == 0 && (free = new_line = i)) {
			cnt++;
			continue;
		}

		if (cnt++ % 10 == 0) {
			fprintf(dot_file, "\t\t}\n\n");
			fprintf(dot_file, "\t\tsubgraph cluster_free%.3zu {\n", cnt / 10);
			fprintf(dot_file, "\t\t\tperipheries = 0\n");
			fprintf(dot_file, "\t\t\tlabel = \"\";\n");
		}
		else
			fprintf(dot_file, "\t\t\tnode%.3d -> node%.3zu [ weight = 1000; color = %s; ];\n", free, i, BG_COLOR);
		free = i;
	}
	fprintf(dot_file, "\t\t}\n\n");

	fprintf(dot_file, "\n");

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
