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
	struct Array/**<Array<NFANode*>>**/ *states;
	struct Array/**<DFAEdge*>**/ *edges;
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

NFANode *initNFANode(Array/**<NFAEdge>**/ *edgeAry, /**NFAEdge *edge1, NFAEdge *edge2,**/ int state) {
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

NFA *symbolNFA(char c) {
	NFAEdge *edge = initNFAEdge(c);
	NFANode *end = initNFANode(NULL, 1);
	edge->node = end;
	Array/**<NFAEdge>**/ *edgeAry = NULL;
	add(&edgeAry, edge, sizeof(NFAEdge));
//	NFANode *start = initNFANode(edge, NULL, 0);
	NFANode *start = initNFANode(edgeAry, 0);
//	NFANode *end = initNFANode(NULL, NULL, 1);
	return initNFA(start, end);
}

NFA *epsilonNFA() {
	return symbolNFA(0x20);
}

NFA *unonNFA(NFA *nfaS, NFA *nfaT) {
	if(nfaT == NULL) return nfaS;
	else if(nfaS == NULL) return nfaT;
	NFAEdge *edge1 = initEpEdge();
	NFAEdge *edge2 = initEpEdge();
	Array *edgeAry1 = NULL;
	add(&edgeAry1, edge1, sizeof(NFAEdge));
	add(&edgeAry1, edge2, sizeof(NFAEdge));
	//NFANode *start = initNFANode(edge1, edge2, 0);
	NFANode *start = initNFANode(edgeAry1, 0);
	NFANode *startOfS = nfaS->start;
	NFANode *startOfT = nfaT->start;
	edge1->node = startOfS;
	edge2->node = startOfT;
	NFANode *end = initNFANode(NULL, 1);
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

NFA *kleenStarNFA(NFA *nfa) {
	if(nfa == NULL) return NULL;
//	NFANode *stn = nfa->start;
//	printf("print nfa node in kleen start nfa\n");
//	printNFANode(stn);
	NFANode *end = initNFANode(NULL, 1);
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
	NFANode *start = initNFANode(edgeAry1, 0);
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

NFA *unonAllNFA() {
	Array/**<NFAEdge>**/ *startEdgeAry = NULL;
	NFANode *endNode = initNFANode(NULL, 1);
	NFAEdge *endEdge = NULL;
	NFAEdge *startEdge = NULL;
	int i;
	for(i=97;i<122;i++) {
		NFA *nfa = symbolNFA(i);
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
	}
	NFANode *startNode = initNFANode(startEdgeAry, 0);
	NFA *nfa = initNFA(startNode, endNode);
	return nfa;
}

NFA *reg2NFA(char *p) {
//	char *p = ".*";
	char *pMove = p;
	NFA *nfa = NULL;
	NFA *nfaTmp = NULL;
	HashMap *map = NULL;
	Array *array = NULL;
	int origValue = 1;
	while(*pMove != '\0') {
		if(*(pMove+1) == '*') {
			if(*pMove == '.') {
				nfaTmp = unonAllNFA();
			} else {
				nfaTmp = symbolNFA(*pMove);
			}
			nfaTmp = kleenStarNFA(nfaTmp); 
			nfa = concatNFA(nfa, nfaTmp);
			pMove+=2;
		} else {
			if(*pMove == '.') {
				nfaTmp = unonAllNFA();
			} else {
				nfaTmp = symbolNFA(*pMove);
			}
			nfa = concatNFA(nfa, nfaTmp);
			pMove++;
		}

		if(*pMove>=97 && *pMove<=122) {
			int *value = (int*)get(map, *pMove);
			if(value == NULL) {
				put(&map, *pMove, &origValue, sizeof(int));
				add(&array, pMove, sizeof(char));
			}
		}
		nfaTmp = NULL;
	}
	nfa->alphabet = array;
	/**
	int i;
	for(i=0;i<getSize(array);i++) {
		char *c = getByIndex(array, i, sizeof(char));
		printf("%c,", *c);
	}
	printf("\n");
	**/
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
	/**
	NFAEdge *edge1 = node->edge1;
	NFAEdge *edge2 = node->edge2;
	Array *dfaStates = NULL;
	if(edge1 != NULL) {
		if(edge1->value == value) {
			add(&dfaStates, edge1->node, sizeof(NFANode));
		}	
	}
	if(edge2 != NULL) {
		if(edge2->value == value) {
			add(&dfaStates, edge2->node, sizeof(NFANode));
		}	
	}
	**/
	return dfaStates;
}

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
		if(pMove != NULL) {
			Array *edgeAry = pMove->edge;
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
				/**
			NFAEdge *edge1 = pMove->edge1;
			NFAEdge *edge2 = pMove->edge2;
			if(edge1 != NULL && edge1->value ==' ' && edge1->node != NULL) {
				int *value = (int*)get(map, edge1->node);
				if(value == NULL) {
					put(&map, edge1->node, &origValue, sizeof(int));
					push(&queue, edge1->node);
					add(&dfaStates, edge1->node, sizeof(NFANode));
				}				
			}
			if(edge2 != NULL && edge2->value == ' ' && edge2->node != NULL) {
				int *value = (int*)get(map, edge2->node);
				if(value == NULL) {
					put(&map, edge2->node, &origValue, sizeof(int));
					push(&queue, edge2->node);
					add(&dfaStates, edge2->node, sizeof(NFANode));
				}				
			}
			**/
		}
		pop(&queue);
		t = top(queue);
	}
	return dfaStates;
}

Array *closure(Array/**<NFANode>**/ *nodes) {
	if(nodes == NULL) return NULL;
	int i;
	Array *result = NULL;
	for(i=0;i<getSize(nodes);i++) {
		NFANode *node = (NFANode*)getByIndex(nodes, i, sizeof(NFANode));
		Array *a = eclosure(node);
		addAllDist(&result, a, sizeof(NFANode));
	}
	return result;
}

void printNFANode(NFANode *node) {
	if(node == NULL) {
		printf("print dfa node failed: node is null\n");
		return;
	}
	printf("node=%p, state=%d\n",node, node->state);
	Array *edgeAry = node->edge;
	int i;
	for(i=0;i<getSize(edgeAry);i++) {
		NFAEdge *edge = (NFAEdge*)getByIndex(edgeAry, i, sizeof(NFAEdge));
		if(edge == NULL) {
			printf("edge is null\n");
		}else {
			if(edge->value == ' ') {
				printf("edge value=epsilon\n");
			} else {
				printf("edge value=%c\n", edge->value);
			}
		}
	}

/**
	NFAEdge *edge1 = node->edge1;
	NFAEdge *edge2 = node->edge2;
	if(edge1 == NULL) {
		printf("edge1 is null\n");
	}else {
		if(edge1->value == ' ') {
			printf("edge1 value=epsilon\n");
		} else {
			printf("edge1 value=%c\n", edge1->value);
		}
	}
	if(edge2 == NULL) {
		printf("edge2 is null\n");
	}else {
		if(edge2->value == ' ') {
			printf("edge2 value=epsilon\n");
		} else {
			printf("edge2 value=%c\n", edge2->value);
		}
	}
	**/
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
				int *value = (int*)get(map, edge->node);
				if(value == NULL) {
					put(&map, edge->node, &origValue, sizeof(int));
					push(&queue, edge->node);
				}
			}
		}
/**
		NFAEdge *edge1 = node->edge1;
		NFAEdge *edge2 = node->edge2;
		if(edge1 != NULL && edge1->node != NULL) {
			int *value = (int*)get(map, edge1->node);
			if(value == NULL) {
				put(&map, edge1->node, &origValue, sizeof(int));
				push(&queue, edge1->node);
			}
		}
		if(edge2 != NULL && edge2->node != NULL) {
			int *value = (int*)get(map, edge2->node);
			if(value == NULL) {
				put(&map, edge2->node, &origValue, sizeof(int));
				push(&queue, edge2->node);
			}
		}
		**/
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

DFA *nfa2DFA(NFA *nfa) {
	if(nfa == NULL) {
		printf("nfa to dfa failed: nfa is null\n");
		return NULL;
	}
	//nfa的字母表
	Array *alphabet = nfa->alphabet;
	NFANode *nfaStartNode = nfa->start;
	printNFANode(nfaStartNode);
	//nfa的初始状态值（只通过epsilon能到达的所有状态）
	Array *state0 = eclosure(nfaStartNode);
	DFA *dfa = (DFA*)calloc(1, sizeof(DFA));
	//dfa的初始状态
	DFANode *dfaNode = (DFANode*) calloc(1, sizeof(DFANode));
	dfaNode->states = state0;
	updateDFANodeState(dfaNode);
	dfa->start = dfaNode;
	Array *ends = NULL;
	if(dfaNode->state == 1) {
		add(&ends, dfaNode, sizeof(DFANode));
	}	
	Queue *queue = NULL;
	Array *nextDFAEdge = NULL;
	Array *nextDFANode = NULL;
	push(&queue, dfaNode);
	Element *t = top(queue);
	int origValue = 1;
	while(t != NULL) {
		DFANode *node = (DFANode*)(t->val);
		Array/**<NFANode>**/ *midStateArray = node->states;
		int i;
		for(i=0;i<getSize(midStateArray);i++) {
			NFANode *nfaNode = (NFANode*)getByIndex(midStateArray, i, sizeof(NFANode));
			int j;
			HashMap *map = NULL;
			for(j=0;j<getSize(alphabet);j++) {
				char *c = getByIndex(alphabet, j, sizeof(char));
				Array/**<NFANode>**/* nextNFAState = delta(nfaNode, *c) ;
				printf("char =%c\n", *c);	
				printf("1 size of nextNFAState is: %d\n", getSize(nextNFAState));
				if(nextNFAState != NULL && getSize(nextNFAState)) {
					nextNFAState = closure(nextNFAState);
					printf("2 size of nextNFAState is: %d\n", getSize(nextNFAState));
					int *v = (int*)get(map, *c);
					if(v==NULL) {
						DFAEdge *edge = initDFAEdge(*c);
						add(&nextDFAEdge, edge, sizeof(DFAEdge));	
						add(&nextDFANode, nextNFAState, sizeof(Array));
						put(&map, *c, &origValue, sizeof(int));
					} else {
						int k;
						for(k=0;k<getSize(nextDFAEdge);k++) {
							//char *cc = getByIndex(nextDFAEdge, k, sizeof(char));
							DFAEdge *edge = (DFAEdge*)getByIndex(nextDFAEdge, k, sizeof(DFAEdge));
							if(edge->value == *c) {
								Array/**<NFANode>**/ *a = (Array*)getByIndex(nextDFANode, k, sizeof(Array));
								addAllDist(&a, nextNFAState, sizeof(NFANode));
								break;
							}
						}
					}
					DFANode *dfn = (DFANode*)calloc(1, sizeof(DFANode));
					dfn->states = nextNFAState;
					dfn->edges = nextDFAEdge;
					updateDFANodeState(dfn);
					if(dfn->state == 1) {
						add(&ends, dfn, sizeof(DFANode));
					}	
					push(&queue, dfn);
				}
			}
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
	char *p = "c*a*b";
	NFA *nfa = reg2NFA(p);
//	NFANode *start = nfa->start;
//	printf("print start node\n");
//	printNFANode(start);
//	NFANode *end = nfa->end;
//	printf("end node is %p, state is %d\n",end, end->state);
	iterateNFA(nfa);
//	DFA *dfa = nfa2DFA(nfa);
//	iterateDFA(dfa);
}

void testQueue() {
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
}

