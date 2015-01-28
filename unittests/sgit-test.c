#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

#include "graph.c"

struct node
{
	int nparent;
	int parents[10];
	char *text;
};

struct node g[] =
{
	{1,{1},"Head"},				/* 0 */
	{1,{2},"Head~1"},			/* 1 */
	{1,{3},"Head~2"},			/* 2 */
	{3,{4,8,9},"Big merge"},	/* 3 */
	{2,{5,7},"Small merge"},	/* 4 */
	{1,{6}, ""},				/* 5 */
	{1,{10},""},				/* 6 */
	{1,{10},"Branch1~1"},		/* 7 */
	{1,{10},"Branch2"},			/* 8 */
	{1,{10},"Branch3"},			/* 9 */
	{1,{11},"Common"},			/* 10 */
	{0,{},"Common~1"}			/* 11 */
};

static node_t get_node(int index, void *userdata)
{
	return (intptr_t)index;
}

static int get_num_parents(node_t node, void *userdata)
{
	return g[(intptr_t)node].nparent;
}

static node_t get_parent(node_t node, int index, void *userdata)
{
	return g[(intptr_t)node].parents[index];
}

static const char *get_text(node_t node, void *userdata)
{
	return g[(intptr_t)node].text;
}

void print_row(cell_state_t *states, int num, void *userdata)
{
	int i;

	for (i = 0; i < num; i++)
	{
		if ((states[i] & TOP_TO_CENTER) == TOP_TO_CENTER) printf(" |");
		else if (states[i] & LEFT_TO_CENTER) printf("\\ ");
		else printf("  ");
	}
	printf("\n");

	for (i = 0; i < num; i++)
	{
		if (states[i] & NODE) printf(" *");
		else if (states[i] & TOP_TO_BOTTOM) printf(" |");
		else printf("  ");
	}
	printf("\n");

	for (i = 0; i < num; i++)
	{
		if (states[i] & BOTTOM_TO_CENTER) printf(" |");
		else if (states[i] & LEFT_TO_CENTER) printf("/ ");
		else printf("  ");
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	graph_callbacks callbacks = {0};

	callbacks.get_node = get_node;
	callbacks.get_num_parents = get_num_parents;
	callbacks.get_parent = get_parent;
	callbacks.get_text = get_text;
	callbacks.print_row = print_row;

	graph_render(sizeof(g)/sizeof(g[0]), &callbacks);

	return 0;
}
