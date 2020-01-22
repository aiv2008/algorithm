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

typedef struct {
	char key;
	int val;
} Entity;

//struct of the hashmap
typedef struct {
	struct Entry **entry;
//	struct Array *entity;
	struct Array *keys;
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
	struct HashMap *weight;
	int size;
	int capacity;
	int startState;
	int endState;
} Graph;

typedef struct {
	struct HashMap *colTitle;
	struct Array *rowTitle;
	struct Array ***states;
//	int ***states;
} NFAModel;

void swap_1(int* x, int* y)
{
    	*x = *x^*y;
	*y = *x^*y;//(*x^*y)^*y=*x(Ô­Öµ)
	*x = *x^*y;//(*x^*y)^((*x^*y)^*y)=*y£šÔ­Öµ£©
}

char *getByIndex(Array *array, int index, int len) {
	if(array == NULL) return -1;
	if(index >= array->size) {
		printf("index is out of bound!\n");
		return -1;
	}
	return array->val+len*index;	
}

//return the hashcode of the character
int hash(char c) {
	return ((int)c) % MAP_SIZE;
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

void put(HashMap **map, char key, int val) {
	if(map == NULL) { return ;}
	if(*map == NULL) {
		*map = (HashMap*)calloc(1, sizeof(HashMap));
		(*map)->size = 0;
		(*map)->entry = (Entry**)calloc(MAP_SIZE, sizeof(Entry*));
	}
	int hashCode = hash(key);
	Entry *entry = *((*map)->entry + hashCode);
	if(entry == NULL) {
		*((*map)->entry + hashCode) = (Entry*)calloc(1, sizeof(Entry));
		entry = *((*map)->entry + hashCode);
		entry->key = key;
		entry->val = val;
		add(&(*map)->keys, &key, sizeof(char));
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
			add(&(*map)->keys, &key, sizeof(char));
			(*map)->size = (*map)->size + 1;
		}
	}
}

Array *getKeys(HashMap *map) {
	if(map == NULL) return NULL;
	return map->keys;
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
	} 
	if((*array)->size + 1 > (*array)->capacity) {
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

//add the element in the position of index
void addByIndex(Array **array, char *val, int len, int index) {
	if(array == NULL) return ;
	if(*array == NULL) {
		*array = (Array*)calloc(1, sizeof(Array));
		(*array)->capacity = ARRAY_SIZE;
		char *a = (char*)calloc(ARRAY_SIZE, len);
		(*array)->val = a;
		a = NULL;		
	}
	if(index >= (*array)->size) return; 
	if((*array)->size + 1 > (*array)->capacity) {
		(*array)->capacity = (*array)->capacity + ((*array)->capacity) / 2;
		char *a = (char*)calloc((*array)->capacity, len);
		memcpy(a, (*array)->val, len*(*array)->size);
		int size = (*array)->size;
		(*array)->val = NULL;
		(*array)->val = a;
		a = NULL;
	}
	char *value = (*array)->val;
	int size = (*array)->size;
	int i;
	for(i=size-1;i>=index;i--) {
		memcpy(value+len*(i+1), value+len*i, len);
	}
	//memcpy(value+len*size, val, len);
	memcpy(value+len*index, val, len);
	(*array)->size = size + 1;
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
		int j;
		for(j=0;j<capacity;j++) {
			printf("node=%d,", *((*g)->node+j));
		}
		memcpy(node, (*g)->node, sizeof(int)*capacity);
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
	//HashMap *weight = g->weight;
//	if(g->weight == NULL) printf("addEdge: weight is null\n");
//	int t = get(g->weight, data);
	//printf("t=%d\n", t);
	if(get(g->weight, data) == -1) {
	//	printf("%c addEdge enter here\n", data);
		put(&g->weight, data, g->weight == NULL ? 0 : ((HashMap*)(g->weight))->size);
	}
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
	Array *keys = getKeys((*g)->weight);
	printf("weight size: %d", keys->size);
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

Array* delta(Graph *g, int state, char key) {
	if(g == NULL ||  state >= g->size) return NULL;
	Array *array = NULL;
	char *edge = *(g->edge+state);
	int size = g->size;
	int i;
	for(i=0;i<size;i++) {
		if(edge+i==NULL) continue;
		char c = *(edge+i);
		if(c == key) {
			int insertValue = i+1;
			if(array != NULL) {
				int j;
				for(j=0;j<array->size;j++) {
					int *value = (int*)getByIndex(array, j, sizeof(int));
					//printf("*value=%d, i=%d\n", *value, i);
					if(*value == insertValue) break;
					else if(*value > insertValue) 
					{
						addByIndex(&array, &insertValue, sizeof(int), j);
						break;
					}
				}
				if(j == array->size) add(&array, &insertValue, sizeof(int));
			} else {
				add(&array, &insertValue, sizeof(int));
			}
		}
	}
	return array;
}

NFAModel *convertToNFA(Graph *g) {
	if(g == NULL) {
		printf("graph is null;\n");
		return NULL;
	}
	HashMap *weight = g->weight;
	if(weight == NULL) {
		printf("weight is null\n");
		return NULL;
	}
	int *node = g->node;
	int size = g->size;
	NFAModel *model = (NFAModel*)calloc(1, sizeof(NFAModel));
	model->colTitle = weight;
	Array *keys = getKeys(weight);
	//printf("size=%d,", size);
	//printf("keys->size=%d\n", keys->size);
	int i;
	for(i=0;i<size;i++) {
		add(&model->rowTitle, node+i, sizeof(int));	
		int j;
		for(j=0;j<keys->size;j++) {
			char *c = getByIndex(keys, j, sizeof(char));
			int value = get(weight, *c);
			Array *array = delta(g, *(node+i), *c);
			if(array != NULL) {
				if(model->states == NULL) {
					model->states = (Array***)calloc(size, sizeof(Array**));
				}
				if(*(model->states+*(node+i)) == NULL) {
					*(model->states+*(node+i)) = (Array**)calloc(keys->size, sizeof(Array*));
				}
				*(*(model->states+*(node+i))+value) = array;
				printf("%c: {", *c);
				int k;
				for(k=0;k<array->size;k++) {
					int *value = (int*)getByIndex(array, k, sizeof(int));
					printf("%d,", *value );
				}
				printf("}\n");
			}
		}	
	}
	return model;
}

void testDelta() {
	char *s = "a*b*";
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

	NFAModel *model = convertToNFA(g);
	if(model == NULL) printf("NFAModel is null\n");
	HashMap *colTitle = model->colTitle;
	Array *rowTitle = model->rowTitle;
	Array ***states = model->states;
	Array *keys = getKeys(model);
	//int i;
	printf("---colTitle begin---\n");
	for(i=0;i<keys->size;i++) {
		char *key = getByIndex(keys, i, sizeof(char));
		int value = get(keys, *key);
		printf("key=%c,value=%d\n", *key, value);		
	}
	printf("---colTitle end---\n");

	printf("---rowTitle begin---\n");
	for(i=0;i<rowTitle->size;i++) {
		int *state = (int*)getByIndex(rowTitle, i, sizeof(int));
		printf("%d,", *state);
	}
	printf("---rowTitle end---\n");

	printf("---value matrix begin---\n");
	for(i=0;i<rowTitle->size;i++) {
		Array **a = *(states+i);
		int j;
		for(j=0;j<keys->size;j++) {
			Array *b = *(a+j);
			if(b != NULL) {
				int k;
				printf("{");
				for(k=0;k<b->size;k++) {
					int *v = (int*)getByIndex(b, k, sizeof(int));
					printf("%d,", *v);	
				}
				printf("}");
			}
		} 
	}
	printf("---value matrix end---\n");
/**
	HashMap *weight = g->weight;
	if(weight == NULL) {
		printf("weight is null\n");
		return;
	}
	Array *keys = getKeys(weight);
	printf("size=%d,", size);
	printf("keys->size=%d\n", keys->size);
	for(i=0;i<size;i++) {
		int j;
		for(j=0;j<keys->size;j++) {
			char *c = getByIndex(keys, j, sizeof(char));
			int value = get(weight, *c);
			Array *array = delta(g, *(node+i), *c);
			if(array != NULL) {
				printf("%c: {", *c);
				int k;
				for(k=0;k<array->size;k++) {
					int *value = (int*)getByIndex(array, k, sizeof(int));
					printf("%d,", *value );
				}
				printf("}\n");
			}
		}	
	}
**/
}

void testMap() {
	char a[] = {'a','b','c','a'};
	HashMap *map = NULL;
	int size = sizeof(a)/sizeof(a[0]);
	int i;
	for(i=0;i<size;i++) {
		int val = get(map, a[i]);
		put(&map, a[i], val == -1 ? 1: (val+1));
	}
	printf("\n");
	Array *keys = getKeys(map);
	for(i=0;i<keys->size;i++) {
		char *key = getByIndex(keys, i, sizeof(char));
		int value = get(map, *key);
		printf("key=%c, value=%d\n", *key, value);
	}
}

void testArray() {
	int a[] = {2,3,5,6,7,8,9,10};
	Array *array = NULL;
	int size = sizeof(a)/sizeof(a[0]);
	int i;
	for(i=0;i<size;i++) {
		add(&array, &a[i], sizeof(int));
	}
	printf("array size is %d\n", array->size);
	for(i=0;i<array->size;i++) {
		int *value = (int*)getByIndex(array, i, sizeof(int));
		printf("%d,", *value);
	}
	int insertedValue = 4;
	addByIndex(&array, &insertedValue, sizeof(int), 10);
	printf("\n");
	for(i=0;i<array->size;i++) {
		int *value = (int*)getByIndex(array, i, sizeof(int));
		printf("%d,", *value);
	}
	printf("\n");
}

int main(void) {

//	testMap();

	testDelta();

//	testArray();

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
