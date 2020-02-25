#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define ARRAY_SIZE 10
#define bool char
#define true '1'
#define false '0'
#define MAP_SIZE 13

//把NFA和DFA统一一个FA
typedef struct {
	//用数字区分不同的状态
	int stateNum;
	struct Array/**<FAEdge>**/ *edge;
	//是否为接受状态 1 是 0 否
	int state;
} FANode;

typedef struct {
	struct FANode *node;
	char value;
} FAEdge;

typedef struct {
	struct FANode *start;
	struct FANode *end;
} FA;

/**
typedef struct {
	//用数字区分不同的状态
	int stateNum;
	struct Array**<NFAEdge>** *edge;
	//是否为接受状态 1 是 0 否
	int state;
} NFANode;

typedef struct {
	struct NFANode *node;
	char value;
} NFAEdge;

typedef struct {
	struct NFANode *start;
	//注: end节点不能有任何指向其他节点的边
	struct NFANode *end;
} NFA;

typedef struct {
	//用数字区分不同的状态
	int stateNum;
	struct Array**<NFANode>** *states;
	struct Array**<DFAEdge>** *edges;
	int state;
} DFANode;

typedef struct {
	struct DFANode *node;
	char value;
} DFAEdge;

typedef struct {
	struct DFANode *start;
	struct Array**<DFANode>** *ends;
} DFA;
**/

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
	char **val;
	int size;
	int capacity;
} Array;

typedef struct {
	int key;
	char *value;
} Entity;

typedef struct {
	struct Array/**<Entity>**/ **entity;
} HashMap;

typedef struct {
	int stateNum;
} Integer;

void swap(int *a, int *b/**, int len**/) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

char *getByIndex(Array *array, int index/**, int len**/) {
	if(!getSize(array)) return NULL;
	if(index >= array->size) {
		printf("getByIndex: index is out of bound!\n");
		return -1;
	}
	return *(array->val+index);
}

char *getLast(Array *array, int len) {
	if(array == NULL) return NULL;
	return *(array->val+len*(array->size-1));
}

int partition(Array *array, int p, int r) {
	//printf("r=%d\n", r);
	int *valR = (int*)getByIndex(array, r);
	int i = p - 1;
	int j;
	for(j=p;j<r;j++) {
		//printf("i=%d, j=%d\n", i, j);
		int *valJ = (int*)getByIndex(array, j);
		if(*valJ <= *valR) {
			i++;
			//printf("--before---\n");
			int *valI = (int*)getByIndex(array, i);
			//printf("i=%d, j=%d, ival=%d, jval=%d\n",i,j, *valI, *valJ);
			swap(valI, valJ);
			//printf("--after---\n");
			//printf("i=%d, j=%d\n", *valI, *valJ);
		}
	}
	//printf("%d\n", i+1);
	int *valIP1 = (int*)getByIndex(array, i+1);
	swap(valIP1, valR);
	int n;
	for(n=0;n<getSize(array);n++ ){
		int *val = (int*)getByIndex(array, n);
		printf("%d,", *val);
	}
	printf("\n");
	return i+1;
}

void quicksort(Array *array, int p, int r) {
	if(p < r) {
		int q = partition(array, p, r);
		quicksort(array, p, q-1);
		quicksort(array, q+1, r);
	}
}


int partitionEx(Array *array, int p, int r) {
	//printf("r=%d\n", r);
	//int *valR = (int*)getByIndex(array, r);
	Integer *valR = (Integer*)getByIndex(array, r);
	int i = p - 1;
	int j;
	for(j=p;j<r;j++) {
		Integer *valJ = (Integer*)getByIndex(array, j);
		if(valJ->stateNum <= valR->stateNum) {
			i++;
			//printf("--before---\n");
			Integer *valI = (Integer*)getByIndex(array, i);
			//printf("i=%d, j=%d, ival=%d, jval=%d\n",i,j, *valI, *valJ);
			Integer *valTmp = valI;
			setByIndex(array, valJ, i);
			setByIndex(array, valTmp, j);
			valTmp = NULL;
			//swap(valI, valJ);
			//printf("--after---\n");
			//printf("i=%d, j=%d\n", *valI, *valJ);
		}
	}
	//printf("%d\n", i+1);
	Integer *valIP1 = (Integer*)getByIndex(array, i+1);
	Integer *valTmp = valIP1;
	setByIndex(array, valR, i+1);
	setByIndex(array, valTmp, r);
	valTmp = NULL;
	//swap(valIP1, valR);
	/**
	int n;
	for(n=0;n<getSize(array);n++ ){
		Integer *val = (Integer*)getByIndex(array, n);
		printf("%d,", val->stateNum);
	}
	printf("\n");
**/
	return i+1;
}

void quicksortEx(Array *array, int p, int r) {
	if(p < r) {
		int q = partitionEx(array, p, r);
		quicksortEx(array, p, q-1);
		quicksortEx(array, q+1, r);
	}
}

/**
int myPartition(Array ***char***array, int start, int end**, int len**)
{
	//if(array == NULL)
	if(!getSize(array))
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
	int *valJ = (int*)getByIndex(array, j);
	int *valEnd = (int*)getByIndex(array, end);
	if(j < end)
	{
		while(j < end)
		{		
			//if(*(array+len*j) <= *(array+len*end)) {
			if(*valJ <= *valEnd) {
				i++;
				int *valI = (int*)getByIndex(array, i);
				if(i != j)
				{
					//swap(array+len*j, array+len*i);
					swap(valJ, valI);
				}
			}
			j++;
		}
		if(i+1 != end)
		{
			int *valIPlus1 = (int*)getByIndex(array, i+1);
			swap(valIPlus1, valEnd);
			//swap(array+len*(i+1), array+len*end);
			return i+1;
		}
		else
		{
			return end;
		}

	}
	return -1;
}
void myQuicksort(Array**char*** *array, int start, int end**, int len**)
{
	//if(array == NULL)
	if(!getSize(array))
	{
		printf("array cannot be null\n");
		return ;
	}
	if(start < end)
	{
		int partitionIndex = myPartition(array, start, end**, len**);
		if(partitionIndex < 0)
		{
		    printf("partitionIndex must larger than 0\n");
		    return ;
		}
		myQuicksort(array, start, partitionIndex-1**, len**);
		myQuicksort(array, partitionIndex+1, end**, len**);
	}
}

int myRandomizedPartition(Array *array**char *array**, int start, int end**, int len**)
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
	if(randIndex != end) {
		//swap(array+len*randIndex, array+len*end);
		swap(getByIndex(array, randIndex), getByIndex(array, end));
	}
	return myPartition(array, start, end**, len**);
}
void myRandomizedQuicksort(Array**char** *array, int start, int end**, int len**)
{
	//if(array == NULL)
	if(!getSize(array))
	{
		printf("quicksort myRandomizedQuicksort: array cannot be null\n");
		return ;
	}
	if(start < end)
	{
		int partitionIndex = myRandomizedPartition(array, start, end**, len**);
		if(partitionIndex < 0)
		{
		    printf("quicksort myRandomizedQuicksort: partitionIndex must larger than 0\n");
		    return ;
		}
		myRandomizedQuicksort(array, start, partitionIndex-1**, len**);
		myRandomizedQuicksort(array, partitionIndex+1, end**, len**);
	}
}
**/


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
			//int *value = (int*)getByIndex(array, i, sizeof(int));
			int *value = (int*)getByIndex(array, i);
			printf("%d,", *value);
		}
		p = p->next;
	}
	printf("\n");
}

void add(Array **array, char *val/**, int len**/) {
	if(array == NULL) return ;
	if(*array == NULL) {
		*array = (Array*)calloc(1, sizeof(Array));
		(*array)->capacity = ARRAY_SIZE;
		//char *a = (char*)calloc(ARRAY_SIZE, len);
		char **a = (char**)calloc(ARRAY_SIZE, sizeof(char*));
		(*array)->val = a;
		//*a = NULL;		
	} 
	if((*array)->size + 1 > (*array)->capacity) {
		(*array)->capacity = (*array)->capacity + ((*array)->capacity) / 2;
		//char *a = (char*)calloc((*array)->capacity, len);
		char **a = (char**)calloc((*array)->capacity, sizeof(char*));
		//memcpy(a, (*array)->val, sizeof(char*)*(*array)->size);
		//memcpy(a, (*array)->val, (*array)->size);
		int i;
		for(i=0;i<(*array)->size;i++) {
			*(a+i) = *((*array)->val+i);
			//printf("i=%d,val=%d,",i, *(*(a+i)));
		}
		//int size = (*array)->size;
		//(*array)->val = NULL;
		free((*array)->val);
		(*array)->val = a;
		//*a = NULL;
	}
	int size = (*array)->size;
	*((*array)->val+size) = val;
	(*array)->size = size + 1;
}

void addByIndex(Array **array, char *val, int index) {
	if(array == NULL) return ;
	if(index < 0) {
		printf("index must larger than 0\n");
		return;
	}
	if(*array == NULL) {
		if(index == 0) {
			*array = (Array*)calloc(1, sizeof(Array));
			(*array)->capacity = ARRAY_SIZE;
			char **a = (char**)calloc(ARRAY_SIZE, sizeof(char*));
			(*array)->val = a;
		} else {
			printf("addByIndex: index is out of bound\n");
			return;
		}
	} 
	if(index > (*array)->size) {
		printf("addByIndex: index is out of bound\n");
		return;
	}else if(index == (*array)->size ) {
		add(array, val);
	} else {
		if((*array)->size + 1 > (*array)->capacity) {
			(*array)->capacity = (*array)->capacity + ((*array)->capacity) / 2;
			char **a = (char**)calloc((*array)->capacity, sizeof(char*));
			int i;
			for(i=0;i<(*array)->size;i++) {
				*(a+i) = *((*array)->val+i);
			}
			free((*array)->val);
			(*array)->val = a;
		}
		int size = (*array)->size;
		int i;
		for(i=size-1;i>=index;i--) {
			*((*array)->val+i+1) = *((*array)->val+i);
		}
		*((*array)->val+index) = val;
		(*array)->size = size + 1;
	}
}

void setByIndex(Array *array, char *val, int index) {
	if(array == NULL) return;
	if(index < 0) {
		printf("index must larger than 0\n");
		return;
	}
	if(index >= array->size) {
		printf("setByIndex: index is out of bound\n");
		return;
	}
	*(array->val+index) = val;
}

int getSize(Array *array) {
	if(array == NULL) return 0;
	return array->size;
}
/**
int *sortNFANode(Array**<FANode>** *array) {
	if(!getSize(array)) return;
	int *result = (int*)malloc(getSize(array)*sizeof(int));
	int i;
	for(i=0;i<getSize(array);i++) {
		FANode *node = (FANode*)getByIndex(array, i);
		*(result+i) = node->stateNum;
	}
	myRandomizedQuicksort(result, 0, getSize(array)-1);
	return result;
}
**/

Array *sortNFANode(Array/**<FANode>**/ *array) {
	if(!getSize(array)) return;
	//int *result = (int*)malloc(getSize(array)*sizeof(int));
	Array *result = NULL;
	int i;
	for(i=0;i<getSize(array);i++) {
		FANode *node = (FANode*)getByIndex(array, i);
		//*(result+i) = node->stateNum;
		add(&result, &node->stateNum);
	}
	//myRandomizedQuicksort(result, 0, getSize(array)-1/**, sizeof(int)**/);
	quicksort(result, 0, getSize(array)-1);
	return result;
}

int hashCode(int key) {
	return key % MAP_SIZE;
}

void put(HashMap **map, int key, char *value/**, int valueLen**/) {
	if(map == NULL) return ;
	if(*map == NULL) {
		*map = (HashMap*)malloc(sizeof(HashMap));
		(*map)->entity = (Array**)calloc(MAP_SIZE, sizeof(Array*));
		if((*map)->entity == NULL) {
			printf("hash map put failed: entity calloc failed\n");
			return;
		}
	}
	int index = hashCode(key);
	Array **entityArray = (*map)->entity;
	if(*(entityArray+index) == NULL) {
		Entity *entity = (Entity*)calloc(1, sizeof(Entity));
		if(entity == NULL) {
			printf("hash map put failed: entity calloc failed\n");
			return;
		}
		entity->key = key;
		//entity->value = (char*)malloc(valueLen);
		entity->value = value;
		//memcpy(entity->value, value, valueLen);
		add((*map)->entity+index, entity);
	} else {
		Array *a = *(entityArray+index);
		int i=0;
		for(;i<getSize(a);i++) {
			Entity *entity = (Entity*)getByIndex(a, i);
			if(entity->key == key) {
				entity->value = value;
				//memcpy(entity->value, value, valueLen);
				break;
			}
		}
		if(i == getSize(a)) {
			Entity *entity = (Entity*)calloc(1, sizeof(Entity));
			if(entity == NULL) {
				printf("hash map put failed: entity calloc failed\n");
				return;
			}
			entity->key = key;
			entity->value = value;
			//entity->value = (char*)malloc(valueLen);
			//memcpy(entity->value,  value, valueLen);
			add((*map)->entity+index, entity);
		}
	}
}

char *get(HashMap *map, int key) {
	if(map == NULL) return NULL;
	int index = hashCode(key);
	Array *a = *(map->entity+index);
	if(a == NULL) return NULL;
	char *result = NULL;
	int i=0;
	for(;i<getSize(a);i++) {
		//Entity *entity = (Entity*)getByIndex(a, i, sizeof(Entity));
		Entity *entity = (Entity*)getByIndex(a, i);
		if(entity->key == key) {
			result = entity->value;
			break;
		}
	}
	return result;
}


FANode *initFANode(Array/**<FAEdge>**/ *edgeAry, int state, int stateNum) {
	if(state != 0 && state != 1) {
		printf("init fa node failed: state must be 1 or 0\n");
		return NULL;
	}
	FANode *node = (FANode*)calloc(1, sizeof(FANode));
	if(node == NULL) {
		printf("init fa node failed\n");
		return NULL;
	}
	node->edge = edgeAry;
	node->state = state;
	node->stateNum = stateNum;
	return node;
}

FAEdge *initFAEdge(char c) {
	FAEdge *edge = (FAEdge*)calloc(1, sizeof(FAEdge));
	if(edge == NULL) {
		printf("init FA edge node failed\n");
		return NULL;
	}
	edge->value = c;
	return edge;
}

FA *initFA(FANode *start, FANode *end) {
	FA *fa = (FA*)malloc(sizeof(FA));
	if(fa == NULL) {
		printf("initFA failed: malloc fa error\n");
		return NULL;
	}
	fa->start = start;
	fa->end = end;
	return fa;
}

FAEdge *initEpEdge() {
	return initFAEdge(' ');
}

void updateFA(FA *fa, FANode *start, FANode *end) {
	if(fa == NULL || start == NULL || end == NULL) {
		printf("update fa failed: start or end node cannot be null\n");
		return NULL;
	}
	fa->start = start;
	fa->end = end;
}

FA *symbolFA(char c, int *stateNum) {
	FAEdge *edge = initFAEdge(c);
	FANode *end = initFANode(NULL, 1, *stateNum);
	*stateNum = *stateNum + 1;
	edge->node = end;
	Array/**<FAEdge>**/ *edgeAry = NULL;
	add(&edgeAry, edge);
	FANode *start = initFANode(edgeAry, 0, *stateNum);
	return initFA(start, end);
}


FA *epsilonFA(int *stateNum) {
	return symbolFA(0x20, stateNum);
}

FA *unonFA(FA *faS, FA *faT, int* stateNum) {
	if(faT == NULL) return faS;
	else if(faS == NULL) return faT;
	FAEdge *edge1 = initEpEdge();
	FAEdge *edge2 = initEpEdge();
	Array *edgeAry1 = NULL;
	add(&edgeAry1, edge1);
	add(&edgeAry1, edge2);
	FANode *start = initFANode(edgeAry1, 0, *stateNum);
	*stateNum = *stateNum + 1;
	FANode *startOfS = faS->start;
	FANode *startOfT = faT->start;
	edge1->node = startOfS;
	edge2->node = startOfT;
	FANode *end = initFANode(NULL, 1, *stateNum);
	FANode *endOfS = faS->end;
	FANode *endOfT = faT->end;
	FAEdge *edge3 = initEpEdge();
	FAEdge *edge4 = initEpEdge();
	edge3->node = end;
	edge4->node = end;
	Array *edgeAry2 = NULL;
	Array *edgeAry3 = NULL;
	add(&edgeAry2, edge3);
	add(&edgeAry3, edge4);
	endOfS->edge = edgeAry2;
	endOfT->edge = edgeAry3;
	updateFA(faS, start, end);
	return faS;
}

FA *concatFA(FA *faS, FA *faT) {
	if(faT == NULL) return faS;
	else if(faS == NULL) return faT;
	FANode *endOfS = faS->end;
	FANode *startOfT = faT->start;
	endOfS->edge = startOfT->edge;
	endOfS->state = 0;
	updateFA(faS, faS->start, faT->end);
	return faS;
}

FA *kleenStarFA(FA *fa, int *stateNum) {
	if(fa == NULL) return NULL;
	FANode *end = initFANode(NULL, 1, *stateNum);
	*stateNum = *stateNum + 1;
	FAEdge *edge1 = initEpEdge();
	edge1->node = fa->start;
	FAEdge *edge2 = initEpEdge();
	edge2->node = end;
	FAEdge *edge3 = initEpEdge();
	edge3->node = fa->start;
	FAEdge *edge4 = initEpEdge();
	edge4->node = end;
	Array/**<FAEdge>**/ *edgeAry1 = NULL;
	add(&edgeAry1, edge1);
	add(&edgeAry1, edge2);
	FANode *start = initFANode(edgeAry1, 0, *stateNum);
	FANode *endOfFA = fa->end;
	Array/**<FAEdge>**/ *edgeAry2 = NULL;
	add(&edgeAry2, edge3);
	add(&edgeAry2, edge4);
	endOfFA->edge = edgeAry2;
	endOfFA->state = 0;
	FA *result = initFA(start, end);	
	return result;
}

FA *unonAllFA(int *stateNum) {
	Array/**<FAEdge>**/ *startEdgeAry = NULL;
	FANode *endNode = initFANode(NULL, 1, *stateNum);
	*stateNum = *stateNum + 1;
	FAEdge *endEdge = NULL;
	FAEdge *startEdge = NULL;
	int i;
	for(i=97;i<=122;i++) {
		FA *fa = symbolFA(i, stateNum);
		*stateNum = *stateNum + 1;
		startEdge = initFAEdge(' ');
		FANode *start = fa->start;
		startEdge->node = start;
		add(&startEdgeAry, startEdge);
		FANode *end = fa->end;
		endEdge = initFAEdge(' ');
		endEdge->node = endNode;
		Array/**<FAEdge>**/ *endEdgeAry = NULL;
		add(&endEdgeAry, endEdge);
		end->edge = endEdgeAry;
		end->state = 0;
	}
	FANode *startNode = initFANode(startEdgeAry, 0, *stateNum);
	FA *fa = initFA(startNode, endNode);
	return fa;
}

FA *reg2NFA(char *p) {
	char *pMove = p;
	FA *nfa = NULL;
	FA *nfaTmp = NULL;
	HashMap *map = NULL;
	Array *array = NULL;
	int stateNum = 0;
	int origValue = 1;
	//先加入一个epsilon，以匹配空串
	nfa = epsilonFA(&stateNum) ;
	stateNum++; 
	//是否已包含所有字母表里的字母， 因为当模式里含有'.'时， 即包含字母表的所有字母
	while(*pMove != '\0') {
		if(*(pMove+1) == '*') {
			if(*pMove == '.') {
				nfaTmp = unonAllFA(&stateNum);
			} else {
				nfaTmp = symbolFA(*pMove, &stateNum);
			}
			stateNum++;
			nfaTmp = kleenStarFA(nfaTmp, &stateNum);
			stateNum++; 
			nfa = concatFA(nfa, nfaTmp);
			pMove+=2;
		} else {
			if(*pMove == '.') {
				nfaTmp = unonAllFA(&stateNum);
			} else {
				nfaTmp = symbolFA(*pMove, &stateNum);
			}
			stateNum++;
			nfa = concatFA(nfa, nfaTmp);
			pMove++;
		}
		nfaTmp = NULL;
	}
	return nfa;
}

/**
NFA *reg2NFA(char *p) {
	char *pMove = p;
	NFA *nfa = NULL;
	NFA *nfaTmp = NULL;
	HashMap *map = NULL;
	Array *array = NULL;
	int stateNum = 0;
	int origValue = 1;
	//先加入一个epsilon，以匹配空串
	nfa = epsilonNFA(&stateNum) ;
	//是否已包含所有字母表里的字母， 因为当模式里含有'.'时， 即包含字母表的所有字母
	while(*pMove != '\0') {
		if(*(pMove+1) == '*') {
			if(*pMove == '.') {
				nfaTmp = unonAllNFA(&stateNum);
				//isAllAlphabet = true; 
				//array = nfaTmp->alphabet;
			} else {
				nfaTmp = symbolNFA(*pMove, &stateNum);
			}
			stateNum++;
			nfaTmp = kleenStarNFA(nfaTmp, &stateNum);
			stateNum++; 
			nfa = concatNFA(nfa, nfaTmp);
			pMove+=2;
		} else {
			if(*pMove == '.') {
				nfaTmp = unonAllNFA(&stateNum);
				//isAllAlphabet = true; 
				//array = nfaTmp->alphabet;
			} else {
				nfaTmp = symbolNFA(*pMove, &stateNum);
			}
			stateNum++;
			nfa = concatNFA(nfa, nfaTmp);
			pMove++;
		}
		nfaTmp = NULL;
	}
	return nfa;
}
**/

Array *delta(FANode *node, char value) {
	if( node == NULL) {
		printf("delta function failed: nfa node is null\n");
		return NULL;
	}
	Array *dfaStates = NULL;
	Array *edgeAry = node->edge;
	int i;
	for(i=0;i<getSize(edgeAry);i++) {
		FAEdge *edge = (FAEdge*)getByIndex(edgeAry, i);
		if(edge != NULL) {
			if(edge->value == value) {
				add(&dfaStates, edge->node);
			}	
		}
	}
	return dfaStates;
}

//从node出发，只通过epsilon边能到达的节点，包括node本身
Array *eclosure(FANode *node) {
	if(node == NULL) {
		printf("eclosure function failed: nfa node is null\n");
		return NULL;
	}

	Array *dfaStates = NULL;
	Queue *queue = NULL;
	HashMap *map = NULL;
	int origValue = 1;
	FANode *pMove = node;
	push(&queue, pMove);
	put(&map, pMove, &origValue);
	add(&dfaStates, pMove);
	Element *t = top(queue);
	while(t != NULL) {
		pMove = (FANode*)(t->val);
		if(pMove != NULL) {
			Array *edgeAry = pMove->edge;
			int i;
			for(i=0;i<getSize(edgeAry);i++) {
				FAEdge *edge = (FAEdge*)getByIndex(edgeAry, i);
				if(edge != NULL && edge->value ==' ' && edge->node != NULL) {
					int *value = (int*)get(map, edge->node);
					if(value == NULL) {
						put(&map, edge->node, &origValue/**, sizeof(int)**/);
						push(&queue, edge->node);
						add(&dfaStates, edge->node);
					}				
				}
			}
		}
		pop(&queue);
		t = top(queue);
	}
	return dfaStates;
}

Array *closure(Array/**<FANode>**/ *nodes) {
	if(nodes == NULL) return NULL;
	int i;
	Array *result = NULL;
	//Array *dataAry = NULL;
	HashMap *map = NULL;
	int origVal = 1;
	for(i=0;i<getSize(nodes);i++) {
		FANode *node = (FANode*)getByIndex(nodes, i);
		Array/**<FANode>**/ *a = eclosure(node);
		int j;
		for(j=0;j<getSize(a);j++) {
			FANode *eNode = (FANode*)getByIndex(a, j);
			int *val = (int*)get(map, eNode->stateNum);
			if(val == NULL) {
				add(&result, eNode);
				put(&map, eNode->stateNum, &origVal/**, sizeof(int)**/);
			}
		}
	}
	return result;
}

void printNFANode(FANode *node) {
	if(node == NULL) {
		printf("print dfa node failed: node is null\n");
		return;
	}
	//printf("---begin print nfa node---\n");
	//printf("%d->",node->stateNum);
	Array *edgeAry = node->edge;
	int i;
	for(i=0;i<getSize(edgeAry);i++) {
		printf("%d->",node->stateNum);
		FAEdge *edge = (FAEdge*)getByIndex(edgeAry, i);
		if(edge->value == ' ') {
			printf("epsilon->");
		} else {
			printf("%c->", edge->value);
		}
		printf("%d\n", ((FANode*)(edge->node))->stateNum);
		printf("\n");
	}
	//printf("---end print nfa node---\n");
}

void iterateNFA(FA *nfa) {
	if(nfa == NULL) {
		printf("iterate nfa failed: nfa is null\n");
		return;
	}
	printf("start=%d, end=%d\n", ((FANode*)(nfa->start))->stateNum, ((FANode*)(nfa->end))->stateNum);
	Queue *queue = NULL;
	HashMap  *map = NULL;
	FANode *start = nfa->start;
	push(&queue, start);
	Element *t = top(queue);
	int origValue = 1;
	while(t != NULL) {
		FANode *node = (FANode*)(t->val);
		//printNFANode(node);
		Array *edgeAry = node->edge;
		int i;
		for(i=0;i<getSize(edgeAry);i++) {
			FAEdge *edge = (FAEdge*)getByIndex(edgeAry, i);
			printf("%d->",node->stateNum);
			if(edge->value == ' ') {
				printf("epsilon->");
			} else {
				printf("%c->", edge->value);
			}
			printf("%d\n", ((FANode*)(edge->node))->stateNum);
			if(edge != NULL && edge->node != NULL) {
				int *value = (int*)get(map, edge->node);
				if(value == NULL) {
					put(&map, edge->node, &origValue);
					push(&queue, edge->node);
				}
			}
		}
		pop(&queue);
		t = top(queue);
	}
}

/**
DFAEdge *initDFAEdge(char c) {
	DFAEdge *edge = (DFAEdge*)calloc(1, sizeof(DFAEdge));
	if(edge == NULL) {
		printf("init DFA edge node failed\n");
		return NULL;
	}
	edge->value = c;
	return edge;
}

DFANode *initDFANode(Array**<NFANode>** *states, int stateNum) {
	if(states == NULL) {
		printf("init dfa node failed: states is null\n");
		return NULL;
	}
	DFANode *node = (DFANode*)malloc(sizeof(DFANode));
	if(node == NULL) {
		printf("init dfa node failed: node malloc space failed\n");
		return NULL;
	}
	node->states = states;
	node->stateNum = stateNum;
	node->state = 0;
	int i;
	for(i=0;i<getSize(states);i++) {
		NFANode *nfaNode = (NFANode*)getByIndex(states, i);
		if(nfaNode->state == 1) {
			node->state = 1;
			break;
		}
	}
	return node;
}
**/

/**
void updateDFANodeState(DFANode *node) {
	if(node == NULL) return;
	Array *states = node->states;
	int i;
	for(i=0;i<getSize(states);i++) {
		//NFANode *nfaNode = (NFANode*)getByIndex(states, i, sizeof(NFANode));
		NFANode *nfaNode = (NFANode*)getByIndex(states, i);
		if(nfaNode->state == 1){
			node->state = 1;
			break;
		}
	}
}
**/

/**
void printDFANode(DFANode *node) {
	if(node == NULL) return;
	Array **<NFANode>>** *states = node->states;
	Array **<DFAEdge>** *edges = node->edges;
	int i;
	printf("%d(", node->stateNum);
	for(i=0;i<getSize(states);i++) {
		//NFANode *nfaNode = (NFANode*)getByIndex(states, i, sizeof(NFANode));
		NFANode *nfaNode = (NFANode*)getByIndex(states, i);
		printf("%d,", nfaNode->stateNum);
	}
	printf(")");
	printf("->");
	for(i=0;i<getSize(edges);i++){
		//DFAEdge *edge = (DFAEdge*)getByIndex(edges, i, sizeof(DFAEdge));
		DFAEdge *edge = (DFAEdge*)getByIndex(edges, i);
		//printf("%d,", *edge);
		printf("%c", edge->value);
		printf("->");
		DFANode *tmpNode = edge->node;
		printf("%d(", tmpNode->stateNum);
		int j;
		for(j=0;j<getSize(tmpNode->states);j++) {
			//NFANode *tmpNfaNode = (NFANode*)getByIndex(tmpNode->states, j, sizeof(NFANode));
			NFANode *tmpNfaNode = (NFANode*)getByIndex(tmpNode->states, j);
			printf("%d,", tmpNfaNode->stateNum);
		}
		printf(")");
		printf("->");
		if(tmpNode->edges != NULL) {
			printf("sizeof edges is %d", getSize(tmpNode->edges));
		} else {
			printf("NULL");
		}
		printf("\n");
	}
	printf("\n");
}
**/

void printDFANode(FANode *node, Array/**<NFANode>>**/ *states) {
	if(node == NULL) return;
	Array /**<FAEdge>**/ *edges = node->edge;
	int i;
	printf("%d(", node->stateNum);
	for(i=0;i<getSize(states);i++) {
		FANode *nfaNode = (FANode*)getByIndex(states, i);
		printf("%d,", nfaNode->stateNum);
	}
	printf(")");
	printf("->");
	for(i=0;i<getSize(edges);i++){
		FAEdge *edge = (FAEdge*)getByIndex(edges, i);
		printf("%c", edge->value);
		printf("->");
		FANode *tmpNode = edge->node;
		printf("%d(", tmpNode->stateNum);
		printf(")");
		printf("\n");
	}
	printf("\n");
}

void updateFANode(FANode *dfaNode, Array/**FANode**/ *nfaNodeAry) {
	if(dfaNode == NULL || !getSize(nfaNodeAry)) return ;
	int i;
	for(i=0;i<getSize(nfaNodeAry);i++) {
		FANode *nfaNode = (FANode*)getByIndex(nfaNodeAry, i);
		if(nfaNode->state == 1){
			dfaNode->state = 1;
			break;
		}
	}
}

FANode *nfa2DFA(FA *nfa) {
	if(nfa == NULL) {
		printf("nfa to dfa failed: nfa is null\n");
		return NULL;
	}
	int stateNum = 0;
	FANode *nfaStartNode = nfa->start;
	//nfa的初始状态值（只通过epsilon能到达的所有状态）
	Array/**FANode**/ *state0 = eclosure(nfaStartNode);
	quicksortEx(state0, 0, getSize(state0)-1);
	Array/**FANode**/ *ends = NULL;
	// 把nfaStartNode添加到数组state0里面
	FANode *dfaNode = initFANode(NULL, 0, stateNum++);
	//移动的fanode指针
	FANode *node = dfaNode;
	Array *nextDFAEdge = NULL;
	Array *nextDFANode = NULL;
	//用一个数组记录已产生的dfa状态
	Array/**<Array<FANode>>**/ *newDFAStateAry = NULL;
	Array/**<FANode>**/ *newDFANodeAry = NULL;
	//Array**<int*>** *newNFANodeAry = NULL;
	//push(&queue, dfaNode);
	add(&newDFANodeAry, node);
	//add(&newNFANodeAry, sortNFANode(state0));
	add(&newDFAStateAry, state0);
	//push(&queue, state0);
	//Element *t = top(queue);
	int n = 0;
	int size = getSize(newDFAStateAry);
	//while(t != NULL) {
	while(1) {
		printf("size=%d\n", size);
	//for(n=0;n<size;n++) {
		if(n >= size /**|| size >30**/) break;
		Array/**FANode**/ *tempStates = (Array*)getByIndex(newDFAStateAry, n);
		int u;
		printf("---print aaa---\n");
		for(u=0;u<getSize(tempStates);u++) {
			FANode *fanode = (FANode*)getByIndex(tempStates, u);
			printf("%d,", fanode->stateNum);
		}
		printf("\n");
		node = (FANode*)getByIndex(newDFANodeAry, n);
		updateFANode(node, tempStates);
		if(node->state == 1) add(&ends, node);
		//同一个节点记录读取过的字母， 避免出现一个节点有两条同一个字母的路径（DFA不允许同一个节点有两条相同的路径）
		HashMap *alphabetMap = NULL;
		int i;
		Array/**<FAEdge>**/ *dfaEdgeAry = NULL;
		for(i=0;i<getSize(tempStates);i++) {
			FANode *tempNode = (FANode*)getByIndex(tempStates, i);
			Array/**<FAEdge>**/ *tempEdges = tempNode->edge;
			int j;
			//printf("size of nfa edge is %d\n", getSize(tempEdges));
			for(j=0;j<getSize(tempEdges);j++) {
				FAEdge *e = (FAEdge*)getByIndex(tempEdges, j );
				char c = e->value;
				if(c<97 || c>122) continue;
				printf("key=%c\n", c);
				//计算由nfa节点出发经过*c（包括经过epsilon边）能到达的nfa节点
				Array *origNodes = delta(tempNode,  c);
				Array/**<FANode>**/ *ca = closure(origNodes);
				if(getSize(ca)) {
					//用快速排序优化
					//int *stateNumAry = sortNFANode(ca);
					quicksortEx(ca, 0, getSize(ca)-1);
					//Array *stateNumAry = sortNFANode(ca);
					Array/**<FANode>**/ *alphabetAry = (Array*)get(alphabetMap, c);
					if(!getSize(alphabetAry)) {
						//printf("---aaa---\n");
						put(&alphabetMap, c, ca);
						alphabetAry = ca;
					} else {
						//printf("---bbb---\n");
						//合并两数组（去重复）
						int l=0;
						int n=0;
						while(l<getSize(ca) && n<getSize(alphabetAry)) {
							FANode *valL = (FANode*)getByIndex(ca, l);
							FANode *valN = (FANode*)getByIndex(alphabetAry, n);
							if(valL->stateNum == valN->stateNum) {
								l++;
								n++;
							} else if(valL->stateNum < valN->stateNum) {
								addByIndex(&alphabetAry, valL, n);
								l++;
								n++;
							} else {
								n++;
							}
						}
						for(;l<getSize(ca);l++) {
							FANode *valL = (FANode*)getByIndex(ca, l);
							add(&alphabetAry, valL);
						}
					}

					//检查从一个nfa节点出发是否已经有相同的不是epsilon边的字母， 如果有， 就把能到达的nfa节点封装在一起
					//先把状态用快速排序算法进行排序, 然后进行比较来去重复
					int k;
					for(k=0;k<getSize(newDFAStateAry);k++) {
						Array *ary = (Array*)getByIndex(newDFAStateAry, k);
						/**
						if(getSize(ary) != getSize(alphabetAry)) {
							printf("size of ary is %d,size of alphabetAry is %d\n",getSize(ary), getSize(alphabetAry) );
							continue;
						}
**/
						//对数组进行快速排序
						//int *exsStateNumAry = (int*)getByIndex(newNFANodeAry, k);
						//Array *exsStateNumAry = (Array*)getByIndex(newDFAStateAry, k);
						int l=0;
						int m=0;
						while(l<getSize(ary) && m <getSize(alphabetAry)) {
						//for(l=0;l<getSize(ary);l++) {
							FANode *valExsist = (FANode*)getByIndex(ary, l);
							FANode *valNew = (FANode*)getByIndex(alphabetAry, m);
							//if(valNew->stateNum != valExsist->stateNum) break;
							if(valNew->stateNum == valExsist->stateNum) {
								l++;
								m++;
							} else {
								l++;
							}
						}
						if(m == getSize(alphabetAry)) {//找到已存在的dfa状态
						//if(l == getSize(ary)) {//找到已存在的dfa状态
							printf("%c has found the right dfa state\n", c);
							break;
						} 
						/**else {
							printf("%c not find the right dfa state: begin print the list\n", c);
							for(l=0;l<getSize(ary);l++) {
								FANode *valNew = (FANode*)getByIndex(alphabetAry, l);
								printf("%d,", valNew->stateNum);
							}
							printf("\n");
							for(l=0;l<getSize(ary);l++) {
								FANode *valNew = (FANode*)getByIndex(ary, l);
								printf("%d,", valNew->stateNum);
							}
							printf("\n");
							printf("end print the list\n");
						}**/
					}	
					//DFAEdge *newDFAEdge = initDFAEdge(c);
					FAEdge *newDFAEdge = initFAEdge(c);
					//DFANode *newDFANode = NULL;
					FANode *newDFANode = NULL;

					if(k == getSize(newDFAStateAry)) {//不存在该dfa节点,新建一个到达的dfa状态和一条dfa边
						//printf("---ccc---\n");
						//add(&newDFAStateAry, ca, sizeof(Array));
						//add(&newDFAStateAry, ca);

printf("---print ccc---\n");
					for(u=0;u<getSize(alphabetAry);u++) {
						FANode *fanode = (FANode*)getByIndex(alphabetAry, u);
						printf("%d,", fanode->stateNum);
					}
					printf("\n");

						add(&newDFAStateAry, alphabetAry);
						//add(&newNFANodeAry, stateNumAry);
						//newDFANode = initFANode(ca, stateNum++);
						newDFANode = initFANode(NULL, 0, stateNum++);
						newDFAEdge->node = newDFANode;
						add(&newDFANodeAry, newDFANode);
						size = getSize(newDFAStateAry);	
						//push(&queue, newDFANode);
						//push(&queue, ca);
					} else {
						//printf("---ddd---\n");
						//newDFANode = (DFANode*)getByIndex(newDFANodeAry, k);
						newDFANode = (FANode*)getByIndex(newDFANodeAry, k);
						//printf("size of nfa node in exsist dfa node  is %d\n", getSize(exsistDFANode->states));
						newDFAEdge->node = newDFANode;
					}
					add(&dfaEdgeAry, newDFAEdge);
				}
			}
			
		}
		node->edge = dfaEdgeAry;
		n++;
		//printDFANode(node, tempStates);
//		pop(&queue);
		//t = top(queue);
		//t = t->next;
	}
printf("---print newDFAStateAry---\n");
	for(n=0;n<getSize(newDFAStateAry);n++){
		Array *a = (Array*)getByIndex(newDFAStateAry,n);
		int v;
		for(v=0;v<getSize(a);v++){
			FANode* fanode = (FANode*)getByIndex(a, v);
			printf("%d,", fanode->stateNum);
		}
		printf("\n");
	}
		

	if(ends == NULL){
		printf("nfa to dfa failed: no end state in DFA\n");
	} else {
		printf("size of dfa ends array is %d\n", getSize(ends));
	}
	//dfa->ends = ends;
	//return dfa;
	return dfaNode;
}

bool isMatch(char *p, char *s) {
	FA *nfa = reg2NFA(p);
	iterateNFA(nfa);
	//DFA *dfa = nfa2DFA(nfa);
	//FA *dfa = nfa2DFA(nfa);
	//iterateDFA(dfa);
	//DFANode *node = dfa->start;
	//FANode *node = dfa->start;
	FANode *node = nfa2DFA(nfa);
	//printDFANode(node);
	char *sM = s;
	while(*sM != '\0') {
		//Array**<DFAEdge>** *edges = node->edges;
		Array/**<FAEdge>**/ *edges = node->edge;
		int i;
		for(i=0;i<getSize(edges);i++) {
			//DFAEdge *edge = (DFAEdge*)getByIndex(edges, i);
			FAEdge *edge = (FAEdge*)getByIndex(edges, i);
			if(edge->value == *sM) {
				node = edge->node;
				break;
			}
		}
		if(i == getSize(edges)) {
			break;
		}
		sM++;
	}
	if(*sM != '\0') return false;
	if(node != NULL && node->state == 1) return true;
	return false;
}

void testFA() {
	char *p = "b*.";
	FA *nfa = reg2NFA(p);
	iterateNFA(nfa);
	printf("\n");
	FA *dfa = nfa2DFA(nfa);
	//iterateDFA(dfa);
}

void test() {
	char *p = "b*.c*..*.b*b*.*c*";
	char *s = "bcaccbbacbcbcab";
	printf("result=%c\n", isMatch(p, s));

//"bcaccbbacbcbcab"
//"b*.c*..*.b*b*.*c*"
}

void testArray() {
	int a[] = {9,8,7,6,5,4,3,2,1};
	int size = sizeof(a)/sizeof(a[0]);
	int i;
	Array *array = NULL;
	for(i=0;i<size;i++) {
		Integer *it = (Integer*)malloc(sizeof(Integer));
		it->stateNum = a[i];
		add(&array, it);
	}
	printf("---before insert---\n");
	for(i=0;i<size;i++) {
		Integer *it = (Integer*)getByIndex(array, i);
		printf("%d,%d\n",*it, it->stateNum);
	}
	
	Integer *tmpIt = (Integer*)getByIndex(array, 4);
	setByIndex(array, getByIndex(array, 5), 4);
	setByIndex(array, tmpIt, 5);

	printf("---after insert---\n");
	for(i=0;i<size;i++) {
		Integer *it = (Integer*)getByIndex(array, i);
		printf("%d,%d\n",*it, it->stateNum);
	}
}



void testQuicksort() {
	int a[] = {57,56};
	int size = sizeof(a)/sizeof(a[0]);
	Array *array = NULL;
	int i;
	for(i=0;i<size;i++) {
		FANode *it = (FANode*) malloc(sizeof(FANode));
		it->stateNum = a[i];
		add(&array, it);
	}
	quicksortEx(array, 0, getSize(array)-1);
	for(i=0;i<size;i++) {
		FANode *it = (FANode*)getByIndex(array, i);
		printf("%d,", it->stateNum);
	}
	printf("\n");
}

void testMerge(){
	int b[] = {7,57};
	int a[] = {2,3,4,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58};
	int sizeA = sizeof(a)/sizeof(a[0]);
	int sizeB = sizeof(b)/sizeof(b[0]);
	Array *ca = NULL;
	Array *alphabetAry = NULL;
	int r;
	for(r=0;r<sizeA;r++) {
		FANode *node = (FANode*)calloc(1, sizeof(FANode));
		node->stateNum = a[r];
		add(&ca, node);
	}
	for(r=0;r<sizeB;r++) {
		FANode *node = (FANode*)calloc(1, sizeof(FANode));
		node->stateNum = b[r];
		add(&alphabetAry, node);
	}
	int l=0;
	int n=0;
	while(l<getSize(ca) && n<getSize(alphabetAry)) {
		FANode *valL = (FANode*)getByIndex(ca, l);
		FANode *valN = (FANode*)getByIndex(alphabetAry, n);
		if(valL->stateNum == valN->stateNum) {
			l++;
			n++;
		} else if(valL->stateNum < valN->stateNum) {
			addByIndex(&alphabetAry, valL, n);
			l++;
			n++;
		} else {
			n++;
		}
	}
	for(;l<getSize(ca);l++) {
		FANode *valL = (FANode*)getByIndex(ca, l);
		add(&alphabetAry, valL);
	}
	
	for(r=0;r<getSize(alphabetAry);r++) {
		FANode *valL = (FANode*)getByIndex(alphabetAry, r);
		printf("%d,", valL->stateNum);
	}
	printf("\n");
}

int main(void) {
	test();
//	testMap();
	//testArray();
//	testQueue();
//testQuicksort();

//testFA();

//testMerge();
//testArray();
	return 0;
}

