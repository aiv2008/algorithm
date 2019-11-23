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


void put(HashMap **ppHashMap,  char key,signed int val)
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
		pValIndex->val = (signed int*)calloc(1, sizeof(signed int));
		*(char*)(pKeyIndex->val) = key;
		*(signed int*)(pValIndex->val) = val;
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
				//pValMove->val = &val;
				*(signed int*)(pValMove->val) = val;
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
			pValNode->val = (signed int*)calloc(1, sizeof(signed int));
			*(char*)(pKeyNode->val) = key;
			*(signed int*)(pValNode->val) = val;
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
	ListNode **ppKeyIndex = pHashMap->key  + hashCode;
	if(!ppKeyIndex)
	{
		printf("key is null\n");
		return -1;
	}
	
	ListNode *pKeyMove = (*ppKeyIndex);	
	ListNode *pValMove = *(pHashMap->val + hashCode);
	signed int val = -1;
	while(pKeyMove)
	{
		if(*(char*)(pKeyMove->val) == key)
		{
			val = *(signed int*)(pValMove->val);	
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
	//void *memcpy ( void * dest, const void * src, size_t num );
	node->val = (char*)calloc(1, sizeof(char));
	memcpy(node->val, (void*)(&val), sizeof(char));
	if(!*ppQueue || !(*ppQueue)->size)
	{
		if(!*ppQueue)*ppQueue = (Queue*)calloc(1, sizeof(Queue));
		(*ppQueue)->top = node;
		(*ppQueue)->bottom = node;
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
	if(!pQueue || !pQueue->size)return;
	if(pQueue->top == pQueue->bottom)
	{//the last element
		free(pQueue->top);
		pQueue->top = NULL;
		pQueue->bottom = NULL;
	}
	else
	{
		ListNode* oldNode = pQueue->top;
		pQueue->top = ((ListNode*)(pQueue->top))->next;
		free(oldNode);
		oldNode = NULL;
	}
	pQueue->size--;
}

int lengthOfLongestSubstring(char* s)
{
	if(!s || !strlen(s))return 0;
	char *pMove = s;
	HashMap *pHashMap = NULL;
	Queue *pQueue = NULL;
	int maxLen = 0;
	while(*pMove)
	{
		if(get(pHashMap, *pMove) == -1)
		{
			put(&pHashMap, *pMove, 1);
			push(&pQueue, *pMove);
		}
		else
		{
			maxLen = pQueue->size > maxLen ? pQueue->size : maxLen;
			ListNode *pTop = pQueue->top;
			while(*(char*)(pTop->val) != *pMove)
			{
				put(&pHashMap, *(char*)(pTop->val), -1);
				pop(pQueue);
				pTop = pQueue->top;
			}
			put(&pHashMap, *(char*)(pTop->val), -1);
			pop(pQueue);
			push(&pQueue, *pMove);	
			put(&pHashMap, *pMove, 1);
		}
		pMove++;
	}
	return pQueue->size > maxLen ? pQueue->size : maxLen;
}


int main(void)
{
	char *s = "pwwkew";	
	printf("%d\n", lengthOfLongestSubstring(s));

	return 0;
}
