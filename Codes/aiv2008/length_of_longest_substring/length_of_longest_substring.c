#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define HASH_SIZE 29

typedef struct
{
	char val;
	struct LinkedListNode *pNext;
} LinkedListNode;

typedef struct
{
	int val;
	struct LinkedListNode2 *pNext;
} LinkedListNode2;

typedef struct
{
	struct LinkedListNode **key;
	struct LinkedListNode2 **val;
} HashMap;


int h(char key)
{
	return (int)key % HASH_SIZE;
}


void push(HashMap **ppHashMap,  char key, int val)
{
	if(!ppHashMap)return;
	if(!*ppHashMap)
	{
		*ppHashMap = (HashMap*)calloc(1, sizeof(HashMap));
		//(*ppHashMap)->size = HASH_SIZE;	
		(*ppHashMap)->key = (LinkedListNode**)calloc(HASH_SIZE, sizeof(LinkedListNode*));
		(*ppHashMap)->val = (LinkedListNode2**)calloc(HASH_SIZE, sizeof(LinkedListNode2*));
	}
	int hashCode = h(key);
	LinkedListNode* pKeyIndex = *((*ppHashMap)->key + hashCode);
	LinkedListNode2* pValIndex = *((*ppHashMap)->val + hashCode);
	if(!pKeyIndex)
	{
		pKeyIndex = (LinkedListNode*)calloc(1, sizeof(LinkedListNode));
		pValIndex = (LinkedListNode2*)calloc(1, sizeof(LinkedListNode2));
		pKeyIndex->val = key;
		pValIndex->val = val;
		*((*ppHashMap)->key + hashCode) = pKeyIndex;
		*((*ppHashMap)->val + hashCode) = pValIndex;
	}
	else
	{
		LinkedListNode* pKeyMove = pKeyIndex;
		LinkedListNode2* pValMove = pValIndex;
		int count=0;
		LinkedListNode *pKeyCur = NULL;
		LinkedListNode2 *pValCur = NULL;
		while(pKeyMove)
		{
			if(pKeyMove->val == key)
			{
				pValMove->val = val;
				count++;
				break;
			}
			pKeyCur = pKeyMove;
			pValCur = pValMove;
			pKeyMove = pKeyMove->pNext;
			pValMove = pValMove->pNext;
		}
		if(!count)
		{
			LinkedListNode *pKeyNode = (LinkedListNode*)calloc(1, sizeof(LinkedListNode));	
			LinkedListNode2 *pValNode = (LinkedListNode*)calloc(1, sizeof(LinkedListNode2));
			pKeyNode->val = key;
			pValNode->val = val;
			pKeyCur->pNext = pKeyNode;
			pValCur->pNext = pValNode;
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
	LinkedListNode **ppKeyIndex = pHashMap->key + hashCode;
	if(!ppKeyIndex)
	{
		printf("key is null\n");
		return -1;
	}
	
	LinkedListNode *pKeyMove = (*ppKeyIndex);	
	LinkedListNode2 *pValMove = *(pHashMap->val + hashCode);
	int val = -1;
	while(pKeyMove)
	{
		if(pKeyMove->val == key)
		{
			val = pValMove->val;		
			break;
		}
		pKeyMove = pKeyMove->pNext;
		pValMove = pValMove->pNext;
	}
	return val;
}

int lengthOfLongestSubstring(char* s)
{
	if(!s || !strlen(s))return 0;
	char *pHeader = s;
	char *pMove = pHeader;
	HashMap *pHashMap = NULL;
	int maxLen = 0;
	int count = 0;
	int i=0;
	while((*pMove)!='\0')
	{
		int index = get(pHashMap, *pMove);
		if(index == -1)
		{
			count++;
			push(&pHashMap, *pMove, i);
		}
		else
		{
			maxLen = (count > maxLen) ? count : maxLen;
			char *pTail = s + index + 1;
			char *pMoveJ = pHeader;
			while(pMoveJ != pTail)
			{
				push(&pHashMap, *pMoveJ, -1);
				pMoveJ++;
			}
			pHeader = pTail;
			push(&pHashMap, *pMove, i);
			count = pMove - pHeader + 1;
		}
		pMove++;
		i++;
	}
	if(count)maxLen = (count > maxLen) ? count : maxLen;
	return maxLen;	
}

int main(void)
{
	printf("please enter the string:\n");
	char str1[30] = {0};
	gets(str1);
	printf("%d\n", lengthOfLongestSubstring(str1));

	return 0;
}
