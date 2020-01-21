#ifndef REG_EXP_MATCHING_H_INCLUDED
#define REG_EXP_MATCHING_H_INCLUDED

typedef struct {
	char key;
	int val;
	struct Entry* next;
} Entry;

typedef struct {
	char key;
	int val;
} Entity;

typedef struct {
	struct Entry **entry;
	struct Array *entity;
	int size;
} HashMap;

typedef struct {
	char val;
	struct Element *next;
} Element;

typedef struct {
	struct Element *top;
	struct Element *bottom;
} Queue;

typedef struct {
	char *val;
	int size;
	int capacity;
} Array;

typedef struct {
	int *node;
	char **edge;
	struct HashMap *weight;
	int size;
	int capacity;
	int startState;
	int endState;
} Graph;

typedef struct {
	struct HashMap *colTitle;
	struct Array *rowTitle;
	int ***states;
} NFAModel;


void swap_1(int *x, int *y);

int hash(char c);

void put(HashMap **map, char key, int val);

int get(HashMap *map, char key);

Entry *getEntries(HashMap *map);

void push(Queue **queue, char val);

void pop(Queue **queue);

Element *bottom(Queue *queue);

void iterateQueue(Queue *queue);

void add(Array **array, char *val, int len);

void addByIndex(Array **array, char *val, int len, int index);

char *getByIndex(Array *array, int index, int len);

int getSize(Array *array);

void iterateArray(Array *array, int len);

int myPartition(int *array, int start, int end);

void myQuicksort(int *array, int start, int end);

int myRandomizedPartition(int *array, int start, int end);

void myRandomizedQuicksort(int *array, int start, int end);

void addState(Graph **g);

void addEdge(Graph *g, char data, int startIndex, int endIndex);

void addKleenStarNFA(Graph **g, char data);

void addStringNFA(Graph **g, char data);

Array *delta(Graph *g, int state, char key);




