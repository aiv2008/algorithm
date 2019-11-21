#ifndef ADD_TWO_NUMBERS_H_INCLUDED
#define ADD_TWO_NUMBERS_H_INCLUDED

typedef struct 
{
	int val;
	struct ListNode *next;
} ListNode;

typedef struct
{
	ListNode* top;
	ListNode* bottom;
} queue;

/**
typedef struct
{
	ListNode* top;
	ListNode* bottom;
} stack;
**/

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2);

#endif
