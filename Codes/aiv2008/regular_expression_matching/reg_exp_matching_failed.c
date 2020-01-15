#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAP_SIZE 7
#define ARRAY_SIZE 10
#define REG_TYPE_COMMON 'c'
#define REG_TYPE_KLEEN 'k'
#define REG_TYPE_DOT 'd'

//struct of the element of the hashmap
typedef struct {
	char key;
	int val;
	//struct Entry* this;
	struct Entry* next;
} Entry;

//struct of the hashmap
typedef struct {
	//Entry entry[MAP_SIZE];
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
//	int *val;
	char *val;
	int size;
	int capacity;
} Array;

/**
typedef struct {
	int rowSize;
	int colSize;
	struct Array **ele;
} Matrix;
**/

typedef struct {
	//struct HashMap *rowTitle;
	struct Array *rowTitle;
	struct HashMap *colTitle;
	//struct Array *colTitle;
	//struct Array ***matrix;
	struct Array *matrix;
} StatusMatrix;

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
		entry = (Entry*)calloc(1, sizeof(Entry));
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
	//printf("val=%d\n", *val);
	if(array == NULL) return ;
	if(*array == NULL) {
		*array = (Array*)calloc(1, sizeof(Array));
		(*array)->capacity = ARRAY_SIZE;
		//int *a = (int*)calloc(ARRAY_SIZE, sizeof(int));
		char *a = (char*)calloc(ARRAY_SIZE, len);
		(*array)->val = a;
		a = NULL;		
	} else if((*array)->size + 1 > (*array)->capacity) {
		(*array)->capacity = (*array)->capacity + ((*array)->capacity) / 2;
		//int *a = (int*)calloc((*array)->capacity, sizeof(int));
		char *a = (char*)calloc((*array)->capacity, len);
		printf("size=%d\n", (*array)->size);
		memcpy(a, (*array)->val, len*(*array)->size);
		int size = (*array)->size;
		/**
		int i;
		for(i=0;i<size;i++) {
			printf("%d,", *(a+i));
		}
		printf("\n");
		**/
		(*array)->val = NULL;
		(*array)->val = a;
		a = NULL;
	}
	char *value = (*array)->val;
	int size = (*array)->size;
	memcpy(value+len*size, val, len);
//	*(value+len*size) = val;
	(*array)->size = size + 1;
}

/**
void setByIndex(Array *array,int val, int index) {
	if(array == NULL) return ;
	if(index >= array->size) {
		printf("index is out of bound!\n");
		return ;
	}
	int* a = array->val;
	*(a+index) = val;
}
**/

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


void getKleeneStarMatrix( char c, char*** matrix, int *rowSize, int *colSize) {
	if(matrix == NULL) return ;
	*rowSize = 4;
	*colSize = 4;
	*matrix = (char**)calloc(*rowSize, sizeof(char*));
	int i;
	for(i=0;i<*rowSize;i++) {
		*(*matrix+i) = (char*)calloc(*colSize, sizeof(char));
		int j;
		for(j=0;j<*colSize;j++) {
			if((i==0&&j==1)||(i==0&&j==3)||(i==2&&j==1)||(i==2&&j==3)) {
				*(*(*matrix+i)+j) = 'E';
			} else if(i==1&&j==2) {
				*(*(*matrix+i)+j) = c;
			} else {
				*(*(*matrix+i)+j) = '0';
			}
		}
	}
}


void getCommmonMatrix( char c, char*** matrix, int *rowSize, int *colSize) {
	if(matrix == NULL) return ;
	*rowSize = 3;
	*colSize = 3;
	*matrix = (char**)calloc(*rowSize, sizeof(char*));
	int i;
	for(i=0;i<*rowSize;i++) {
		*(*matrix+i) = (char*)calloc(*colSize, sizeof(char));
		int j;
		for(j=0;j<*colSize;j++) {
			if(i==0&&j==1) {
				*(*(*matrix+i)+j) = c;
			} else if(i==1&&j==2) {
				*(*(*matrix+i)+j) = 'E';
			} else {
				*(*(*matrix+i)+j) = '0';
			}
		}
	}
}

//allow there is no row title, but not allow there is no collum title
void addRow(StatusMatrix *sm) {
	if(sm == NULL || sm->colTitle == NULL)	return;
	if(sm->rowTitle == NULL) {
		Array *rowTitle = NULL;
		add(&rowTitle, 0, sizeof(int));
		sm->rowTitle = rowTitle;
	} else {
		Array *rowTitle = sm->rowTitle;
		add(&rowTitle, getSize(rowTitle), sizeof(int));
	}
	HashMap *colTitle = sm->colTitle;
	Array *matrix = sm->matrix;
	Array *row = NULL;
	Array *col = NULL;
	int j;
	for(j=0;j<colTitle->size;j++) {
		add(&row, col, sizeof(Array));
	}
	add(&matrix, row, sizeof(Array));
	sm->matrix = matrix;
}

void addCol(StatusMatrix **sm, char c) {
	if(sm == NULL) return;
	if(*sm == NULL) {
		*sm = (StatusMatrix*)calloc(1, sizeof(StatusMatrix));
		put(&(*sm)->colTitle, c, 0);
	} else {
		HashMap *colTitle = (*sm)->colTitle;
		put(&colTitle, c, colTitle->size);
	}
}

Array *getMatrixByIndex(StatusMatrix *sm, int rowIndex, int colIndex) {
	if(sm == NULL) {
		printf("matrix can not be null\n");
		return NULL;
	}
	if(sm->rowTitle == NULL || sm->colTitle == NULL) {
		printf("row title or collum title can not be null\n");
		return NULL;
	}
	HashMap *rowTitle = sm->rowTitle;
	Array *colTitle = sm->colTitle;
	if(rowIndex < 0 || colIndex < 0 || rowIndex >= rowTitle->size || colIndex >= colTitle->size) {
		printf("index is overflow\n");
		return NULL;
	}
	Array *matrix = sm->matrix;
	Array *row = (Array*)getByIndex(matrix, rowIndex, sizeof(Array));
	Array *cell = (Array*)getByIndex(row, colIndex, sizeof(Array));
	return cell;
}

int regExpToNFA(char val, char regType, StatusMatrix **sm, int startStatus) {
	if(sm == NULL) return;
	if(*sm == NULL) {
		*sm = (StatusMatrix*)calloc(1, sizeof(StatusMatrix));
	}
	char **matrix = NULL;
	int rowSize = 0;
	int colSize = 0;
	if(regType == REG_TYPE_KLEEN) {
		getKleeneStarMatrix(val, &matrix, &rowSize, &colSize);
	} else {
		getCommmonMatrix(val, &matrix, &rowSize, &colSize);
	}
	int i = 0, j=0;
	int rowIndex = 0, colIndex = 0 ;
	char c;
	HashMap *rowTitle = (*sm)->rowTitle;
	Array *colTitle = (*sm)->colTitle;

	while(i<rowSize) {
		c = *(*(matrix+i)+j);
		if(c != '0') {
			if(rowTitle == NULL) {
				rowTitle = (HashMap*)calloc(1, sizeof(HashMap));
				(*sm)->rowTitle = rowTitle;
				put(&rowTitle, c, 0);
				colIndex = 0;
			} else {
				int value = get((*sm)->rowTitle, c);
				if(value >= 0) {
					colIndex = value;
				} else {
					colIndex = rowTitle->size+1;
					put(&rowTitle, c, colIndex);
				}
			}
		/**	
			if(colTitle == NULL) {
				colTitle = (Array*)calloc(1, sizeof(Array));
				(*sm)->colTitle = colTitle;
				add(&colTitle, 0);
				rowIndex = 0;
			} else {
				rowIndex = colTitle->size;
				add(&colTitle, rowIndex);	
			}
**/
			
		}
		i++;
	}
}

void test() {
	int rowSize = 4;
	int colSize = 5;
	int **a = (int**)calloc(4, sizeof(int*));
	printf("size=%d\n", sizeof(a)/sizeof(*a));
}

void testHashMap() {
	HashMap *map = NULL;;
	char b[] = {'a', 'a', 'c'};
	int i;
	int size = sizeof(b)/sizeof(b[0]);
	for(i=0;i<size;i++) {
		int val = get(map, b[i]);
		put( &map, b[i], val == -1 ? 1 : (val + 1));
	}
	for(i=0;i<size;i++) {
		printf("%d,", get(map, b[i]));
	}
	printf("map size=%d", map->size);
	printf("\n");	
}

void testKleeneStarMatrix() {
	char **matrix = NULL;
	int rowSize = 0;
	int colSize = 0;
	getKleeneStarMatrix('a', &matrix, &rowSize, &colSize);
	int i;
	for(i=0;i<rowSize;i++) {
		int j;
		for(j=0;j<colSize;j++) {
			printf("%c ", *(*(matrix+i)+j));
		}
		printf("\n");
	}
}

void testQueue() {
	char b[] = {'a','b','c','d','e','f','g','h', 'a', 'c'};
	int size = sizeof(b)/sizeof(b[0]);
	Queue *queue = NULL;
	int i;
	for(i=0;i<size;i++) {
		push(&queue, b[i]);
		Element *t = top(queue);
		Element *b = bottom(queue);
		printf("top=%c, bottom=%c\n", t->val, b->val);
	}
	while(queue != NULL) {
		iterateQueue(queue);
		pop(&queue);
	}
}

void testArray() {
	Array *array = NULL;
	//int a[] = {1,23,3,4,5,6,7,4,3,6,8};
	int a[11][2] = {{1,2},{3,4},{5,6},{7,8},{9,10},{11,12},{13,14},{15,16},{17,18},{19,20},{21,22}};
	//int size = sizeof(a)/sizeof(a[0]);
	int size = 11;
	int i;
	for(i=0;i<size;i++) {
		int j;
		Array *b = NULL;
		for(j=0;j<2;j++) {
			add(&b, &a[i][j], sizeof(int));
		}
		add(&array, b, sizeof(Array));
	}
	printf("capacity=%d, size=%d\n", array->capacity, array->size);
	for(i=0;i<size;i++) {
		int j;
		Array *b = getByIndex(array, i, sizeof(Array));
		printf("b size is %d\n", b->size);
		for(j=0;j<b->size;j++) {
			int *value = (int*)getByIndex(b, j, sizeof(int));
			printf("%d,", *value);
		}
		printf("\n");
	}
//	iterateArray(array);
//	setByIndex(array, 100, 20);
//	iterateArray(array);
}

void testArray2() {
	int a[] = {1,2,3,4,5,6,7, 8,9,10,11};
	int size = sizeof(a)/sizeof(a[0]);
	int i;
	Array *array = NULL;
	for(i=0;i<size;i++) {
		add(&array, &a[i], sizeof(int)); 	
	}
	for(i=0;i<array->size;i++) {
		printf("%d,", *((int*)(array->val)+i));
	}
	printf("\n");
}

void testStatusMatrix() {
	char colArray[] = {'E', 'a'};
	int *valArray[] = {{1,3}, {2}};
	int valLen[] = {2,1};
	StatusMatrix *sm = NULL;
	addCol(&sm, colArray[0]);
	addCol(&sm, colArray[1]);
	addRow(sm);
	int i;
	int size = sizeof(colArray)/sizeof(colArray[0]);
	for(i=0;i<size;i++) {
		int colIndex = get(sm->colTitle, colArray[i]);
		int rowIndex = getSize(sm->rowTitle) - 1;
		Array *matrix = getMatrixByIndex(sm, rowIndex, colIndex);	
		int *a = valArray[i];
		int size = valLen[i];
		int j;
		for(j=0;j<size;j++) {
			add(&matrix, *(a+j), sizeof(int));
		}
	}
	HashMap *colTitle = sm->colTitle;
	Array *rowTitle = sm->rowTitle;
	int colSize = colTitle->size;
	int rowSize = rowTitle->size;
	for(i=0;i<rowSize;i++) {
		printf("row title= %d\n", *(rowTitle+i));
		int j;
		for(j=0;j<colSize;j++) {
			//printf("", *(colTitle));
		}
	}	
}

int main(void) {
	//testKleeneStarMatrix();
//	testArray();
//	testMatrix();
	testHashMap();
//testKleeneStarMatrix();
//testStatusMatrix();
	return 0;
}
