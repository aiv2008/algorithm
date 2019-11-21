#include<stdio.h>
#include<stdlib.h>
#include"add_two_numbers.h"

/**
typedef struct
{
	ListNode* top;
	ListNode* bottom;
} stack;
**/

void push(queue **ppQueue, ListNode* node)
{
	if(!ppQueue||!node)return;
	if(!*ppQueue)
	{
		*ppQueue = (queue*)calloc(1, sizeof(queue));
		(*ppQueue)->top = node;
		(*ppQueue)->bottom = node;
		//((ListNode*)((*ppQueue)->bottom))->next = NULL;
	}
	else
	{
		((ListNode*)((*ppQueue)->bottom))->next = node;
		(*ppQueue)->bottom = ((ListNode*)((*ppQueue)->bottom))->next;
	}
}

void pop(queue *pQueue)
{
	if(!pQueue)return;
	if(pQueue->top == pQueue->bottom)
	{
		pQueue->top = ((ListNode*)(pQueue->top))->next;
		pQueue->bottom = pQueue->top;
		free(pQueue);
		return;
	}
	ListNode* oldNode = pQueue->top;
	pQueue->top = ((ListNode*)(pQueue->top))->next;
	printf("pop node is %d\n", oldNode->val);
	free(oldNode);
	oldNode = NULL;
}

void print(queue *pQueue)
{
	if(!pQueue)return;
	ListNode* pMove = pQueue->top;
	while(pMove)
	{
		printf("%d,", pMove->val);
		pMove = pMove->next;
	}
	printf("\n");
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{

	if(!l1 && !l2)return NULL;
	ListNode* pL1Move = l1;
	ListNode* pL2Move = l2;
	int carryFlag = 0;
	//stack *pStack = NULL;
	queue *pQueue = NULL;
	while(pL1Move || pL2Move)
	{
		int bit = ((pL1Move?pL1Move->val:0) + (pL2Move?pL2Move->val:0) + carryFlag)%10;
		//printf("bit=%d\n", bit);
		carryFlag = ((pL1Move?pL1Move->val:0) + (pL2Move?pL2Move->val:0) + carryFlag)/10;
		//printf("carryFlag=%d\n", carryFlag);
		ListNode *node = (ListNode*)calloc(1, sizeof(ListNode));
		node->val = bit;
		push(&pQueue, node);
		if(pL1Move)pL1Move = pL1Move->next;
		if(pL2Move)pL2Move = pL2Move->next;			
	}
	if(carryFlag)
	{
		ListNode *node = (ListNode*)calloc(1, sizeof(ListNode));
		node->val = carryFlag;
		push(&pQueue, node);
	}
	print(pQueue);
	return pQueue ? pQueue->top : NULL;
}

