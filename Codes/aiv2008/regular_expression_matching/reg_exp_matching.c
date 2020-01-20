#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define MAP_SIZE 7
#define ARRAY_SIZE 10

//struct of the element of the hashmap
typedef struct {
	char key;
	int val;
	struct Entry* next;
} Entry;

//struct of the hashmap
typedef struct {
	Entry **entry;
	int size;
} HashMap;

//struct of the element of the queue
typedef struct {
	char val;
	struct Element *next;
} Element;

//struct of the queue
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
//	int *key;
	int size;
	int capacity;
	int startState;
	int endState;
} Graph;

typedef struct {
	struct HashMap *colTitile;
	struct Array *rowTitle;
	int ***states;
} NFAModel;

void swap_1(int* x, int* y)
{
    	*x = *x^*y;
	*y = *x^*y;//(*x^*y)^*y=*x(Ô­Öµ)
	*x = *x^*y;//(*x^*y)^((*x^*y)^*y)=*y£šÔ­Öµ£©
}

//return the hashcode of the character
int hash(char c) {
	return ((int)c) % MAP_SIZE;
}

void put(HashMap **map, char key, int val) {
	if(map == NULL) { return ;}
	if(*map == NULL) {
		*map = (HashMap*)calloc(1, sizeof(HashMap));
		(*map)->size = 0;
		(*map)->entry = (Entry**)calloc(MAP_SIZE, sizeof(Entry*));
	}
	//printf("aaaa\n");
	int hashCode = hash(key);
	Entry *entry = *((*map)->entry + hashCode);
	if(entry == NULL) {
		*((*map)->entry + hashCode) = (Entry*)calloc(1, sizeof(Entry));
		entry = *((*map)->entry + hashCode);
		//entry = (Entry*)calloc(1, sizeof(Entry));
		entry->key = key;
		entry->val = val;
		(*map)->size = (*map)->size + 1;
	} else {
		Entry *pEntry = entry;
		while(pEntry->next != NULL) {
			if(pEntry->key == key) {
				printf("11key=%c, val=%d\n", key, val);
				pEntry->val = val;
				break;
			}
			pEntry = pEntry->next;
		}
		//最后一个节点
		if(pEntry->key == key) {
			pEntry->val = val;
		} else {
			Entry *newEntry = (Entry*)calloc(1, sizeof(Entry));
			newEntry->key = key;
			newEntry->val = val;
			pEntry->next = newEntry;
			(*map)->size = (*map)->size + 1;
		}
	}
}

int get(HashMap *map, char key) {
	if(map == NULL) return -1;
	int val = -1;
	int hashCode = hash(key);
//	Entry entry = (map->entry)[hashCode];
	Entry *entry = *(map->entry + hashCode);
	if(entry == NULL) return -1;
	//Entry *pEntry = &entry;
	Entry *pEntry = entry;
	while(pEntry != NULL) {
		if(pEntry->key == key) {
			val = pEntry->val;
			break;
		}
		pEntry = pEntry->next;
	}
	return val;
}

Entry *getEntries(HashMap *map) {
	if(map == NULL) return NULL;
	Entry *result = (Entry*)calloc(map->size, sizeof(Entry));
	int mapSize = MAP_SIZE;
	int i;
	int j=0;
	for(i=0;i<mapSize;i++) {
		if(*(map->entry+i) != NULL) {
			Entry *entry = *(map->entry+i);
			Entry *p = entry;
			while(p != NULL) {
				//memcpy(result+j, p, sizeof(Entry));
				(result+j)->key = p->key;
				(result+j)->val = p->val;
				p = p->next;
				j++;
			}
		}
	}
	return result;
}

void push(Queue **queue, char val) {
	if(queue == NULL) return ;
	if(*queue == NULL) {
		*queue = (Queue*)calloc(1, sizeof(Queue));
	}
	Element *top = (Element*)calloc(1, sizeof(Element));
	top->val = val;
	top->next = NULL;
	if((*queue)->top == NULL) {
//		Element *top = (Element*)calloc(1, sizeof(Element));
		(*queue)->top = top;
		(*queue)->bottom = top;
	} else {
		((Element*)((*queue)->bottom))->next = top;
		(*queue)->bottom = top;
	}
	top = NULL;
}

void pop(Queue **queue) {
	if(queue == NULL || *queue == NULL ) return ;
	Element *top = (*queue)->top;
	(*queue)->top = top->next;
	free(top);
	top = NULL;
	if((*queue)->top == NULL) {
		free(*queue);
		*queue = NULL;
	}
}

struct Element *top(Queue *queue) {
	if(queue == NULL) return NULL;
	return queue->top;	
}

Element *bottom(Queue *queue) {
	if(queue == NULL) return NULL;
	return queue->bottom;
}

void iterateQueue(Queue *queue) {
	Element *p = queue->top;
	while(p != NULL) {
		printf("%c,", p->val);
		p = p->next;
	}
	printf("\n");
}

void add(Array **array, char *val, int len) {
	if(array == NULL) return ;
	if(*array == NULL) {
		*array = (Array*)calloc(1, sizeof(Array));
		(*array)->capacity = ARRAY_SIZE;
		char *a = (char*)calloc(ARRAY_SIZE, len);
		(*array)->val = a;
		a = NULL;		
	} else if((*array)->size + 1 > (*array)->capacity) {
		(*array)->capacity = (*array)->capacity + ((*array)->capacity) / 2;
		char *a = (char*)calloc((*array)->capacity, len);
		//printf("size=%d\n", (*array)->size);
		memcpy(a, (*array)->val, len*(*array)->size);
		int size = (*array)->size;
		(*array)->val = NULL;
		(*array)->val = a;
		a = NULL;
	}
	char *value = (*array)->val;
	int size = (*array)->size;
	memcpy(value+len*size, val, len);
	(*array)->size = size + 1;
}

char *getByIndex(Array *array, int index, int len) {
	if(array == NULL) return -1;
	if(index >= array->size) {
		printf("index is out of bound!\n");
		return -1;
	}
	return array->val+len*index;	
}

int getSize(Array *array) {
	if(array == NULL) return 0;
	return array->size;
}

void iterateArray(Array *array, int len) {
	if(array == NULL) return;
	int size = array->size;
	int *val = array->val;
	int i;
	for(i=0;i<size;i++) {
		printf("%d,", *(val+i));
	}
	printf("\n");
}


int myPartition(int* array, int start, int end)
{
	if(array == '\0')
	{
		printf("array cannot be null\n");
		return -1;
	}
	if(start < 0)
	{
		printf("index must begin with 1\n");
		return -1;
	}
	int i = start - 1;
	int j = start;
	if(j < end)
	{
		while(j < end)
		{
			if(*(array+j) <= *(array+end))
			{
				i++;
				if(i != j)
				{
					swap_1(array+j, array+i);
				}
			}
			j++;
		}
		if(i+1 != end)
		{
			swap_1(array+i+1, array+end);
			return i+1;
		}
		else
		{
			return end;
		}

	}
	return -1;
}

void myQuicksort(int* array, int start, int end)
{
	if(array == '\0')
	{
		printf("array cannot be null\n");
		return ;
	}
	if(start < end)
	{
		int partitionIndex = myPartition(array, start, end);
		if(partitionIndex < 0)
		{
		    printf("partitionIndex must larger than 0\n");
		    return ;
		}
		myQuicksort(array, start, partitionIndex-1);
		myQuicksort(array, partitionIndex+1, end);
	}
}

int myRandomizedPartition(int* array, int start, int end)
{
	if(start < 0)
	{
		printf("quicksort myRandomizedPartition: index must begin with 1\n");
		return -1;
	}
	if(start > end)
	{
		printf("quicksort myRandomizedPartition: start must smaller than end\n");
		return -1;
	}
	srand(time(0));
    	int randIndex = start + rand()%(end - start);
	if(randIndex != end)swap_1(array+randIndex, array+end);
	return myPartition(array, start, end);
}

void myRandomizedQuicksort(int* array, int start, int end)
{
	if(array == '\0')
	{
		printf("quicksort myRandomizedQuicksort: array cannot be null\n");
		return ;
	}
	if(start < end)
	{
		int partitionIndex = myRandomizedPartition(array, start, end);
		if(partitionIndex < 0)
		{
		    printf("quicksort myRandomizedQuicksort: partitionIndex must larger than 0\n");
		    return ;
		}
		myRandomizedQuicksort(array, start, partitionIndex-1);
		myRandomizedQuicksort(array, partitionIndex+1, end);
	}
}

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
		//int capacity = (*g)->capacity + (*g)->capacity/2;
		int capacity = (*g)->capacity;
		(*g)->capacity = capacity + capacity/2;
		int *node = (int*)calloc((*g)->capacity, sizeof(int));
		printf("capacity=%d, (*g)->capacity=%d\n", capacity, (*g)->capacity);
		int j;
		for(j=0;j<capacity;j++) {
			printf("node=%d,", *((*g)->node+j));
		}
		printf("\naaaaq\n");
		memcpy(node, (*g)->node, sizeof(int)*capacity);
		printf("bbbbb\n");
		free((*g)->node);
		(*g)->node = node;
		node = NULL;
		char **edges = (char**)calloc((*g)->capacity, sizeof(char*));
		int i;
		for(i=0;i<capacity;i++) {
			char *edge = *((*g)->edge+i);
			if(edge != NULL) {
				*(edges+i) = (char*)calloc((*g)->capacity, sizeof(char));
				memcpy(*(edges+i), edge, sizeof(char)*capacity);
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
	int state = *g == NULL ? -1 : (*g)->endState;
	if(state >= 0) {
		addState(g);
		state = (*g)->endState;
		addEdge(*g, 'E', state, state);
	}
	int size = 3;
	int i;
	for(i=0;i<size;i++) {
		addState(g);	
	}
	addEdge(*g, 'E', state+1, state+1);
	addEdge(*g, 'E', state+1, state+3);
	addEdge(*g, 'E', state+3, state+3);
	addEdge(*g, 'E', state+3, state+1);
	addEdge(*g, data, state+2, state+2);
}

void addStringNFA(Graph **g, char data) {
	if(g == NULL) return;
	int state = *g == NULL ? -1 : (*g)->endState;
	printf("endState1=%d\n", state);
	if(state >= 0) {
		addState(g);
		state = (*g)->endState;
		printf("endState2=%d\n", state);
		addEdge(*g, 'E', state, state);
	}
	int size = 2;
	int i;
	for(i=0;i<size;i++) {
		addState(g);
	}
	addEdge(*g, data, state+1, state+1);
	addEdge(*g, 'E', state+2, state+2);
}

void delta(Graph *g, int state, char key, int **result, int *resultSize) {
	if(g == NULL || result == NULL || resultSize == NULL) 
	{
		printf("g is null\n");
		return NULL;
	}
	printf("state=%d\n", state);
	char *edge = *(g->edge+state);
	if(edge == NULL) return NULL;
	//int *result = NULL;
	Array *array = NULL;
	int size = g->size;
	//printf("size=%d\n", size);
	int i;
	for(i=0;i<size;i++) {
		if( *(edge+i) == key) {
			add(&array, &i, sizeof(int));
		}
	}	

	//array sorted
	if(array != NULL) {
		//int *a = (int*)calloc(array->size, sizeof(int));
		*result = (int *)calloc(array->size, sizeof(int));
		memcpy(*result, array->val, array->size*sizeof(int));
		free(array->val);
		array->val = NULL;
		free(array);
		array = NULL;
		myRandomizedQuicksort(*result, 0, size-1);
		*resultSize = size;
	}
}

void testDelta() {
	char *s = "a*";
	char *p = s;
	Graph *g = NULL;
	while(*p != '\0') {
		if(*(p+1) == '*') {
			addKleenStarNFA(&g, *p);
			p+=2;
		} else if(*(p+1) == '.') {
			printf("*p=%c, *(p+1)=%c\n", *p, *(p+1));
			addStringNFA(&g, *p);
			addStringNFA(&g, *p);
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

	//int i;
	for(i=0;i<size;i++) {
		p = s;
		int *array = NULL;
		int arraySize = 0;
		while(*p != '\0') {
			if(*p == '*' || *p == '.') {
				p++;
				continue;
			}
			delta(g, *(node+i), *p, &array, &arraySize);
			//printf("arraySize=%d\n", arraySize);
			printf("char=%c,", *p);
			if(array != NULL) {
				int j;
				for(j=0;j<arraySize;j++) {
					printf("states=%d, ", *(array+j));
				}
				printf("\n");
			}
			p++;
		}
		
	}
}

void testMap() {
	char a[] = {'a','b','c','a'};
	HashMap *map = NULL;
	int size = sizeof(a)/sizeof(a[0]);
	int i;
	for(i=0;i<size;i++) {
		int val = get(map, a[i]);
		printf("%d,", val == -1 ? 1 : (val+1) );
		put(&map, a[i], val == -1 ? 1: (val+1));
	}
	printf("\n");
	for(i=0;i<size;i++) {
		printf("%d,", get(map, a[i]));
	}
	printf("\n");
	printf("%d\n", map->size);
	Entry *entry = getEntries(map);
	for(i=0;i<map->size;i++) {
		char key = (entry+i)->key;
		int val = (entry+i)->val;
		printf("key=%c, val=%d\n", key, val);
	}
}

int main(void) {

//	testMap();

	testDelta();

/**
	char *s = "a*b*a.";
	char *p = s;
	Graph *g = NULL;
	while(*p != '\0') {
		if(*(p+1) == '*') {
			addKleenStarNFA(&g, *p);
			p+=2;
		} else if(*(p+1) == '.') {
			printf("*p=%c, *(p+1)=%c\n", *p, *(p+1));
			addStringNFA(&g, *p);
			addStringNFA(&g, *p);
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
		if(edge == NULL ) {
			printf("0");
		}else {
			int j;
			for(j=0;j<size;j++) {
				char charVal = *(edge+j);
				int intVal = (int)charVal;
				printf("%c(%d),",charVal, intVal);
			}
		}
		printf("\n");
	}
**/

	return 0;
}
