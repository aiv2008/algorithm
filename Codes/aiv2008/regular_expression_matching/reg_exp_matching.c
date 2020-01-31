#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define MAP_SIZE 7
#define ARRAY_SIZE 10

#define bool int
#define true 1
#define false 0

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
	char *val;
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
	int endState;
//	int ***states;
} NFAModel;

void swap_1(int* x, int* y)
{
    *x = *x^*y;
	*y = *x^*y;//(*x^*y)^*y=*x(Ô­Öµ)
	*x = *x^*y;//(*x^*y)^((*x^*y)^*y)=*y£šÔ­Öµ£©
}

char *getByIndex(Array *array, int index, int len) {
	if(array == NULL) return NULL;
	if(index >= array->size) {
		printf("index is out of bound!\n");
		return -1;
	}
	return array->val+len*index;	
}

char *getLast(Array *array, int len) {
	if(array == NULL) return NULL;
	return array->val+len*(array->size-1);
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

void push(Queue **queue, void *val) {
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

Element *top(Queue *queue) {
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
//		printf("%c,", p->val);
		Array *array = (Array*)(p->val);
		int i;
		for(i=0;i<getSize(array);i++) {
			int *value = (int*)getByIndex(array, i, sizeof(int));
			printf("%d,", *value);
		}
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
	memcpy(value+len*index, val, len);
	(*array)->size = size + 1;
}

int getSize(Array *array) {
	if(array == NULL) return 0;
	return array->size;
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
	printf("g end state: %d\n", (*g)->endState);
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
	if(get(g->weight, data) == -1) {
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
	(*g)->endState++;
//	Array *keys = getKeys((*g)->weight);
//	printf("weight size: %d", keys->size);
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
	(*g)->endState++;
}

void addDocNFA(Graph **g) {
	if(g == NULL) return;
	int state = *g == NULL ? -1 : (*g)->endState;
	if(state >= 0) {
		addState(g);
		state = (*g)->endState;
		printf("endState2=%d\n", state);
		addEdge(*g, 'E', state, state);
	}
	int size = 55;
	int i;
	for(i=0;i<size;i++) {
		addState(g);
	}
	addEdge(*g, 'E', state+1, state+1);
	int edgeCount = 2;
	for(i=0;i<26;i++) {
		printf("edgeCount=%d\n", edgeCount);
		addEdge(*g, 'E', state+2, state+(edgeCount++));
		addEdge(*g, i+97, state+(edgeCount++), state+edgeCount);
		addEdge(*g, 'E', state+edgeCount, state+54);
	}
	addEdge(*g, 'E', state+55, state+55);
	(*g)->endState++;
}

void addDocStarNFA(Graph **g) {
	if(g == NULL) return;
	int state = *g == NULL ? -1 : (*g)->endState;
	if(state >= 0) {
		addState(g);
		state = (*g)->endState;
		printf("endState2=%d\n", state);
		addEdge(*g, 'E', state, state);
	}
	int size = 55;
	int i;
	for(i=0;i<size;i++) {
		addState(g);
	}
	addEdge(*g, 'E', state+1, state+1);
	int edgeCount = 2;
	for(i=0;i<26;i++) {
		printf("edgeCount=%d\n", edgeCount);
		addEdge(*g, 'E', state+2, state+(edgeCount++));
		addEdge(*g, i+97, state+(edgeCount++), state+edgeCount);
		addEdge(*g, 'E', state+edgeCount, state+edgeCount-2);
		addEdge(*g, 'E', state+2, state+54);
		addEdge(*g, 'E', state+edgeCount, state+54);
	}
	addEdge(*g, 'E', state+55, state+55);
	(*g)->endState++;
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

void mergeSort(Array **dest, Array *src) {
	if(dest == NULL) return;
	if((*dest==NULL || !getSize(*dest)) && (src==NULL || !getSize(src))) return;
	else if(*dest == NULL || !getSize(*dest)) {
		int *value = NULL;
		int i;
		for(i=0;i<getSize(src);i++) {
			value = (int*)getByIndex(src, i, sizeof(int));
			add(dest, value, sizeof(int));
		}
	} else if(src == NULL || !getSize(src)) return;
	int i=0;
	int j=0;
	while(i<getSize(*dest) && j<getSize(src)) {
		int *aVal = (int*)getByIndex(*dest, i, sizeof(int));
		int *bVal = (int*)getByIndex(src, j, sizeof(int));
		if(*aVal == *bVal) {
			i++;
			j++;
		} else if(*aVal < *bVal) {
			i++;
		} else {
			addByIndex(dest, bVal, sizeof(int), i);
			j++;
		}
	}
	for(;j<getSize(src);j++) {
		int *bVal = (int*)getByIndex(src, j, sizeof(int));
		add(dest, bVal, sizeof(int));
	}
}


Array *delta2(Array ***states, int state, HashMap *cMap, char c) {
	printf("key=%c\n", c);
	if(states == NULL || state<0 || cMap == NULL) return NULL;
	Array **a = *(states+state);
	int colVal = get(cMap, c);
	if(a != NULL && colVal >= 0) {
		return *(a+colVal);
	}
	return NULL;
}

Array *eclosure(Array ***states, int state, HashMap *cMap) {
	return delta2(states, state, cMap, 'E');
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
	printf("test in convertToNFA: \n");
	for(i=0;i<keys->size;i++) {
		char *cTest = getByIndex(keys, i, sizeof(char));
		printf("%c,", *cTest);
	}
	printf("\nend\n");
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
	model->endState = g->endState;
	return model;
}
void iterateArray(Array *a) {
	printf("---enter iterate array ----\n");
	int i;
	for(i=0;i<getSize(a);i++) {
		int *val = (int*)getByIndex(a, i, sizeof(int));
		printf("%d,", *val);
	}
	printf("\n");
}
void eclosureRecursion(Array ***states, Array **initStates, HashMap *cMap, int rowSize) {
	if(states == NULL || initStates == NULL || *initStates == NULL || cMap == NULL) return;
	Queue *q = NULL;
//	Array *a = *initStates;
	Array *a = (Array*)malloc(sizeof(Array));
	memcpy(a, *initStates, sizeof(Array));
	//Array *result = NULL;
	push(&q, a);
	Element *t = top(q);
	Array *keys = getKeys(cMap);
	while(t != NULL) {
		printf("aaaaa\n");
		a = (Array*)(t->val);
		int i;
		for(i=0;i<getSize(a);i++) {
			int *val = (int*)getByIndex(a, i, sizeof(int));
			printf("*val=%d\n", *val);
			if(*val >= rowSize) break;
			Array *b = eclosure(states, *val, cMap);
			if(b != NULL) {
				int j;
				for(j=0;j<getSize(b);j++) {
					int *val2 = (int*)getByIndex(b, j, sizeof(int));
					printf("val2=%d\n", *val2);
				}
				push(&q, b);
				//result = b;
				mergeSort(initStates, b);
				iterateArray(*initStates);
			}
		}
		printf("\nsafdsfs\n");
		pop(&q);
		t = top(q);
		printf("bbbbb\n");	
	}
//	return deltaRecursion(states, initStates, cMap, 'E'); 
}

Array *NFA2DFA(NFAModel *model, char *s) {
	if(model == NULL || s == NULL || !strlen(s)) return NULL;
	HashMap *colTitle = model->colTitle;
	Array *keys = getKeys(colTitle);
	Array *rowTitle= model->rowTitle;
	Array ***states = model->states;
	Array *initStates = NULL;
	int st = 0;
	add(&initStates, &st, sizeof(int));
	eclosureRecursion(states, &initStates, colTitle, getSize(rowTitle));
	char *p = s;
	Array *newStates = NULL;
	while(*p != '\0') {
//		initStates = deltaRecursion(states, &initStates, colTitle, *p);
		printf("---before----\n");
		iterateArray(initStates);
		int i;
		for(i=0;i<getSize(initStates);i++) {
			int *val = (int*)getByIndex(initStates, i, sizeof(int));
			printf("val=%d,", *val);
			if(*val >= getSize(rowTitle)) break;
			Array *temp = delta2(states, *val, colTitle, *p);
			if(temp != NULL) {
				printf("aaaa\n");
				mergeSort(&newStates, temp);
			}
		}
		printf("\n");
		//initStates = delta2(states, &initStates, colTitle, *p);
		printf("---after----\n");
		printf("key=%c\n", *p);
		initStates = newStates;
		newStates = NULL;
		iterateArray(initStates);
		eclosureRecursion(states, &initStates, colTitle, getSize(rowTitle));
		p++;
	}
	int i;
	printf("---NFA2DFA---\n");
	printf("size of initStates is %d\n", getSize(initStates));
	for(i=0;i<getSize(initStates);i++) {
		int *val = (int*)getByIndex(initStates, i, sizeof(int));
		printf("%d,", *val);
	}
	printf("\n");
	printf("endStates is %d\n", model->endState);
	return initStates;
}

void  testMergeSort() {
	int a[] = {1,3,7,9};
	int b[] = {2,4,5,6};
	Array *aArr = NULL;
	Array *bArr = NULL;
	int aSize = sizeof(a)/sizeof(a[0]);
	int bSize = sizeof(b)/sizeof(b[0]);
	int i;
	for(i=0;i<aSize;i++) {
		add(&aArr, &a[i], sizeof(int));
	}
	for(i=0;i<bSize;i++) {
		add(&bArr, &b[i], sizeof(int));
	}
	mergeSort(&aArr, bArr);
	for(i=0;i<getSize(aArr);i++) {
		int *value = (int*)getByIndex(aArr,i, sizeof(int));
		printf("%d,", *value);
	}
	printf("\n");
	for(i=0;i<getSize(bArr);i++) {
		int *value = (int*)getByIndex(bArr, i, sizeof(int));
		printf("%d,", *value);
	}
	printf("\n");
}

bool isMatch(char *s, char *p) {
	char *pMove = p;
	Graph *g = NULL;
	while(*pMove != '\0') {
		if(*(pMove+1) == '*') {
			if(*pMove == '.') {
				addDocNFA(&g);
				addDocStarNFA(&g);
			}
			else addKleenStarNFA(&g, *pMove);
			pMove+=2;
		} else {
			if(*pMove == '.') addDocNFA(&g);
			else addStringNFA(&g, *pMove);
			pMove++;
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
	Array *result = NFA2DFA(model, s);
	int *last = (int*)getLast(result, sizeof(int));
	if(model->endState == (last == NULL ? -1 : *last)) return true;
	else return false;
}

void testDelta() {
	char *s = "mississippi";
	char *p = "mis*is*p*.";
	bool b = isMatch(s, p);
	printf("result is %d\n", b);
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

void testQueue() {
	int a[] = {2,3,4,5,6,7,8,9};
	int *p = a;
	Queue *q = NULL;
	int size = sizeof(a)/sizeof(a[0]);
	int i=0;
	push(&q, p);
	i++;
	p++;
	Element *t = top(q);
	while(t != NULL) {
		if(i < size) {
			push(&q, p);
		}
		int *val = (int*)(t->val);
		printf("sdfsdfsdfsd,");
		printf("%d\n", *val);
		pop(&q);
		t = top(q);
		i++;
		p++;
	}
}

void testDocNFA() {
	Graph *g = NULL;
	addDocNFA(&g);
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
	printf("endState=%d\n", g->endState);
}

void testDocStarNFA() {
	Graph *g = NULL;
	addDocStarNFA(&g);
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
	printf("endState=%d\n", g->endState);
}

int main(void) {

//	testMap();

	testDelta();

//	testArray();

//	testMergeSort();

//	testQueue();

//	testDocNFA();

//	testDocStarNFA();

	return 0;

}
