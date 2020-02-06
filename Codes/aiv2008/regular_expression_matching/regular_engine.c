#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

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
	while(*pMove != '\0') {
		if(*pMove == '.') {
			nfa = unonAllNFA();
		} else if(*pMove == '*') {
			nfa = kleenStarNFA(nfa); 
		} else {
			nfa = symbolNFA(*pMove);
		}
		pMove++;
	}
	return nfa;
}

void test() {
	char *p = "c*a*b";
	NFA *nfa = reg2NFA(p);
}

int main(void) {
	test();
}

/**
NFA *initEpsilon() {
	return initSymbol(' ');
}

NFA *initSymbol(char c) {
	NFA *nfa = (NFA*)calloc(1, sizeof(NFA));
	if(nfa == NULL) {
		printf("nfa calloc failed\n");
		return;
	}
	NFANode *start = (NFANode*)calloc(1, sizeof(NFANode));
	if(start == NULL) {
		printf("nfa start node calloc failed\n");
		free(nfa);
		return;
	}
	start->value = 0x00;
	start->state = 0;
	NFANode *end = (NFANode*)calloc(1, sizeof(NFANode));
	if(end == NULL) {
		printf("nfa end node calloc failed\n");
		free(start);
		start = NULL;
		free(nfa);
		nfa = NULL;
	}
	end->value = c;
	end->state = 1;
	start->nextEdge1 = end;
	nfa->start = start;
	nfa->end = end;
	return nfa;
}

void addNFANode(NFANode *start, NFANode *end) {
	if(start == NULL || end == NULL) {
		printf("start or end node is null\n");
		return;
	}
	if(start->nextEdge1 == NULL) start->nextEdge1 = end;
	else if(start->nextEdge2 == NULL) start->nextEdge2 = end;
	else printf("cannot be more than 2 tranfer edge\n");
}

//basic operator: concat
NFA *concatNFA(NFA *start, NFA **end) {
	if(end == NULL) return start;
	if(start == NULL && *end == NULL) return NULL;
	else if(start == NULL) return *end;
	else if(*end == NULL) return start;
	NFANode *endOfStart = start->end;
	NFANode *startOfEnd = (*end)->start;
	if(startOfEnd->nextEdge1 == NULL) {
		endOfStart->nextEdge1 = startOfEnd->nextEdge1;
	} else if(startOfEnd->nextEdge2 == NULL) {
		endOfStart->nextEdge2 = startOfEnd->nextEdge2;
	} 
	start->end = (*end)->end;
	if((*end)->start != NULL) {
		free((*end)->start);
		(*end)->start = NULL;
	}
	(*end)->end = NULL;
	free(*end);
	*end = NULL;
	return start;
}

//basic operator: union
NFA *unon(NFA *nfaS, NFA **nfaT) {
	if(nfaT == NULL) return NULL;
	if(nfaS == NULL ) return *nfaT;
	else if(*nfaT == NULL) return nfaS;
	NFANode *start = (NFANode*)calloc(1, sizeof(NFANode));
	NFANode *end = (NFANode*)calloc(1, sizeof(NFANode));
	start->value = '\0';
	end->value = '\0';
	NFANode *startS = nfaS->start;
	NFANode *startT = nfaT->start;
	startS->value = ' ';
	startT->value = ' ';
	start->nextEdge1 = startS;
	start->nextEdge2 = startT;

}

void initKleenStar(NFA *src) {
	if(src == NULL) {
		printf("nfa is null\n");
		return NULL;
	}
	NFANode  *startNode = (NFANode*)calloc(1, sizeof(NFANode));
	if(startNode == NULL) {
		printf("initKleenStar: start node calloc failed\n");
		return;
	}
	startNode->value = ' ';
	NFANode  *endNode = (NFANode*)calloc(1, sizeof(NFANode));
	if(endNode == NULL) {
		printf("initKleenStar: end node calloc failed\n");
		return;
	}
	endNode->value = '\0';
	addNFANode(startNode, src->start);
	addNFANode(start->end, src->start);
	addNFANode(start->end, endNode);
	addNFANode(startNode, endNode);
	NFANode *srcEndNode = src->end;
	srcEndNode->state = 0;
	endNode->state = 1;
	src->start = startNode;
	src->end = endNode;
}
**/
