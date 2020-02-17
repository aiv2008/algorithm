#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define ARRAY_SIZE 10
#define bool char
#define true '1'
#define false '0'
#define MAP_SIZE 13

typedef struct {
	//状态转移边，在thompson算法中， 每个节点最多只有两条转移边
//	struct NFANode *nextEdge1;
//	struct NFANode *nextEdge2;
//	struct NFAEdge *edge1;
//	struct NFAEdge *edge2;
	int stateNum;
	struct Array/**<NFAEdge>**/ *edge;
//	char value;
	//是否为接受状态 1 是 0 否
	int state;
} NFANode;

typedef struct {
//	NFANode *in;
	struct NFANode *node;
	char value;
} NFAEdge;

typedef struct {
	struct NFANode *start;
	//注: end节点不能有任何指向其他节点的边
	struct NFANode *end;
	//记录一下字母表
	struct Array *alphabet;
} NFA;

typedef struct {
	struct Array/**<NFANode>**/ *states;
	struct Array/**<DFAEdge>**/ *edges;
	int state;
} DFANode;

typedef struct {
	struct DFANode *node;
	char value;
} DFAEdge;

typedef struct {
	struct DFANode *start;
	struct Array/**<DFANode>**/ *ends;
} DFA;

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
	int key;
	char *value;
} Entity;

typedef struct {
	struct Array/**<Entity>**/ **entity;
} HashMap;


void swap(char *a, char *b, int len) {
	char *temp = malloc(len);
	memcpy(temp, a, len);
	memcpy(a, b, len);
	memcpy(b, temp, len);
	free(temp);
	temp = NULL;
}
int myPartition(char* array, int start, int end, int len)
{
	if(array == NULL)
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
			if(*(array+len*j) <= *(array+len*end))
			{
				i++;
				if(i != j)
				{
					swap(array+len*j, array+len*i, sizeof(int));
				}
			}
			j++;
		}
		if(i+1 != end)
		{
			swap(array+len*(i+1), array+len*end, sizeof(int));
			return i+1;
		}
		else
		{
			return end;
		}

	}
	return -1;
}
void myQuicksort(char* array, int start, int end, int len)
{
	if(array == NULL)
	{
		printf("array cannot be null\n");
		return ;
	}
	if(start < end)
	{
		int partitionIndex = myPartition(array, start, end, len);
		if(partitionIndex < 0)
		{
		    printf("partitionIndex must larger than 0\n");
		    return ;
		}
		myQuicksort(array, start, partitionIndex-1, len);
		myQuicksort(array, partitionIndex+1, end, len);
	}
}

int myRandomizedPartition(char* array, int start, int end, int len)
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
	if(randIndex != end)
			swap(array+len*randIndex, array+len*end, sizeof(int));
	return myPartition(array, start, end, len);
}
void myRandomizedQuicksort(char* array, int start, int end, int len)
{
	if(array == NULL)
	{
		printf("quicksort myRandomizedQuicksort: array cannot be null\n");
		return ;
	}
	if(start < end)
	{
		int partitionIndex = myRandomizedPartition(array, start, end, len);
		if(partitionIndex < 0)
		{
		    printf("quicksort myRandomizedQuicksort: partitionIndex must larger than 0\n");
		    return ;
		}
		myRandomizedQuicksort(array, start, partitionIndex-1, len);
		myRandomizedQuicksort(array, partitionIndex+1, end, len);
	}
}

void myRandomizedQuicksortArray(Array *array, int start, int end, int len) {
	if(array == NULL || !getSize(array)) return ;
	myRandomizedQuicksort(array->val, start, end, len);
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

//遍历队列
bool TraverseQueue(Queue *queue, char *ele) {
	if(queue == NULL || ele == NULL) return false;
	bool result = false;
	Element *p = queue->top;
	while(p != NULL) {
		char *val = p->val;
		if(*val == *ele) {
			result = true;
			break;
		}
		p = p->next;
	}
	return result;
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

//把src所有元素添加到dest
void addAll(Array **dest, Array *src, int len) {
	if(dest == NULL || src == NULL) return;
	if(*dest == NULL) {
		int i;
		for(i=0;i<getSize(src);i++) {
			char *value = getByIndex(src, i, len);
			add(dest, value, len);	
		}
	}	
}

//把src所有元素添加到dest（去重复）
void addAllDist(Array **dest, Array *src, int len) {
	//先遍历两个数组， 以后优化为w二分法
	if(dest == NULL || src == NULL) return;
//	if(*dest == NULL) {
		int i;
		for(i=0;i<getSize(src);i++) {
			int j;
			char *valueI = getByIndex(src, i, len);
			for(j=0;j<getSize(*dest);j++) {
				char *valueJ = getByIndex(*dest, j, len);
				if(*valueI == *valueJ) break;
			}
			//j等于dest的size， 说明没有重复的元素
			if(j == getSize(*dest))	add(dest, valueI, len);
		}
//	}
}

int getSize(Array *array) {
	if(array == NULL) return 0;
	return array->size;
}

void sortAsc(Array *array, int len) {
	if(array == NULL) return;
	myRandomizedQuicksort(array->val, 0, getSize(array)-1, len);
}

int hashCode(int key) {
	return key % MAP_SIZE;
}

void put(HashMap **map, int key, char *value, int valueLen) {
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
		entity->value = (char*)malloc(valueLen);
		//entity->value = value;
		memcpy(entity->value, value, valueLen);
		add((*map)->entity+index, entity, sizeof(Entity));
	} else {
		Array *a = *(entityArray+index);
		int i=0;
		for(;i<getSize(a);i++) {
			Entity *entity = (Entity*)getByIndex(a, i, sizeof(Entity));
			if(entity->key == key) {
				//entity->value = value;
				memcpy(entity->value, value, valueLen);
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
		//	entity->value = value;
			entity->value = (char*)malloc(valueLen);
			memcpy(entity->value,  value, valueLen);
			add((*map)->entity+index, entity, sizeof(Entity));
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
		Entity *entity = (Entity*)getByIndex(a, i, sizeof(Entity));
		if(entity->key == key) {
			result = entity->value;
			break;
		}
	}
	return result;
}

void testMap(){
	HashMap *map = NULL;
	int a[] = {1,2,3,4,55,6};
	int b[] = {4,5,6,7,8,9,9};
	int c[] = {1,2,3,4,55,6};
	Array *arrayA = NULL;
	Array *arrayB = NULL;
	Array *arrayC = NULL;
	int i;
	for(i=0;i<sizeof(a)/sizeof(a[0]);i++) {
		add(&arrayA, &a[i], sizeof(int));
	}
	for(i=0;i<sizeof(b)/sizeof(b[0]);i++) {
		add(&arrayB, &b[i], sizeof(int));
	}
	for(i=0;i<sizeof(c)/sizeof(c[0]);i++) {
		add(&arrayC, &c[i], sizeof(int));
	}
	int origValue = 1;
	put(&map, arrayA, &origValue, sizeof(int));
	put(&map, arrayB, &origValue, sizeof(int));
	put(&map, arrayC, &origValue, sizeof(int));

	int *valueA = (int*)get(map, arrayA);
	if(valueA == NULL) {
		put(&map, arrayA, &origValue, sizeof(int));
	} else {
		int v = *valueA + 1;
		put(&map, arrayA, &v, sizeof(int));
	}
	int *valueB = (int*)get(map, arrayB);
	int *valueC = (int*)get(map, arrayC);
	valueA = (int*)get(map, arrayA);
	printf("a=%d, b=%d, c=%d\n", *valueA, *valueB, *valueC);
}

NFANode *initNFANode(Array/**<NFAEdge>**/ *edgeAry, /**NFAEdge *edge1, NFAEdge *edge2,**/ int state, int *stateNum) {
	if(state != 0x00 && state != 0x01) {
		printf("init nfa node failed: state must be 1 or 0\n");
		return NULL;
	}
	NFANode *node = (NFANode*)calloc(1, sizeof(NFANode));
	if(node == NULL) {
		printf("init nfa node failed\n");
		return NULL;
	}
//	if(edge1 != NULL) node->edge1 = edge1;
//	if(edge2 != NULL) node->edge2 = edge2;
	node->edge = edgeAry;
	node->state = state;
	node->stateNum = *stateNum;
	return node;
}

NFAEdge *initNFAEdge(char c) {
	NFAEdge *edge = (NFAEdge*)calloc(1, sizeof(NFAEdge));
	if(edge == NULL) {
		printf("init edge node failed\n");
		return NULL;
	}
	edge->value = c;
	return edge;
}

NFAEdge *initEpEdge() {
	return initNFAEdge(' ');
}

NFA *initNFA(NFANode *start, NFANode *end) {
	if(start == NULL || end == NULL) {
		printf("init nfa failed: start or end node cannot be null\n");
		return NULL;
	}
	NFA *nfa = (NFA*)malloc(sizeof(NFA));
	if(nfa == NULL) {
		printf("init nfa failed\n");
		return NULL;
	}
	nfa->start = start;
	nfa->end = end;
	return nfa;
}

void updateNFA(NFA *nfa, NFANode *start, NFANode *end) {
	if(nfa == NULL || start == NULL || end == NULL) {
		printf("update nfa failed: start or end node cannot be null\n");
		return NULL;
	}
	nfa->start = start;
	nfa->end = end;
}

NFA *symbolNFA(char c, int *stateNum) {
	NFAEdge *edge = initNFAEdge(c);
	NFANode *end = initNFANode(NULL, 1, stateNum);
	*stateNum = *stateNum + 1;
	edge->node = end;
	Array/**<NFAEdge>**/ *edgeAry = NULL;
	add(&edgeAry, edge, sizeof(NFAEdge));
//	NFANode *start = initNFANode(edge, NULL, 0);
	NFANode *start = initNFANode(edgeAry, 0, stateNum);
//	NFANode *end = initNFANode(NULL, NULL, 1);
	return initNFA(start, end);
}

NFA *epsilonNFA(int *stateNum) {
	return symbolNFA(0x20, stateNum);
}

NFA *unonNFA(NFA *nfaS, NFA *nfaT, int* stateNum) {
	if(nfaT == NULL) return nfaS;
	else if(nfaS == NULL) return nfaT;
	NFAEdge *edge1 = initEpEdge();
	NFAEdge *edge2 = initEpEdge();
	Array *edgeAry1 = NULL;
	add(&edgeAry1, edge1, sizeof(NFAEdge));
	add(&edgeAry1, edge2, sizeof(NFAEdge));
	//NFANode *start = initNFANode(edge1, edge2, 0);
	NFANode *start = initNFANode(edgeAry1, 0, stateNum);
	*stateNum = *stateNum + 1;
	NFANode *startOfS = nfaS->start;
	NFANode *startOfT = nfaT->start;
	edge1->node = startOfS;
	edge2->node = startOfT;
	NFANode *end = initNFANode(NULL, 1, stateNum);
	NFANode *endOfS = nfaS->end;
	NFANode *endOfT = nfaT->end;
	NFAEdge *edge3 = initEpEdge();
	NFAEdge *edge4 = initEpEdge();
	edge3->node = end;
	edge4->node = end;
	Array *edgeAry2 = NULL;
	Array *edgeAry3 = NULL;
	add(&edgeAry2, edge3, sizeof(NFAEdge));
	add(&edgeAry3, edge4, sizeof(NFAEdge));
	//endOfS->edge1 = edge3;
	//endOfT->edge1 = edge4;
	endOfS->edge = edgeAry2;
	endOfT->edge = edgeAry3;
//	nfaS->start = start;
//	nfaS->end = end;
//	NFA *nfa = initNFA(start, end);
	updateNFA(nfaS, start, end);
	return nfaS;
}

NFA *concatNFA(NFA *nfaS, NFA *nfaT) {
	if(nfaT == NULL) return nfaS;
	else if(nfaS == NULL) return nfaT;
	NFANode *endOfS = nfaS->end;
	NFANode *startOfT = nfaT->start;
//	endOfS->edge1 = startOfT->edge1 == NULL ? NULL : startOfT->edge1;
//	endOfS->edge2 = startOfT->edge2 == NULL ? NULL : startOfT->edge2;
	endOfS->edge = startOfT->edge;
	endOfS->state = 0;
	updateNFA(nfaS, nfaS->start, nfaT->end);
	return nfaS;
}

NFA *kleenStarNFA(NFA *nfa, int *stateNum) {
	if(nfa == NULL) return NULL;
//	NFANode *stn = nfa->start;
//	printf("print nfa node in kleen start nfa\n");
//	printNFANode(stn);
	NFANode *end = initNFANode(NULL, 1, stateNum);
	*stateNum = *stateNum + 1;
	NFAEdge *edge1 = initEpEdge();
	edge1->node = nfa->start;
	NFAEdge *edge2 = initEpEdge();
	edge2->node = end;
	NFAEdge *edge3 = initEpEdge();
	edge3->node = nfa->start;
	NFAEdge *edge4 = initEpEdge();
	edge4->node = end;
	Array/**<NFAEdge>**/ *edgeAry1 = NULL;
//	Array *edgeAry2 = NULL;
	add(&edgeAry1, edge1, sizeof(NFAEdge));
	add(&edgeAry1, edge2, sizeof(NFAEdge));
	NFANode *start = initNFANode(edgeAry1, 0, stateNum);
//	NFANode *start = initNFANode(edge1, edge2, 0);
	NFANode *endOfNFA = nfa->end;

	Array/**<NFAEdge>**/ *edgeAry2 = NULL;
	add(&edgeAry2, edge3, sizeof(NFAEdge));
//	endOfNFA->edge1 = edge3;
	add(&edgeAry2, edge4, sizeof(NFAEdge));
//	endOfNFA->edge1 = edge3;
//	endOfNFA->edge2 = edge4;
	endOfNFA->edge = edgeAry2;
	endOfNFA->state = 0;
//	updateNFA(nfa, start, end);
	NFA *result = initNFA(start, end);	
	return result;
}

NFA *unonAllNFA(int *stateNum) {
	Array/**<NFAEdge>**/ *startEdgeAry = NULL;
	NFANode *endNode = initNFANode(NULL, 1, stateNum);
	*stateNum = *stateNum + 1;
	NFAEdge *endEdge = NULL;
	NFAEdge *startEdge = NULL;
	Array/**<char>**/ *alphabet = NULL;
	int i;
	for(i=97;i<=122;i++) {
		NFA *nfa = symbolNFA(i, stateNum);
		*stateNum = *stateNum + 1;
		startEdge = initNFAEdge(' ');
		NFANode *start = nfa->start;
		startEdge->node = start;
		add(&startEdgeAry, startEdge, sizeof(NFAEdge));
		NFANode *end = nfa->end;
		endEdge = initNFAEdge(' ');
		endEdge->node = endNode;
		Array/**<NFAEdge>**/ *endEdgeAry = NULL;
		add(&endEdgeAry, endEdge, sizeof(NFAEdge));
		end->edge = endEdgeAry;
		end->state = 0;
		add(&alphabet, &i, sizeof(char));
	}
	NFANode *startNode = initNFANode(startEdgeAry, 0, stateNum);
	NFA *nfa = initNFA(startNode, endNode);
	nfa->alphabet = alphabet;
	return nfa;
}

NFA *reg2NFA(char *p) {
//	char *p = ".*";
	char *pMove = p;
	NFA *nfa = NULL;
	NFA *nfaTmp = NULL;
	HashMap *map = NULL;
	Array *array = NULL;
	int stateNum = 0;
	int origValue = 1;
	//是否已包含所有字母表里的字母， 因为当模式里含有'.'时， 即包含字母表的所有字母
	bool isAllAlphabet = false;
	while(*pMove != '\0') {
		if(*(pMove+1) == '*') {
			if(*pMove == '.') {
				nfaTmp = unonAllNFA(&stateNum);
				isAllAlphabet = true; 
				array = nfaTmp->alphabet;
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
				isAllAlphabet = true; 
				array = nfaTmp->alphabet;
			} else {
				nfaTmp = symbolNFA(*pMove, &stateNum);
			}
			stateNum++;
			nfa = concatNFA(nfa, nfaTmp);
			pMove++;
		}

		if(isAllAlphabet == false && *p>=97 && *p<=122) {
			int *value = (int*)get(map, *p);
			if(value == NULL) {
				put(&map, *p, &origValue, sizeof(int));
				add(&array, p, sizeof(char));
			}
		}
		nfaTmp = NULL;
	}
	nfa->alphabet = array;
	return nfa;
}

Array *delta(NFANode *node, char value) {
	if( node == NULL) {
		printf("delta function failed: nfa node is null\n");
		return NULL;
	}
	Array *dfaStates = NULL;
	Array *edgeAry = node->edge;
	int i;
	for(i=0;i<getSize(edgeAry);i++) {
		NFAEdge *edge = (NFAEdge*)getByIndex(edgeAry, i, sizeof(NFAEdge));
		if(edge != NULL) {
			if(edge->value == value) {
				add(&dfaStates, edge->node, sizeof(NFANode));
			}	
		}
	}
//	sortAsc(dfaStates, sizeof(NFANode));
	return dfaStates;
}

//从node出发，只通过epsilon边能到达的节点， 但不包括node本身
Array *eclosure(NFANode *node) {
	if(node == NULL) {
		printf("eclosure function failed: nfa node is null\n");
		return NULL;
	}
	Array *dfaStates = NULL;
	Queue *queue = NULL;
	HashMap *map = NULL;
	NFANode *pMove = node;
	push(&queue, pMove);
	Element *t = top(queue);
	int origValue = 1;
	while(t != NULL) {
		pMove = (NFANode*)(t->val);
//		if(pMove->state== 1) {
//			printf("reach the final state\n");
//		}
		if(pMove != NULL) {
			Array *edgeAry = pMove->edge;
	//		printf("size of edgeAry is %d\n", getSize(edgeAry));
			int i;
			for(i=0;i<getSize(edgeAry);i++) {
				NFAEdge *edge = (NFAEdge*)getByIndex(edgeAry, i, sizeof(NFAEdge));
				if(edge != NULL && edge->value ==' ' && edge->node != NULL) {
					int *value = (int*)get(map, edge->node);
					if(value == NULL) {
						put(&map, edge->node, &origValue, sizeof(int));
						push(&queue, edge->node);
						add(&dfaStates, edge->node, sizeof(NFANode));
					}				
				}
			}
		}
		pop(&queue);
		t = top(queue);
	}
//	sortAsc(dfaStates, sizeof(NFANode));
	return dfaStates;
}

Array *closure(Array/**<NFANode>**/ *nodes) {
	if(nodes == NULL) return NULL;
	int i;
	Array *result = NULL;
	for(i=0;i<getSize(nodes);i++) {
		NFANode *node = (NFANode*)getByIndex(nodes, i, sizeof(NFANode));
		Array *a = eclosure(node);
		if(a != NULL) 
			addAllDist(&result, a, sizeof(NFANode));
	}
//	sortAsc(result, sizeof(NFANode));
	return result;
}

void printNFANode(NFANode *node) {
	if(node == NULL) {
		printf("print dfa node failed: node is null\n");
		return;
	}
	printf("---begin print nfa node---\n");
	printf("start node=%d\n",node->stateNum);
//	printf("*node=%d\n", *node);
	Array *edgeAry = node->edge;
	int i;
	for(i=0;i<getSize(edgeAry);i++) {
		NFAEdge *edge = (NFAEdge*)getByIndex(edgeAry, i, sizeof(NFAEdge));
		if(edge == NULL) {
			printf("edge is null\n");
		}else {
			//printf("edge address=%p,", edge);
			if(edge->value == ' ') {
				printf("edge value=epsilon\n");
			} else {
				printf("edge value=%c\n", edge->value);
			}
			printf("end node=%d\n", ((NFANode*)(edge->node))->stateNum);
		}
	}
	printf("---end print nfa node---\n");
}

void iterateNFA(NFA *nfa) {
	if(nfa == NULL) {
		printf("iterate nfa failed: nfa is null\n");
		return;
	}
	Queue *queue = NULL;
	HashMap  *map = NULL;
	NFANode *start = nfa->start;
	push(&queue, start);
	Element *t = top(queue);
	int origValue = 1;
	while(t != NULL) {
		NFANode *node = (NFANode*)(t->val);
		printNFANode(node);
		Array *edgeAry = node->edge;
		int i;
		for(i=0;i<getSize(edgeAry);i++) {
			NFAEdge *edge = (NFAEdge*)getByIndex(edgeAry, i, sizeof(NFAEdge));
			if(edge != NULL && edge->node != NULL) {
				printf("edge->value=%c, edge->node=%d\n",edge->value, ((NFANode*)(edge->node))->stateNum);
				int *value = (int*)get(map, edge->node);
				if(value == NULL) {
					put(&map, edge->node, &origValue, sizeof(int));
					push(&queue, edge->node);
				}
			}
		}
		pop(&queue);
		t = top(queue);
	}
}

DFAEdge *initDFAEdge(char c) {
	DFAEdge *edge = (DFAEdge*)calloc(1, sizeof(DFAEdge));
	if(edge == NULL) {
		printf("init DFA edge node failed\n");
		return NULL;
	}
	edge->value = c;
	return edge;
}


DFANode *initDFANode(Array/**<NFANode>**/ *states) {
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
	//node->edges = edges;
	node->state = 0;
	int i;
	for(i=0;i<getSize(states);i++) {
		NFANode *nfaNode = (NFANode*)getByIndex(states, i, sizeof(NFANode));
		if(nfaNode->state == 1) {
			node->state = 1;
			break;
		}
	}
	return node;
}

void updateDFANodeState(DFANode *node) {
	if(node == NULL) return;
	Array *states = node->states;
	int i;
	for(i=0;i<getSize(states);i++) {
		NFANode *nfaNode = (NFANode*)getByIndex(states, i, sizeof(NFANode));
		if(nfaNode->state == 1){
			node->state = 1;
			break;
		}
	}
}

void printDFANode(DFANode *node) {
	if(node == NULL) return;
	Array /**<NFANode>>**/ *states = node->states;
	Array /**<DFAEdge>**/ *edges = node->edges;
	int i;
	printf("print nfa nodes:\n");
	for(i=0;i<getSize(states);i++) {
		//Array /**<NFANode>**/ *nfaNodesAry = (Array*)getByIndex(states, i, sizeof(NFANode));
		//int j;
		//for(j=0;j<getSize(nfaNodesAry);j++) {
			NFANode *nfaNode = (NFANode*)getByIndex(states, i, sizeof(NFANode));
			printf("%d,", nfaNode->stateNum);
		//}
		printf("\n");
	}
	printf("print dfa edges:\n");
	for(i=0;i<getSize(edges);i++){
		DFAEdge *edge = (DFAEdge*)getByIndex(edges, i, sizeof(DFAEdge));
		printf("%c,", edge->value);
	}
	printf("\n");
}

//比较两个已经排序的array数组
bool compare2SortedArray(Array *a, Array *b, int len){
	if(!getSize(a) && !getSize(b)) return true;
	if(getSize(a) != getSize(b)) return false;
	int i;
	for(i=0;i<getSize(a);i++) {
		char *aEntity = getByIndex(a, i, len);
		char *bEntity = getByIndex(b, i, len);
		if(*aEntity != *bEntity) break;
	}
	if(i != getSize(a)) return false;
	else return true;
}

DFA *nfa2DFA(NFA *nfa) {
	if(nfa == NULL) {
		printf("nfa to dfa failed: nfa is null\n");
		return NULL;
	}
	int stateNum = 0;
	//nfa的字母表
	Array *alphabet = nfa->alphabet;
	NFANode *nfaStartNode = nfa->start;
//	printNFANode(nfaStartNode);
	//nfa的初始状态值（只通过epsilon能到达的所有状态）
	Array *state0 = eclosure(nfaStartNode);
	// 把nfaStartNode添加到数组state0里面
	add(&state0, nfaStartNode, sizeof(NFANode));
	printf("after size of state0 array is %d\n", getSize(state0));
	DFANode *dfaNode = initDFANode(state0);
	DFA *dfa = (DFA*)calloc(1, sizeof(DFA));
	//dfa的初始状态
	printDFANode(dfaNode);
//	return NULL;
	dfa->start = dfaNode;
	Array *ends = NULL;
	if(dfaNode->state == 1) {
		add(&ends, dfaNode, sizeof(DFANode));
	}	
	Queue *queue = NULL;
	Array *nextDFAEdge = NULL;
	Array *nextDFANode = NULL;
	//用一个数组记录已产生的dfa状态
	Array *newDFAStateAry = NULL;
	push(&queue, dfaNode);
	Element *t = top(queue);
	int origValue = 1;
	while(t != NULL) {
		DFANode *node = (DFANode*)(t->val);
		Array/**<NFANode>**/ *tempStates = node->states;
		int i;
		for(i=0;i<getSize(tempStates);i++) {
			NFANode *tempNode = (NFANode*)getByIndex(tempStates, i, sizeof(NFANode));
			Array/**<NFAEdge>**/ *tempEdges = tempNode->edge;
			Array/**<DFAEdge>**/ *dfaEdgeAry = NULL;
			int j;
			for(j=0;j<getSize(tempEdges);j++) {
				char *c = getByIndex(tempEdges, j, sizeof(char));
				if(*c<97 || *c>122) continue;
				//计算由nfa节点出发经过*c（包括经过epsilon边）能到达的nfa节点
				Array/**<NFANode>**/ *ca = closure(delta(tempNode,  *c));
				if(ca != NULL) {
					//检查从一个nfa节点出发是否已经有相同的不是epsilon边的字母， 如果有， 就把能到达的nfa节点封装在一起
					//先把状态用快速排序算法进行排序, 然后进行比较来去重复
					int k;
					HashMap *map = NULL;
					for(k=0;k<getSize(ca);k++){
						NFANode *nfaNode = (NFANode*)getByIndex(ca, k, sizeof(NFANode));
						put(&map, nfaNode->stateNum, nfaNode, sizeof(NFANode));
					}

					for(k=0;k<getSize(newDFAStateAry);k++) {
						Array *ary = (Array*)getByIndex(newDFAStateAry, k, sizeof(Array));
						int l;
						for(l=0;l<getSize(ary);l++) {
							NFANode *nfaNode = (NFANode*)getByIndex(ary, l, sizeof(NFANode));
							if(get(map, nfaNode->stateNum) == NULL) {
								break;
							}
						}
						if(l != getSize(ary)) break;
					}
					

/**
					sortAsc(ca, sizeof(NFANode));
					int k;
					for(k=0;k<getSize(newDFAStateAry);k++) {
						Array *ary = (Array*)getByIndex(newDFAStateAry, k, sizeof(Array));
						bool b = compare2SortedArray(ca, ary, sizeof(NFANode));
						if(b == true) //找到已存在的dfa状态
							break;
					}
**/
					if(k == getSize(newDFAStateAry)) {//新建一个到达的dfa状态和一条dfa边
						add(&newDFAStateAry, ca, sizeof(Array));
						DFANode *newDFANode = initDFANode(ca);
						DFAEdge *newDFAEdge = initDFAEdge(*c);
						newDFAEdge->node = newDFANode;
						add(&dfaEdgeAry, newDFAEdge, sizeof(DFAEdge));
						push(&queue, newDFANode);
					}

				}
			}
			node->edges = dfaEdgeAry;
		}
		pop(&queue);
		t = top(queue);
	}
	if(ends == NULL){
	//	printf("nfa to dfa failed: no end state in DFA\n");
	//	return NULL;
	}
	dfa->ends = ends;
	return dfa;
}

void iterateDFA(DFA *dfa) {
	if(dfa == NULL) return;
	Queue *queue = NULL;
	push(&queue, dfa->start);
	Element *t = top(queue);
	while(t != NULL) {
		DFANode *node = (DFANode*)(t->val);
		Array *states = node->states;
		Array *edges = node->edges;
		int i;
		for(i=0;i<getSize(edges);i++) {
			DFAEdge *edge = (DFAEdge*)getByIndex(edges, i, sizeof(DFAEdge));
			Array *state = (Array*)getByIndex(states, i, sizeof(Array));
			printf("edge=%c,", edge->value);
			int j;
			printf("state={");
			for(j=0;j<getSize(state);j++) {
				NFANode *n = (NFANode*)getByIndex(state, j, sizeof(NFANode));
				printf("%d,", n->state);
			}
			printf("}\n");
			if(edge->node != NULL) {
				push(&queue, edge->node);
			}
		}
		pop(&queue);
		t = top(queue);
	}
}

void test() {
	char *p = "a*";
	NFA *nfa = reg2NFA(p);
//	NFANode *start = nfa->start;
//	printf("print start node\n");
//	printNFANode(start);
//	NFANode *end = nfa->end;
//	printf("end node is %p, state is %d\n",end, end->state);
	iterateNFA(nfa);
//	printf("size of alphabet is %d\n", getSize(nfa->alphabet));
	DFA *dfa = nfa2DFA(nfa);
//	iterateDFA(dfa);
}

typedef struct {
	int val;
	struct Array *array;
} Integer;

void testQueue() {
		/**
	int a[] = {9,8,7,6,5,4,3,2,1};
	int b[]	= {2,4,6,8,10};
	Array *arrayA = NULL;
	Array *arrayB = NULL;
	int i;
	for(i=0;i<sizeof(a)/sizeof(a[0]);i++) {
		add(&arrayA, &a[i], sizeof(int));
	}
	for(i=0;i<sizeof(b)/sizeof(b[0]);i++) {
		add(&arrayB, &b[i], sizeof(int));
	}
	printf("print array a:\n");
	for(i=0;i<getSize(arrayA);i++) {
		int *value = (int*)getByIndex(arrayA, i, sizeof(int));
		printf("%d,", *value);
	}
	printf("\nprint array b:\n");
	for(i=0;i<getSize(arrayB);i++) {
		int *value = (int*)getByIndex(arrayB, i, sizeof(int));
		printf("%d,", *value);
	}
	printf("\n");
	Queue *queue  = NULL;
	push(&queue, arrayA);
	push(&queue, arrayB);
	Element *t = top(queue);
	while(t != NULL) {
		Array *tmpArray = (Array*)(t->val);
		for(i=0;i<getSize(tmpArray);i++) {
			int *value = (int*)getByIndex(tmpArray, i, sizeof(int));
			printf("%d,", *value);
		}
		printf("\n");
		pop(&queue);
		t = top(queue);
	}
	**/

	Integer *i_1 = (Integer*)malloc(sizeof(Integer));
	Integer *i_2 = (Integer*)malloc(sizeof(Integer));
	i_1->val = 1;
	i_2->val = 2;
	Queue *queue = NULL;
//	push(&queue, i_1);
	push(&queue, i_2);

	bool b = TraverseQueue(queue, i_1) ;
	printf("%c\n", b);
	b = TraverseQueue(queue, i_2) ;
	printf("%c\n", b);
}

void testArray() {
	int a[] = {9,8,7,6,5,4,3,2,1};
	int b[]	= {2,4,6,8,10};
	Array *arrayA = NULL;
	Array *arrayB = NULL;
	int i;
	for(i=0;i<sizeof(a)/sizeof(a[0]);i++) {
		add(&arrayA, &a[i], sizeof(int));
	}
	for(i=0;i<sizeof(b)/sizeof(b[0]);i++) {
		add(&arrayB, &b[i], sizeof(int));
	}
	printf("print array a:\n");
	for(i=0;i<getSize(arrayA);i++) {
		int *value = (int*)getByIndex(arrayA, i, sizeof(int));
		printf("%d,", *value);
	}
	printf("\nprint array b:\n");
	for(i=0;i<getSize(arrayB);i++) {
		int *value = (int*)getByIndex(arrayB, i, sizeof(int));
		printf("%d,", *value);
	}
	printf("\n");
	addAllDist(&arrayA, arrayB, sizeof(int));
	printf("print array a:\n");
	printf("size of array a is: %d\n", getSize(arrayA));
	for(i=0;i<getSize(arrayA);i++) {
		int *value = (int*)getByIndex(arrayA, i, sizeof(int));
		printf("%d,", *value);
	}
	printf("\n");
}

int main(void) {
	test();
//	testMap();
//	testArray();
//	testQueue();

	return 0;
}

