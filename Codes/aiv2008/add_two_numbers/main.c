#include<stdio.h>
#include<stdlib.h>
#include"add_two_numbers.h"


int main(void)
{
	int a[] = {3,4,4};	
	int sizeA = sizeof(a)/sizeof(a[0]);
	int b[] = {4,6,5};
	int sizeB = sizeof(b)/sizeof(b[0]);
	queue *pQueueA = NULL;
	queue *pQueueB = NULL;
	int i;
	for(i=0;i<sizeA;i++)
	{
		ListNode *node = (ListNode*)calloc(1, sizeof(ListNode));
		node->val = a[i];
		push(&pQueueA, node);
	}
	//print(pQueueA);

	for(i=0;i<sizeB;i++)
	{
		ListNode *node = (ListNode*)calloc(1, sizeof(ListNode));
		node->val = b[i];
		push(&pQueueB, node);
	}
	ListNode *pResult = addTwoNumbers(pQueueA->top, pQueueB->top);

	ListNode *pMove = pResult;
	if(!pMove) printf("list is null\n");
	while(pMove)
	{
		printf("%d,", pMove->val);
		pMove = pMove->next;
	}
	printf("\n");	

	return 0;
}
