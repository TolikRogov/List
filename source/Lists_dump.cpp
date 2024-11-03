#include "Lists_dump.hpp"

ListStatusCode ListGraphDump(List* list) {

	FILE* dot_file = fopen("../dump/graph.dot", "w");
	if (!dot_file)
		LIST_ERROR_CHECK(LIST_FILE_OPEN_ERROR);

	fprintf(dot_file, "digraph {\n");

	fprintf(dot_file, "\trankdir = LR;\n");

	ListGraphFreeCluster(list, dot_file);
	ListGraphCaptiveCluster(list, dot_file);

	fprintf(dot_file, "}\n");

	if (fclose(dot_file))
		LIST_ERROR_CHECK(LIST_FILE_CLOSE_ERROR);

	system("dot ../dump/graph.dot -Tpng -o ../dump/graph.png");

	return LIST_NO_ERROR;
}

ListStatusCode ListGraphCaptiveCluster(List* list, FILE* dot_file) {

	fprintf(dot_file, "\n");

	fprintf(dot_file, "\tsubgraph cluster_captive {\n");

	for (size_t i = 0; i < list->capacity; i++) {
		if (list->elems[i].prev == -1)
			continue;

		fprintf(dot_file, "\t\tnode%.3zu [ shape = Mrecord; label = \" %.3zu | data = %d | next = %d | prev = %d \" ];\n",
						 i, i, list->elems[i].data, list->elems[i].next, list->elems[i].prev);
	}

	fprintf(dot_file, "\n");

	fprintf(dot_file, "\t\tnode%.3d -> node%.3d [label = \"0\"];\n", 0, 0);

	for (size_t i = 0; i < list->capacity; i++) {
		if (list->elems[i].prev == -1)
			continue;

		fprintf(dot_file, "\t\tnode%.3zu -> node%.3d [ color = red; ];\n", i, list->elems[i].next);
	}

	fprintf(dot_file, "\n");

	for (size_t i = 0; i < list->capacity; i++) {
		if (list->elems[i].prev == -1)
			continue;

		fprintf(dot_file, "\t\tnode%.3zu -> node%.3d [ color = blue; ];\n", i, list->elems[i].prev);
	}

	fprintf(dot_file, "\t}\n");

	fprintf(dot_file, "\n");

	return LIST_NO_ERROR;
}

ListStatusCode ListGraphFreeCluster(List* list, FILE* dot_file) {

	fprintf(dot_file, "\n");

	fprintf(dot_file, "\tsubgraph cluster_free {\n");

	for (size_t i = 0; i < list->capacity; i++) {
		if (list->elems[i].prev != -1)
			continue;

		fprintf(dot_file, "\t\tnode%.3zu [ shape = Mrecord; label = \" %.3zu | data = %d | next = %d | prev = %d \" ];\n",
						 i, i, list->elems[i].data, list->elems[i].next, list->elems[i].prev);
	}

	fprintf(dot_file, "\n");

	Indexes_t free = 0;
	for (size_t i = 0, j = 0; i < list->capacity; i++) {
		if (list->elems[i].prev != -1)
			continue;

		if (j++ == 0 && (free = i))
			continue;

		fprintf(dot_file, "\t\tnode%.3d -> node%.3zu [ weight = 1000; color = white; ];\n", free, i);
		free = i;
	}

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
