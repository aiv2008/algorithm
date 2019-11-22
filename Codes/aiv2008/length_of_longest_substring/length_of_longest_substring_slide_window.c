#include<stdio.h>
#include<stdlib.h>

struct
{
	int *top;
	int *bottom;
} Queue;

void push(Queue **ppQueue, int val)
{
	if(!ppQueue)return;
	if(!*ppQueue)
	{
		*ppQueue = (Queue*)calloc(1, sizeof(Queue));
	}
}

void pop(Queue *pQueue)
{

}

int top(Queue *pQueue)
{

}

int lengthOfLongestSubstring(char* s)
{

}
