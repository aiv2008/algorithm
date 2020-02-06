#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define ARRAY_SIZE 10
#define bool char
#define true '1'
#define false '0'

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
	NFANode *node;
	char value;
} NFAEdge;

typedef struct {
	NFANode *start;
	//注: end节点不能有任何指向其他节点的边
	NFANode *end;
} NFA;

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

int getSize(Array *array) {
	if(array == NULL) return 0;
	return array->size;
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
	while(*pMove != '\0') {
		if(*pMove == '.') {
			nfaTmp = unonAllNFA();
		} else if(*pMove == '*') {
			nfaTmp = kleenStarNFA(nfa); 
		} else {
			nfaTmp = symbolNFA(*pMove);
		}
		nfa = concatNFA(nfa, nfaTmp);
		nfaTmp = NULL;
		pMove++;
	}
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
	NFANode *pMove = node;
	push(&queue, pMove);
	Element *t = top(queue);
	while(t != NULL) {
		if(pMove != NULL) {
			NFAEdge *edge1 = pMove->edge1;
			NFAEdge *edge2 = pMove->edge2;
			if(edge1 != NULL && edge1->node != NULL) {
				push(&queue, edge1->node);
				
			}
			if(edge2 != NULL && edge2->node != NULL) {
				push(&queue, edge2->node);
			}
		}
		pop(&queue);
		t = top(queue);
	}
}

void eclosure() {

}


void test() {
	char *p = "c*a*b";
	NFA *nfa = reg2NFA(p);
}

int main(void) {
	test();
}

