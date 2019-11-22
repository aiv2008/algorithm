#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define HASH_SIZE 29

typedef struct
{
	void *val;
	struct ListNode *next;	
} ListNode;

typedef struct
{
	struct ListNode* top;
	struct ListNode* bottom;
	int size;
} Queue;


typedef struct
{
	struct ListNode **key;
	struct ListNode **val;
} HashMap;


int h(char key)
{
	return (int)key % HASH_SIZE;
}


void put(HashMap **ppHashMap,  char key, int val)
{
	if(!ppHashMap)return;
	if(!*ppHashMap)
	{
		*ppHashMap = (HashMap*)calloc(1, sizeof(HashMap));
		(*ppHashMap)->key = (ListNode**)calloc(HASH_SIZE, sizeof(ListNode*));
		(*ppHashMap)->val = (ListNode**)calloc(HASH_SIZE, sizeof(ListNode*));
	}
	int hashCode = h(key);
	ListNode* pKeyIndex = *((*ppHashMap)->key + hashCode);
	ListNode* pValIndex = *((*ppHashMap)->val + hashCode);
	if(!pKeyIndex)
	{
		pKeyIndex = (ListNode*)calloc(1, sizeof(ListNode));
		pValIndex = (ListNode*)calloc(1, sizeof(ListNode));
		pKeyIndex->val = (char*)calloc(1, sizeof(char));
		pValIndex->val = (int*)calloc(1, sizeof(int));
		*(char*)(pKeyIndex->val) = key;
		*(int*)(pValIndex->val) = val;
		*((*ppHashMap)->key + hashCode) = pKeyIndex;
		*((*ppHashMap)->val + hashCode) = pValIndex;
	}
	else
	{
		ListNode* pKeyMove = pKeyIndex;
		ListNode* pValMove = pValIndex;
		int count=0;
		ListNode *pKeyCur = NULL;
		ListNode *pValCur = NULL;
		while(pKeyMove)
		{
			if(*(char*)(pKeyMove->val) == key)
			{
				pValMove->val = &val;
				count++;
				break;
			}
			pKeyCur = pKeyMove;
			pValCur = pValMove;
			pKeyMove = pKeyMove->next;
			pValMove = pValMove->next;
		}
		if(!count)
		{
			ListNode *pKeyNode = (ListNode*)calloc(1, sizeof(ListNode));	
			ListNode *pValNode = (ListNode*)calloc(1, sizeof(ListNode));
			pKeyNode->val = (char*)calloc(1, sizeof(char));
			pValNode->val = (int*)calloc(1, sizeof(int));
			*(char*)(pKeyNode->val) = key;
			*(int*)(pValNode->val) = val;
			pKeyCur->next = pKeyNode;
			pValCur->next = pValNode;
			pKeyNode = NULL;
			pValNode = NULL;
		}
		pKeyMove = NULL;
		pValMove = NULL;
		pKeyCur = NULL;
		pValCur = NULL;
	}	
}

int get(HashMap *pHashMap, char key)
{
	if(!pHashMap)
		return -1;
	int hashCode = h(key);
	if(!pHashMap->key)
	{
		printf("plinkedlistkey is null\n");
		return;
	}
	ListNode **ppKeyIndex = pHashMap->key + hashCode;
	if(!ppKeyIndex)
	{
		printf("key is null\n");
		return -1;
	}
	
	ListNode *pKeyMove = (*ppKeyIndex);	
	ListNode *pValMove = *(pHashMap->val + hashCode);
	int val = -1;
	while(pKeyMove)
	{
		//printf("key=%c\n", *(char*)(pKeyMove->val));
		if(*(char*)(pKeyMove->val) == key)
		{
			val = *(int*)(pValMove->val);		
			break;
		}
		pKeyMove = pKeyMove->next;
		pValMove = pValMove->next;
	}
	return val;
}

void push(Queue **ppQueue, char val)
{
	if(!ppQueue)return;
	ListNode *node = (ListNode*)calloc(1, sizeof(ListNode));
	node->val = (char*)calloc(1, sizeof(char));
	*(char*)(node->val) = val;
	printf("\npush:val=%c, node->val= %c\n",val, *(char*)(node->val));
	if(!*ppQueue || !(*ppQueue)->size)
	{
		if(*ppQueue && !(*ppQueue)->size)
		{
			printf("queue size=0, enter here\n");
			free((*ppQueue)->top);
			free((*ppQueue)->bottom);
			(*ppQueue)->top = NULL;
			(*ppQueue)->bottom = NULL;
			realloc(*ppQueue, sizeof(Queue));
			//free(*ppQueue);
		}
		else			
			*ppQueue = (Queue*)calloc(1, sizeof(Queue));
		printf("\npush:val=%c, node->val= %c\n",val, *(char*)(node->val));
		(*ppQueue)->top = node;
		(*ppQueue)->bottom = node;
		
		printf("\npush: %c\n", *(char*)(((ListNode*)((*ppQueue)->top))->val));
	}
	else
	{
		((ListNode*)((*ppQueue)->bottom))->next = node;
		(*ppQueue)->bottom = ((ListNode*)((*ppQueue)->bottom))->next;
	}
	(*ppQueue)->size++;
}

void pop(Queue *pQueue)
{
	if(!pQueue)return;
	pQueue->size--;
	if(pQueue->top == pQueue->bottom)
	{
		pQueue->top = ((ListNode*)(pQueue->top))->next;
		pQueue->bottom = pQueue->top;
		free(pQueue);
		return;
	}
	ListNode* oldNode = pQueue->top;
	pQueue->top = ((ListNode*)(pQueue->top))->next;
	//printf("pop node is %d\n", oldNode->val);
	free(oldNode);
	oldNode = NULL;
}


void print(Queue *pQueue)
{
	printf("\n---print queue begin---\n");
	if(!pQueue)return;
	ListNode* pMove = pQueue->top;
	int i=0;
	while(pMove || i<3)
	{
		printf("%c,", *(char*)(pMove->val));
		pMove = pMove->next;
		i++;
	}
	printf("\n---print queue end---\n");
}

int lengthOfLongestSubstring(char* s)
{
	if(!s || !strlen(s))return 0;
	char *pMove = s;
	HashMap *pHashMap = NULL;
	Queue *pQueue = NULL;
	int maxLen = 0;
	//int count  0;
	while(*pMove)
	{
		if(get(pHashMap, *pMove) == -1)
		{
			put(&pHashMap, *pMove, 1);
			push(&pQueue, *pMove);
			printf("\n---111---\n");
			printf("pMove=%c\n", *pMove);
			//print(pQueue);
		}
		else
		{
			printf("\n---222---\n");
			printf("pMove=%c\n", *pMove);
			//print(pQueue);
			ListNode *pTop = pQueue->top;
			printf("111pTop->val===%c\n", *(char*)(pTop->val));
			while(*(char*)(pTop->val) != *pMove)
			{
				pop(pQueue);
				//print(pQueue);
				pTop = pQueue->top;
				printf("222pTop->val===%c\n", *(char*)(pTop->val));
			}
			maxLen = pQueue->size > maxLen ? pQueue->size : maxLen;
			printf("111queue size=%d\n",pQueue->size);
			if(!pQueue)printf("111pQueue is null\n");
			pop(pQueue);
			printf("222queue size=%d\n",pQueue->size);
			if(!pQueue)printf("222pQueue is null\n");
			push(&pQueue, *pMove);	
			printf("333pTop->val===%c\n", *(char*)(pTop->val));
			//print(pQueue);
		}
		pMove++;
	}
	printf("maxLen=%d\n", pQueue->size > maxLen ? pQueue->size : maxLen);
	return pQueue->size > maxLen ? pQueue->size : maxLen;
}


int main(void)
{
	char *s = "abba";	
/**
	Queue *pQueue = NULL;
	char *pMove = s;
	while((*pMove) != '\0')
		push(&pQueue, *pMove++);
	print(pQueue);
**/
	printf("%d", lengthOfLongestSubstring(s));
	return 0;
}
