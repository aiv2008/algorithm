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
	struct NFAEdge *edge1;
	struct NFAEdge *edge2;
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
	Array *alphabet;
} NFA;

typedef struct {
	struct Array/**<NFANode*>**/ **states;
	struct Array/**<DFAEdge*>**/ *edges;
	int state;
} DFANode;

typedef struct {
	struct DFANode *node;
	char value;
} DFAEdge;

typedef struct {
	struct DFANode *start;
	struct DFANode *end;
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
	char c[4] = {'a','b','b','a'};
	HashMap *map = NULL;
	int i=0;
	int origValue = 1;
	for(;i<4;i++) {
		int *value = (int*)get(map, c[i]);
		printf("key=%c,", c[i]);
		printf("value=%d\n", value == NULL ? -1 : *value);
		if(value == NULL) {
			put(&map, c[i], &origValue, sizeof(int));
		} else {
			int v = *value+1;
			put(&map, c[i], &v, sizeof(int));
		}
	}
	for(i=0;i<4;i++){
		int *value = (int*)get(map, c[i]);
	//	printf("key=%c, value=%d\n", c[i], *value);
	printf("%c,",  c[i]);
	printf("%d,", *value);
	}
	printf("\n");
}

NFANode *initNFANode(NFAEdge *edge1, NFAEdge *edge2, int state) {
	if(state != 0x00 && state != 0x01) {
		printf("init nfa node failed: state must be 1 or 0\n");
		return NULL;
	}
	NFANode *node = (NFANode*)calloc(1, sizeof(NFANode));
	if(node == NULL) {
		printf("init nfa node failed\n");
		return NULL;
	}
	if(edge1 != NULL) node->edge1 = edge1;
	if(edge2 != NULL) node->edge2 = edge2;
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
	NFANode *start = initNFANode(edge, NULL, 0);
	NFANode *end = initNFANode(NULL, NULL, 1);
	edge->node = end;
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
	NFANode *start = initNFANode(edge1, edge2, 0);
	NFANode *startOfS = nfaS->start;
	NFANode *startOfT = nfaT->start;
	edge1->node = startOfS;
	edge2->node = startOfT;
	NFANode *end = initNFANode(NULL, NULL, 1);
	NFANode *endOfS = nfaS->end;
	NFANode *endOfT = nfaT->end;
	NFAEdge *edge3 = initEpEdge();
	NFAEdge *edge4 = initEpEdge();
	endOfS->edge1 = edge3;
	endOfT->edge1 = edge4;
	edge3->node = end;
	edge4->node = end;
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
	endOfS->edge1 = startOfT->edge1 == NULL ? NULL : startOfT->edge1;
	endOfS->edge2 = startOfT->edge2 == NULL ? NULL : startOfT->edge2;
	endOfS->state = 0;
	updateNFA(nfaS, nfaS->start, nfaT->end);
	return nfaS;
}

NFA *kleenStarNFA(NFA *nfa) {
	if(nfa == NULL) return NULL;
	NFAEdge *edge1 = initEpEdge();
	NFAEdge *edge2 = initEpEdge();
	NFAEdge *edge3 = initEpEdge();
	NFAEdge *edge4 = initEpEdge();
	NFANode *start = initNFANode(edge1, edge2, 0);
	edge1->node = nfa->start;
	NFANode *end = initNFANode(NULL, NULL, 1);
	edge2->node = end;
	NFANode *endOfNFA = nfa->end;
	endOfNFA->edge1 = edge3;
	edge3->node = nfa->start;
	endOfNFA->edge2 = edge4;
	edge4->node = end;
	endOfNFA->state = 0;
	updateNFA(nfa, start, end);
	return nfa;
}

NFA *unonAllNFA() {
	NFA *nfa = symbolNFA('a');
	NFA *nfaTmp = NULL;
	int i;
	for(i=98;i<=122;i++) {
		nfaTmp = symbolNFA((char)i);
		nfa = unonNFA(nfa, nfaTmp);
	}
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
		if(*pMove == '.') {
			nfaTmp = unonAllNFA();
		} else if(*pMove == '*') {
			nfaTmp = kleenStarNFA(nfa); 
		} else {
			nfaTmp = symbolNFA(*pMove);
		}
		nfa = concatNFA(nfa, nfaTmp);
		if(*pMove>=97 && *pMove<=122) {
			int *value = get(map, *pMove);
			if(value != NULL) {
				put(&map, *pMove, &origValue, sizeof(int));
				add(&array, *pMove, sizeof(char));
			}
		}
		nfaTmp = NULL;
		pMove++;
	}
	nfa->alphabet = array;
	return nfa;
}

Array *delta(NFANode *node, char value) {
	if( node == NULL) {
		printf("delta function failed: nfa node is null\n");
		return NULL;
	}
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
		}
		pop(&queue);
		t = top(queue);
	}
	return dfaStates;
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
	if(nfa == NULL) return NULL;
	//nfa的字母表
	Array *alphabet = nfa->alphabet;
	NFANode *nfaStartNode = nfa->start;
	//nfa的初始状态值（只通过epsilon能到达的所有状态）
	Array state0 = eclosure(nfaStartNode);
	DFA *dfa = (DFA*)calloc(1, sizeof(DFA));
	//dfa的初始状态
	DFANode *dfaNode = (DFANode*) calloc(1, sizeof(DFANode));
	dfaNode->states = state0;
	updateDFANodeState(dfaNode);

	HashMap *map = NULL;
	Queue *queue = NULL;
	Array *nextDFAEdge = NULL;
	Array *nextDFANode = NULL;
	int i;
	for(i=0;i<getSize(state0);i++) {
		NFANode *nfaNode = (NFANode*)getByIndex(state0, i, sizeof(NFANode));
		int j;
		for(j=0;j<getSize(alphabet);j++) {
			char *c = getByIndex(alphabet, j, sizeof(char));
			Array* nextNFAState = delta(nfaNode, *c) ;
			if(nextNFAState != NULL && getSize(nextNFAState)) {
				
			}
		}
	}
}

void test() {
	char *p = "c*a*b";
	NFA *nfa = reg2NFA(p);
}

int main(void) {
//	test();
	testMap();
}

