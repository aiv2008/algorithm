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
	char *value;
	struct FANode *node;
} FAEdge;

typedef struct {
	struct FANode *start;
	struct FANode *end;
	//记录所有状态
	struct Array /**FANode**/ *nodeAry;
	struct Array /**char(alphabet)**/ *alphabetAry;
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
	char *data;
	struct Node *next;
} Node;

typedef struct {
	struct Node *head;
	struct Node *tail;
	struct Node *move;
} List;

typedef struct {
	int key;
	char *value;
} Entity;

typedef struct {
	struct Array/**<Entity>**/ **entity;
} HashMap;

typedef struct {
	char *key;
	char *value;
} Mapper;

/**
typedef struct {
	int stateNum;
} Integer;
**/

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
	//Integer *valR = (Integer*)getByIndex(array, r);
	int *valR = (int*)getByIndex(array, r);
	int i = p - 1;
	int j;
	for(j=p;j<r;j++) {
		//Integer *valJ = (Integer*)getByIndex(array, j);
		int *valJ = (int*)getByIndex(array, j);
		//if(valJ->stateNum <= valR->stateNum) {
		if(*valJ <= *valR) {
			i++;
			//printf("--before---\n");
			//Integer *valI = (Integer*)getByIndex(array, i);
			int *valI = (int*)getByIndex(array, i);
			//printf("i=%d, j=%d, ival=%d, jval=%d\n",i,j, *valI, *valJ);
			//Integer *valTmp = valI;
			int *valTmp = valI;
			setByIndex(array, valJ, i);
			setByIndex(array, valTmp, j);
			valTmp = NULL;
			//swap(valI, valJ);
			//printf("--after---\n");
			//printf("i=%d, j=%d\n", *valI, *valJ);
		}
	}
	//printf("%d\n", i+1);
	//Integer *valIP1 = (Integer*)getByIndex(array, i+1);
	int *valIP1 = (int*)getByIndex(array, i+1);
	//Integer *valTmp = valIP1;
	int *valTmp = valIP1;
	setByIndex(array, valR, i+1);
	setByIndex(array, valTmp, r);
	valTmp = NULL;
	//swap(valIP1, valR);
	/**
	int n;
	for(n=0;n<getSize(array);n++ ){
		//Integer *val = (Integer*)getByIndex(array, n);
		int *val = (int*)getByIndex(array, n);
		printf("%d,", *val);
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

void insert(List **list, void *data) {
	if(list == NULL) return ;
	if(*list == NULL) {
		*list = (List*)calloc(1, sizeof(List));
	}
	Node *head = (Node*)calloc(1, sizeof(Node));
	head->data = data;
	head->next = NULL;
	if((*list)->head == NULL) {
		(*list)->head = head;
		(*list)->tail = head;
		(*list)->move = head;
	} else {
		((Node*)((*list)->tail))->next = head;
		(*list)->tail = head;
	}
	head = NULL;
}

Node *next(List *list) {
	if(list == NULL) return NULL;
	Node *this = list->move;
	if(this == NULL) return NULL;
	list->move = this->next;
	return this;	
}

Node *getHead(List *list) {
	if(list == NULL) return NULL;
	return list->head;
}

Node *getTail(List *list) {
	if(list == NULL) return NULL;
	return list->tail;
}

//重置move指针
void reset(List *list) {
	if(list == NULL) return;
	list->move = list->head;
}

/**
void delete(List *list) {
	if(list == NULL) return ;
	
}
**/

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

void addAll(Array **src, Array *dest) {
	if(src == NULL) return;
	if( !getSize(dest)) return;
	int i;
	for(i=0;i<getSize(dest);i++) {
		add(src, getByIndex(dest, i));
	}
}


int indexOf(Array *array, char *val) {
	if(array == NULL || val == NULL) return -1;
	int result = -1;
	int i;
	for(i=0;i<getSize(array);i++) {
		char *elem = getByIndex(array, i);
		if(*elem == *val) {
			result = i;
			break;
		} 
	}
	return result;
}

Array *subArray(Array *array, int start, int end) {
	if(array == NULL) return NULL;
	if(start >= getSize(array) || end < 0 || end < start) {
		printf("subArray error: index is out of bound\n");
		return NULL;
	}
	Array *result = NULL;
	int i;
	for(i=start;i<=end;i++) {
		add(&result, getByIndex(array, i));
	}
	return result;
}

void removeByIndex(Array *array, int index) {
	if(array == NULL) return;
	if(index >= getSize(array)) {
		printf("removeByIndex: index is out of bound\n");
		return;
	}
	int i;
	for(i=index;i<getSize(array);i++) {
		if(index == getSize(array)-1) {
			free(*(array->val+i));
			*(array->val+i) = NULL;
		} else {
			*(array->val+i) = *(array->val+i+1);
		}
	}
	array->size--;
}

int getSize(Array *array) {
	if(array == NULL) return 0;
	return array->size;
}

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

FAEdge *initFAEdge(char* c) {
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
	return initFAEdge(NULL);
}

void updateFA(FA *fa, FANode *start, FANode *end) {
	if(fa == NULL || start == NULL || end == NULL) {
		printf("update fa failed: start or end node cannot be null\n");
		return NULL;
	}
	fa->start = start;
	fa->end = end;
}

FA *symbolFA(char *c, int *stateNum) {
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
	return symbolFA(NULL, stateNum);
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
	char *c = NULL;
	for(i=97;i<=122;i++) {
		char cVal = (char)i;
		c = malloc(sizeof(char));
		if(c == NULL) {
			printf("unonAllFA: char malloc failed\n");
			return NULL;
		}
		memcpy(c, &cVal, sizeof(char));
		FA *fa = symbolFA(c, stateNum);
		c = NULL;
		*stateNum = *stateNum + 1;
		//startEdge = initFAEdge(NULL);
		startEdge = initEpEdge();
		FANode *start = fa->start;
		startEdge->node = start;
		add(&startEdgeAry, startEdge);
		FANode *end = fa->end;
		//endEdge = initFAEdge(NULL);
		endEdge = initEpEdge();
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
				nfaTmp = symbolFA(pMove, &stateNum);
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
				nfaTmp = symbolFA(pMove, &stateNum);
			}
			stateNum++;
			nfa = concatFA(nfa, nfaTmp);
			pMove++;
		}
		nfaTmp = NULL;
	}
	return nfa;
}

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
			if(*edge->value == value) {
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
				if(edge != NULL && edge->value ==NULL && edge->node != NULL) {
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

void printFANode(FANode *node) {
	if(node == NULL) {
		printf("print dfa node failed: node is null\n");
		return;
	}
	//printf("---begin print nfa node---\n");
	//printf("%d->",node->stateNum);
	Array *edgeAry = node->edge;
	int i;
	for(i=0;i<getSize(edgeAry);i++) {
		printf("%d(%d)->",node->stateNum, node->state);
		FAEdge *edge = (FAEdge*)getByIndex(edgeAry, i);
		if(edge->value == NULL) {
			printf("epsilon->");
		} else {
			printf("%c->", *edge->value);
		}
		FANode *dest = edge->node;
		printf("%d(%d)\n", dest->stateNum, dest->state);
//		printf("\n");
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
		Array *edgeAry = node->edge;
		int i;
		for(i=0;i<getSize(edgeAry);i++) {
			FAEdge *edge = (FAEdge*)getByIndex(edgeAry, i);
			printf("%d->",node->stateNum);
			if(edge->value == NULL) {
				printf("epsilon->");
			} else {
				printf("%c->", *edge->value);
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
		printf("%c", *edge->value);
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
/**
DFA *initDFA(FANode *start, FANode *end) {
	DFA *fa = (DFA*)malloc(sizeof(DFA));
	if(fa == NULL) {
		printf("initDFA failed: malloc fa error\n");
		return NULL;
	}
	fa->start = start;
	fa->end = end;
	return fa;
}
**/
FA *nfa2DFA(FA *nfa) {
	if(nfa == NULL) {
		printf("nfa to dfa failed: nfa is null\n");
		return NULL;
	}
/**
	printf("---begin print nfa end states---\n");
	FANode *end = nfa->end;
	printf("%d\n", end->stateNum);
	printf("---end print nfa end states---\n");
**/
	int stateNum = 0;
	FANode *nfaStartNode = nfa->start;
	//nfa的初始状态值（只通过epsilon能到达的所有状态）
	Array/**FANode**/ *state0 = eclosure(nfaStartNode);
	quicksortEx(state0, 0, getSize(state0)-1);
	Array/**FANode**/ *ends = NULL;
	// 把nfaStartNode添加到数组state0里面
	FANode *dfaNode = initFANode(NULL, 0, stateNum++);
	FA *fa = initFA(dfaNode, NULL) ;
	//DFA *fa = initDFA(dfaNode, NULL);
	//移动的fanode指针
	FANode *node = dfaNode;
	Array *nextDFAEdge = NULL;
	Array *nextDFANode = NULL;
	//用一个数组记录已产生的dfa状态
	Array/**<Array<FANode>>**/ *newDFAStateAry = NULL;
	Array/**<FANode>**/ *newDFANodeAry = NULL;
	add(&newDFANodeAry, node);
	//add(&newNFANodeAry, sortNFANode(state0));
	add(&newDFAStateAry, state0);
	int n = 0;
	int size = getSize(newDFAStateAry);
	Array /**char**/ *alphabetCharAry = NULL;
	int orgiVal = 1;
	HashMap *letterMap = NULL;
	while(1) {
		//printf("size=%d\n", size);
		if(n >= size ) break;
		Array/**FANode**/ *tempStates = (Array*)getByIndex(newDFAStateAry, n);
/**
		printf("---begin print nfa states in dfa\n");	
		int u;
		for(u=0;u<getSize(tempStates);u++) {
			FANode *fanode = (FANode*)getByIndex(tempStates, u);
			printf("%d,", fanode->stateNum);
		}
		printf("\n");
		printf("---end print nfa states in dfa\n");	
		printf("\n");
**/		
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
			for(j=0;j<getSize(tempEdges);j++) {
				FAEdge *e = (FAEdge*)getByIndex(tempEdges, j );
				char *c = e->value;
				if(c == NULL || *c<97 || *c>122) continue;
				int *cVal = (int*)get(letterMap, *c);
				if(cVal == NULL) {
					put(&letterMap, *c, &orgiVal );
					char *pc = malloc(sizeof(char));
					memcpy(pc, c, sizeof(char));
					add(&alphabetCharAry, pc);
				}
				//计算由nfa节点出发经过*c（包括经过epsilon边）能到达的nfa节点
				Array *origNodes = delta(tempNode,  *c);
				Array/**<FANode>**/ *ca = closure(origNodes);
				if(getSize(ca)) {
					//用快速排序优化
					//int *stateNumAry = sortNFANode(ca);
					quicksortEx(ca, 0, getSize(ca)-1);
					//Array *stateNumAry = sortNFANode(ca);
					Array/**<FANode>**/ *alphabetAry = (Array*)get(alphabetMap, *c);
					if(!getSize(alphabetAry)) {
						//printf("---aaa---\n");
						put(&alphabetMap, *c, ca);
						alphabetAry = ca;
					} else {
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
						//当从同一个节点出发出现两条相同的边，则把新的节点里的nfa节点合并的旧的nfa节点里，不需要进行下面的是否重复节点的检查
						continue;
					}

					//检查从一个nfa节点出发是否已经有相同的不是epsilon边的字母， 如果有， 就把能到达的nfa节点封装在一起
					int k;
					for(k=0;k<getSize(newDFAStateAry);k++) {
						Array *ary = (Array*)getByIndex(newDFAStateAry, k);
						//这里判断是否添加新节点的原则是，如果旧的dfa节点里的nfa节点包含了新dfa节点里的所有nfa节点，则判断认为该新dfa节点已存在，不添加（判断依据是最大匹配）
						int l=0;
						int m=0;
						while(l<getSize(ary) && m <getSize(alphabetAry)) {
							FANode *valExsist = (FANode*)getByIndex(ary, l);
							FANode *valNew = (FANode*)getByIndex(alphabetAry, m);
							if(valNew->stateNum == valExsist->stateNum) {
								l++;
								m++;
							} else {
								l++;
							}
						}
						if(m == getSize(alphabetAry)) {//找到已存在的dfa状态
							printf("%c has found the right dfa state\n", *c);
							break;
						} 
					}	
					//DFAEdge *newDFAEdge = initDFAEdge(c);
					FAEdge *newDFAEdge = initFAEdge(c);
					//DFANode *newDFANode = NULL;
					FANode *newDFANode = NULL;

					if(k == getSize(newDFAStateAry)) {//不存在该dfa节点,新建一个到达的dfa状态和一条dfa边
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
	}
	fa->alphabetAry = alphabetCharAry;	
	if(ends == NULL){
		printf("nfa to dfa failed: no end state in DFA\n");
	} else {
		printf("size of dfa ends array is %d\n", getSize(ends));
	}
	fa->nodeAry = newDFANodeAry;
	return fa;
	//return dfaNode;
}

bool isMatch(char *p, char *s) {
	FA *nfa = reg2NFA(p);
	//FANode *node = nfa2DFA(nfa);
	//FA *dfa = nfa2DFA(nfa);
	FA *dfa = nfa2DFA(nfa);
	minimalDFA(dfa);
	FANode *node = dfa->start;
	char *sM = s;
	while(*sM != '\0') {
		Array/**<FAEdge>**/ *edges = node->edge;
		int i;
		for(i=0;i<getSize(edges);i++) {
			FAEdge *edge = (FAEdge*)getByIndex(edges, i);
			if(*edge->value == *sM) {
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

void iterateDFA(FANode *node) {
	if(node == NULL) return;
	//FANode *faNode = node;
	Array /**FANode**/ *nodeAry = NULL;
	add(&nodeAry, node);
	int i=0;
	while(1) {
		if(i>=getSize(nodeAry)) break;
		//printf("i=%d, size of nodeAry is %d\n", i, getSize(nodeAry));
		FANode *faNode = (FANode*)getByIndex(nodeAry, i++);
		Array /**FAEdge**/ *edgeAry = faNode->edge; 
		int l;
		for(l=0;l<getSize(edgeAry);l++) {
			FAEdge *edge = (FAEdge*)getByIndex(edgeAry, l);
			printf("%d(%d)->%c->", faNode->stateNum, faNode->state, *edge->value);
			if(edge->node == NULL) {
				printf("epsilon");
			} else {
				FANode *destNode = edge->node;
				printf("%d(%d)", destNode->stateNum, destNode->state);
				int j;
				int k=0;
				for(j=0;j<getSize(nodeAry);j++,k++) {
					FANode *tmpNode = (FANode*)getByIndex(nodeAry, j);
					if(tmpNode->stateNum == destNode->stateNum) break;
					else if(tmpNode->stateNum > destNode->stateNum) {
						k = getSize(nodeAry);
						break;
					}
				}
				if(k == getSize(nodeAry)) {
					//printf("\n---add---\n");
					//printf("size=%d,j=%d\n",getSize(nodeAry), j);
					addByIndex(&nodeAry, destNode, j);
				}				
			}
			printf("\n");
		}
	}
}

FANode *move(FANode *node, char c) {
	if(node == NULL) {
		printf("move function error: node is null\n");
		return NULL;
	}
	FANode *result = NULL;
	Array /**FAEdge**/ *edgeAry = node->edge;
	int i;
	for(i=0;i<getSize(edgeAry);i++) {
		FAEdge *edge = (FAEdge*)getByIndex(edgeAry, i);
		if(*edge->value == c) {
			result = edge->node;
		}
	}
	return result;
}

//compare two sorted array
bool compareTo(Array *a, Array *b) {
	if(a == NULL && b == NULL) return true;
	else if(getSize(a) != getSize(b)) return false;
	else {
		int i=0;
		while(i < getSize(a)) {
			int *aI = (int*)getByIndex(a, i);
			int *bI = (int*)getByIndex(b, i);
			if(*aI != *bI) break;
			i++;	
		}
		if(i != getSize(a))return false;
		else return true;
	}
}

void printNodeAryAry(Array *array) {
	printf("---begin pring node array array--\n");
	int i;
	for(i=0;i<getSize(array);i++) {
		Array *a = (Array*)getByIndex(array, i);
		if(!getSize(a)){
			printf("node array is 0\n");
			continue;
		}
		int j;
		for(j=0;j<getSize(a);j++) {
			FANode *node = (FANode*)getByIndex(a, j);
			if(node == NULL) printf("node is null,");
			else printf("%d,", node->stateNum);	
		}
		printf("\n");
	}
	printf("---end pring node array array--\n");
}

/**
 * 该方法输入的是一个fanode数组， 输出是一个fanode数组的数组
 * **/
Array/**Array<FANode>**/ *recursion(Array *nodeAry, Array *letterAry, int j, Array *nodeAryAry) {
	//printNodeAryAry(nodeAryAry);
	if(j >= getSize(letterAry) || getSize(nodeAry) < 2){
/**
		int i;
		printf("--printf return array---\n");
		for(i=0;i<getSize(nodeAry);i++) {
			FANode *node  = (FANode*)getByIndex(nodeAry, i);
			printf("%d,", node->stateNum);
		}
		printf("\n\n");
**/
		Array *result = NULL;
		add(&result, nodeAry);
		return result;
	}
//通过move函数把fanode能到达的状态找出来， 然后查出该状态属于哪个状态集里
		Array *destAry = NULL;
		int i;
		for(i=0;i<getSize(nodeAry);i++) {
			//Aray *srcAry = (Element*)(t->val);
			char *c = getByIndex(letterAry, j);
			FANode *src = (FANode*)getByIndex(nodeAry, i);
			FANode *dest = move(src, *c);
			Mapper *mapper = (Mapper*)malloc(sizeof(Mapper));
			if(mapper == NULL) {
				printf("mapper malloc failed\n");
				return;
			}
			Array *keyAry = NULL;
			Array *valAry = NULL;
			add(&keyAry, src);
			mapper->key = keyAry;
			if(dest == NULL) add(&valAry, dest);
			else {
				int l;
				for(l=0;l<getSize(nodeAryAry);l++) {
					Array *tmpAry = (Array*)getByIndex(nodeAryAry, l);
					int index = indexOf(tmpAry, dest);
					if(index > -1) {
						add(&valAry, tmpAry);
						break;
					}
				}
			}
			mapper->value = valAry;
			add(&destAry, mapper);
		}
		//把重复的状态归纳到一个状态集里， 例如：move(0,'a')=1, move(1,'a')=1, move(2,'a')=3, 则把{0,1}归纳到一齐
		int k=0;
		int kSize = getSize(destAry);
		int lSize = kSize;
		while(k<kSize){
			Mapper *kMapper = (Mapper*)getByIndex(destAry, k);
			int l=k+1;
			while(l<lSize) {
				Mapper *lMapper = (Mapper*)getByIndex(destAry, l);
				if(!getSize(kMapper->value) && !getSize(lMapper->value)) {
					Array *kAry = (Array*)(kMapper->key);
					addAll(&kAry, (Array*)(lMapper->key)); 
/**
					int r ;
					printf("---print k array---\n");
					for(r=0;r<getSize(kAry);r++) {
						FANode *nd = (FANode*)getByIndex(kAry, r);
						if(nd==NULL) printf("node is null,");
						else printf("%d,", nd->stateNum);
					}
					printf("\n");
**/
					removeByIndex(destAry, l);
					kSize = getSize(destAry);
					lSize = kSize;
				} else if(getSize(kMapper->value) && getSize(lMapper->value)) {
					Array *kAry = (Array*)(kMapper->value);
					Array *lAry = (Array*)(lMapper->value);
					FANode *kN = (FANode*)getByIndex(kAry, 0);
					FANode *lN = (FANode*)getByIndex(lAry, 0);
					if((kN == NULL && lN == NULL) || (kN != NULL && lN != NULL && kN->stateNum == lN->stateNum)) {
						Array *kAry = (Array*)(kMapper->key);
						addAll(&kAry, (Array*)(lMapper->key)); 
						removeByIndex(destAry, l);
						kSize = getSize(destAry);
						lSize = kSize;
					} else l++;
				} else l++;
			}
			k++;
		}
//划分状态集， 细分到最小（即不能再分为止）
		Mapper *mapper = NULL;
		if(getSize(destAry) > 1) {
			for(k=0;k<getSize(nodeAryAry);k++) {
				Array *tmpAry = (Array*)getByIndex(nodeAryAry, k);
				FANode *tmpN1 = (FANode*)getByIndex(nodeAry, 0);
				FANode *tmpN2 = (FANode*)getByIndex(tmpAry, 0);
				if(tmpN1->stateNum == tmpN2->stateNum) {
					removeByIndex(nodeAryAry, k);
					break;
				}
			}
			for(k=0;k<getSize(destAry);k++) {
				mapper = (Mapper*)getByIndex(destAry, k);
				Array *keyAry = (Array*)(mapper->key);
				add(&nodeAryAry, keyAry);
			}
		}
		Array *result = NULL;
		HashMap *map = NULL;
		//printf("sizeof dest ary is %d\n", getSize(destAry));
		for(k=0;k<getSize(destAry);k++) {
			Mapper *mapper = (Mapper*)getByIndex(destAry, k);
			Array *keyAry = (Array*)(mapper->key);
			addAll(&result, recursion((Array*)(mapper->key), letterAry, j+1, nodeAryAry));
		}
		return result;
}

void minimalDFA(FA *dfa) {
	if(dfa == NULL) return;
	Array /**Array<FANode>**/ *nodeAryAry = NULL;
	Array /**FANode**/ *nodeAry = dfa->nodeAry;
	Array /**FANode**/ *finalStateAry = NULL;
	Array /**FANode**/ *nonFinalStateAry = NULL;
	Array *alphabetAry = dfa->alphabetAry;
	if(alphabetAry == NULL) {
		printf("minimal dfa error: alphabet is null\n");
		return;
	}
	int i;
	for(i=0;i<getSize(nodeAry);i++) {
		FANode *node = (FANode*)getByIndex(nodeAry, i);
		if(node->state) {
			add(&finalStateAry, node);			
		} else {
			add(&nonFinalStateAry, node);
		}
	}
	quicksortEx(finalStateAry, 0, getSize(finalStateAry)-1);
	quicksortEx(nonFinalStateAry, 0, getSize(nonFinalStateAry)-1);
	Array *result = NULL;
	printf("size of finalStateAry is %d, size of nonFinalStateAry is %d\n", getSize(finalStateAry), getSize(nonFinalStateAry));	
	//printf("sizeof nodeAryAry is %d\n", getSize(nodeAryAry));
	if(getSize(nonFinalStateAry)) {
		add(&nodeAryAry, nonFinalStateAry);
		addAll(&result, recursion(nonFinalStateAry, alphabetAry, 0, nodeAryAry));
	}
	if(getSize(finalStateAry))	{
		add(&nodeAryAry, finalStateAry);
		addAll(&result, recursion(finalStateAry, alphabetAry, 0, nodeAryAry));
	}
	
/**
	for(i=0;;i++) {
		if(i>=getSize(nodeAryAry)) break;
		printf("--aa----\n");
		Array *tmpary = (Array*)getByIndex(nodeAryAry, i);
		int j;
		for(j=0;j<getSize(tmpary);j++) {
			FANode *node = (FANode*)getByIndex(tmpary, j);
			printf("%d,", node->stateNum);
		}
		printf("\n");
		addAll(&result, recursion(tmpary, alphabetAry, 0, nodeAryAry));
		//size = getSize(nodeAryAry);
	}
**/
	HashMap *map = NULL;
	int size = getSize(result);
	for(i=0;i<size;) {
		Array *array = (Array*)getByIndex(result, i);
		FANode *node = (FANode*)getByIndex(array, 0);
		if(get(map, node->stateNum) == NULL) {
			put(&map, node->stateNum, array);
			i++;
		} else {
			printf("---begin print removed ele---\n");
			printf("%d\n", node->stateNum);
			printf("---end print removed ele---\n\n");
			removeByIndex(result, i);
			size = getSize(result);
		}
	}


	for(i=0;i<getSize(result);i++) {
		Array *array = (Array*)getByIndex(result, i);
		printf("(");
		int j;
		for(j=0;j<getSize(array);j++) {
			FANode *node = (FANode*)getByIndex(array, j);
			printf("%d,", node->stateNum);
		}
		printf(")\n");
	}
	printf("\n");
	mergeDFA(result);
/**
	printf("--begin print new fa start---\n");
	printFANode(dfa->start);
	printf("--end print new fa start---\n");
**/
}

void mergeDFA(Array/**Array<FANode>**/ *array) {
	if(!getSize(array)) return;
	Array /**FANode**/ *result = NULL;
	int i;
	for(i=0;i<getSize(array);i++) {
		Array *a = (Array*)getByIndex(array, i);
		int j;
		for(j=0;j<getSize(a);j++) {
			FANode *src = (FANode*)getByIndex(a, j);
			if(j == 0) {
				add(&result, src);
				int k;
				Array *edgeAry = src->edge;
				for(k=0;k<getSize(edgeAry);k++) {
					FAEdge *edge = (FAEdge*)getByIndex(edgeAry,k);
					FANode *dest = edge->node;
					int l;
					int index=-1;
					Array *tmpAry = NULL;
					for(l=0;l<getSize(array);l++) {
						tmpAry = (Array*)getByIndex(array, l);
						index = indexOf(tmpAry, dest);
						if(index > -1) break;
					}
					//index为0代表他在集合里的位置不是第一个，我们最终目的都是把dest用集合里的第一个元素代替；例如dest为2，他在集合{1，2}里，则我们用1来取代2
					if(index > 0) {
						edge->node = (FANode*)getByIndex(tmpAry, 0);
					}
				}
			}
		}
	}
	//把多余的节点释放掉
	for(i=0;i<getSize(array);i++) {
		Array *a = (Array*)getByIndex(array, i);
		int j;
		for(j=0;j<getSize(a);j++) {
			if(j==0) continue;
			FANode *node = (FANode*)getByIndex(a, j);
			int k;
			Array *edgeAry = node->edge;
			for(k=0;k<getSize(edgeAry);k++) {
				FAEdge *edge = (FAEdge*)getByIndex(edgeAry, k);
				free(edge);
			}
			free(edgeAry);
			free(node);
		}
	}
	for(i=0;i<getSize(result);i++) {
		FANode *node = (FANode*)getByIndex(result, i);
		printFANode(node);
		//printf("%d,", node->stateNum);
	}
	printf("\n");
}

void testFA() {
	char *p = "b*.c*..*.b*b*.*c*";		
	FA *nfa = reg2NFA(p);
	iterateNFA(nfa);
//	FA *dfa = nfa2DFA(nfa);
//	iterateDFA(dfa->start);
//	minimalDFA(dfa);
}


void testArray() {
	int a[] = {4,5,6,9,3,23,4,67,8,9,10};
	int b[] = {1,9,87};
	int size = sizeof(a)/sizeof(a[0]);
	Array *arrayA = NULL;
	int i;
	for(i=0;i<size;i++) {
		add(&arrayA, &a[i]);
	}
	size = sizeof(b)/sizeof(b[0]);
	Array *arrayB = NULL;
	for(i=0;i<size;i++) {
		add(&arrayB, &b[i]);
	}
	addAll(&arrayA, arrayB);
	for(i=0;i<getSize(arrayA);i++) {
		int *val = (int*)getByIndex(arrayA, i);
		printf("%d,", *val);
	}
	printf("\n");
}

void test() {
	char *p = "b*.c*..*.b*b*.*c*";
	char *s = "bcaccbbacbcbcab";
	printf("result=%c\n", isMatch(p, s));

//"bcaccbbacbcbcab"
//"b*.c*..*.b*b*.*c*"
}

void testQuicksort() {
	char c[] = {'c','a','b','f','e'};
	int size = sizeof(c)/sizeof(c[0]);
	int i;
	Array *array = NULL;
	for(i=0;i<size;i++) {
		FAEdge *edge = initFAEdge(&c[i]);
		add(&array, edge);
	}
	quicksort(array, 0, getSize(array)-1);
	for(i=0;i<getSize(array);i++) {
		FAEdge *edge = (FAEdge*)getByIndex(array, i);
		printf("%c,", *edge->value);
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

void testList() {
	int a[] = {2,3,4,8,34,102,10,12};
	List *list = NULL;
	int size = sizeof(a) / sizeof(a[0]);
	int i;
	for(i=0;i<size;i++) {
		insert(&list, &a[i]);
	}

	Node *node = next(list);
	while(node != NULL) {
		int *data = (int*)(node->data);
		printf("%d,", *data);
		node = next(list);
	}
	node = getHead(list);
	if(node == NULL) printf("head is null\n");
	else {
		int *data = node->data;
		printf("head is %d\n", *data);
	}

	node = getTail(list);
	if(node == NULL) printf("tail is null\n");
	else {
		int *data = node->data;
		printf("tail is %d\n", *data);
	}
	
	if(list == NULL || list->move == NULL) printf("move is null\n");
	else printf("move is %d\n", *((Node*)(list->move))->data);

	reset(list);
	if(list == NULL || list->move == NULL) printf("move is null\n");
	else printf("move is %d\n", *((Node*)(list->move))->data);
	printf("\n");
}

int main(void) {
	test();
//	testMap();
//	testArray();
//	testQueue();
//testQuicksort();
//testFA();

//	testList();

//testMerge();
//testArray();
	return 0;
}

