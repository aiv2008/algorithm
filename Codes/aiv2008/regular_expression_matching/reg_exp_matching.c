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
	struct Array *entity;
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
	//printf("aaaa\n");
	int hashCode = hash(key);
	Entry *entry = *((*map)->entry + hashCode);
	if(entry == NULL) {
		*((*map)->entry + hashCode) = (Entry*)calloc(1, sizeof(Entry));
		entry = *((*map)->entry + hashCode);
		//entry = (Entry*)calloc(1, sizeof(Entry));
		entry->key = key;
		entry->val = val;
		Entity *entity = (Entity*)malloc(sizeof(Entity));
		entity->key = key;
		entity->val = val;
		add(&(*map)->entity, entity, sizeof(Entity));
		(*map)->size = (*map)->size + 1;
	} else {
		Entry *pEntry = entry;
		while(pEntry->next != NULL) {
			if(pEntry->key == key) {
				printf("11key=%c, val=%d\n", key, val);
				pEntry->val = val;
				int i;
				Array *entites = (*map)->entity;
				printf("entites size: %d\n", entites->size);
				for(i=0;i<entites->size;i++) {
					Entity *entity = (Entity*)getByIndex(entites, i, sizeof(Entity));
					printf("entity->key=%c, key=%c\n", entity->key, key);
					if(entity->key == key) {
						printf("enter here!!!\n");
						entity->val = val;
						break;
					}
				}
				break;
			}
			pEntry = pEntry->next;
		}
		//最后一个节点
		if(pEntry->key == key) {
			pEntry->val = val;
			int i;
			Array *entites = (*map)->entity;
			printf("entites size: %d\n", entites->size);
			for(i=0;i<entites->size;i++) {
				Entity *entity = (Entity*)getByIndex(entites, i, sizeof(Entity));
				printf("entity->key=%c, key=%c\n", entity->key, key);
				if(entity->key == key) {
					printf("enter here!!!\n");
					entity->val = val;
					break;
				}
			}
		} else {
			Entry *newEntry = (Entry*)calloc(1, sizeof(Entry));
			newEntry->key = key;
			newEntry->val = val;
			pEntry->next = newEntry;
			(*map)->size = (*map)->size + 1;
			Entity *entity = (Entity*)malloc(sizeof(Entity));
			entity->key = key;
			entity->val = val;
			add(&(*map)->entity, entity, sizeof(Entity));
		}
	}
}

Array *getEntites(HashMap *map) {
	if(map == NULL) return NULL;
	return map->entity;
/**
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
**/
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
	HashMap *weight = g->weight;
	//int weight = get(g->weight, data);
	if(get(weight, data) == -1) {
		put(&weight, data, weight->size);
	}
//	add(&g->weight, &data, sizeof(char));	
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
			if(array != NULL) {
				int j;
				for(j=0;j<array->size;j++) {
					int *value = (int*)getByIndex(array, j, sizeof(int));
					if(*value == i) break;
					else if(*value < i) addByIndex(&array, &i, sizeof(int), j);
				}
				if(j == array->size) add(&array, &i, sizeof(int));
			} else {
				add(&array, &i, sizeof(int));
			}
		}
	}
	return array;
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

//	int *node = g->node;
	HashMap *weight = g->weight;
	int wSize = weight->size;
	printf("wSize=%d\n", wSize);
	Array *entities = getEntites(weight);
	for(i=0;i<size;i++) {
		int j;
		for(j=0;j<wSize;j++) {
			//char *c = getByIndex(weight, j, sizeof(char));
			//Entry *entry = getEntries(weight);
			//Array *entity = getEntites(weight);
			//char c = (entity+j)->key;
			Entity *entity = (Entity*)getByIndex(entities, j, sizeof(Entity));
			char c = entity->key;
			printf("key=%c\n, value=%d\n", entity->key, entity->val);
			Array *array = delta(g, *(node+i), c);
			if(array != NULL) {
				printf("%c: {", c);
				int k;
				for(k=0;k<array->size;k++) {
					int *value = (int*)getByIndex(array, k, sizeof(int));
					printf("%d,", *value );
				}
				printf("}\n");
			}
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
	//printf("%d\n", map->size);
	Array *entites = getEntites(map);
	if(entites == NULL) printf("entity is null\n");
	printf("map size: %d\n", entites->size);
	for(i=0;i<entites->size;i++) {
		Entity *entity = (Entity*)getByIndex(entites, i, sizeof(Entity));
		char key = entity->key;
		int val = entity->val;
		printf("key=%c, val=%d\n", key, val);
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

	testMap();

//	testDelta();

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
