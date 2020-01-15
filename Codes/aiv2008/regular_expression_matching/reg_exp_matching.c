#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define END_STATUS 'e'

typedef struct {
	int *node;
	char **edge;
	//int nodeSize;
	//int edgeSize;
	int size;
	int capacity;
	int startState;
	int endState;
} Graph;

void addState(Graph **g) {
	if(g == NULL) return ;
	if(*g == NULL) {
		*g = (Graph*)calloc(1, sizeof(Graph));
		int capacity = 10;
		(*g)->capacity = capacity;
		(*g)->node = (int*)calloc(capacity, sizeof(int));
		int i;
		for(i=0;i<capacity;i++)
			*((*g)->node+i) = -1;
		(*g)->edge = (char**)calloc(capacity, sizeof(char*));
		(*g)->startState = 0;
	}
	if((*g)->size + 1 > (*g)->capacity) {
		int capacity = (*g)->capacity + (*g)->capacity/2;
		(*g)->capacity = capacity;
		int *node = (int*)calloc(capacity, sizeof(int));
		memcpy(node, (*g)->node, sizeof(int)*(*g)->capacity);
		free((*g)->node);
		(*g)->node = node;
		node = NULL;
		char **edges = (char**)calloc(capacity, sizeof(char*));
		int i;
		for(i=0;i<(*g)->capacity;i++) {
			char *edge = *((*g)->edge+i);
			if(edge != NULL) {
				*(edges+i) = (char*)calloc(capacity, sizeof(char));
				memcpy(*(edges+i), edge, sizeof(char)*(*g)->capacity);
			}
		}
		free((*g)->edge);
		(*g)->edge = edges;
	}
	int size = (*g)->size;
	*((*g)->node+size) = size;
	(*g)->endState = size;
	(*g)->size++;
}

void addEdge(Graph *g,char data, int startIndex, int endIndex) {
	if(g == NULL || g->node == NULL || startIndex >= g->size || endIndex >= g->size) return;
	char *edge = *(g->edge+startIndex);
	if(edge == NULL) {
		edge = (char*)calloc(g->capacity, sizeof(char));
		*(g->edge+startIndex) = edge;
	}
	*(edge+endIndex) = data;
}

void addKleenStarNFA(Graph **g, char data) {
	if(g == NULL) return;
	int state = *g == NULL ? 0 : (*g)->endState;
	int size = 4;
	int i;
	for(i=0;i<size;i++) {
		addState(g);	
	}
	if(*g != NULL) {
		addEdge(*g, 'E', state, state+1);
	}
	addEdge(*g, 'E', state+1, state+2);
	addEdge(*g, 'E', state+1, state+4);
	addEdge(*g, 'E', state+3, state+4);
	addEdge(*g, 'E', state+3, state+2);
	addEdge(*g, data, state+2, state+3);
}

void addStringNFA(Graph **g, char data) {
	if(g == NULL) return;
	int state = *g == NULL ? 0 : (*g)->endState;
	int size = 3;
	int i;
	for(i=0;i<size;i++) {
		addState(g);
	}
	if(*g != NULL) {
		addEdge(*g, 'E', state, state+1);
	}
	addEdge(*g, data, state+1, state+2);
	addEdge(*g, 'E', state+2, state+3);
}

int main(void) {
	char *s = "a*b";
	char *p = s;
	Graph *g = NULL;
	while(*p != '\0') {
		if(*(p+1) == '*') {
			addKleenStarNFA(&g, *p);
			p+=2;
		} else {
			addStringNFA(&g, *p);
			p++;
		}
	}

	int *node = g->node;
	char **edges = g->edge;
	int size = g->size;
	int i;
	for(i=0;i<size;i++) {
		printf("%d,", *(node+i));
	}
	printf("\n");
	char *edge = NULL;
	for(i=0;i<size;i++) {
		edge = *(edges+i);
		if(edge == NULL) {
			printf("0");
		}else {
			int j;
			for(j=0;j<size;j++) {
				printf("%c,", *(edge+j));
			}
		}
		printf("\n");
	}
	return 0;
}
