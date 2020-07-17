#include<stdio.h>
#include<stdlib.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


typedef struct {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode; 


typedef struct{
	int val;
	struct StackNode* next;
} StackNode;

typedef struct{
	struct StackNode* top;
	struct StackNode* bottom;
} Stack;

int max(int a, int b){
	return a > b ? a : b;
}

void stackPush(Stack** stack, int val) {
	if(stack == NULL) return;
	StackNode* node = (StackNode*)malloc(sizeof(StackNode));
	node->val = val;
	if(*stack == NULL) {
		*stack = (Stack*)malloc(sizeof(Stack));
		(*stack)->top = node;
		(*stack)->bottom = node;
	} else {
		((StackNode*)((*stack)->bottom))->next = node;
		(*stack)->bottom = node;
	}
}

StackNode* stackTop(Stack* stack){
	return stack == NULL ? NULL : stack->top;
}
StackNode* stackBottom(Stack* stack) {
	return stack == NULL ? NULL : stack->bottom;
}

void stackPop(Stack* stack) {
	if(stack == NULL) return;
	StackNode* top = stackTop(stack);
	StackNode* bottom = stackBottom(stack);
	if(top == bottom) {
		//free(top);
		stack->top = NULL;
		//free(bottom);
		stack->bottom = NULL;
	} else {
		StackNode* tmpNode = top;
		stack->top = top->next;
		tmpNode->next = NULL;
		//free(tmpNode);
		tmpNode = NULL;
	}
}

int *postTrasval(TreeNode* node) {
	int *dp = (int*)calloc(2, sizeof(int));
	*dp = 0;
	*(dp+1) = 0;
	if(node == NULL) return dp;
	if(node->left == NULL && node->right == NULL) {
		*dp = 0;
		*(dp+1) = node->val;
		return dp;
	}
	int* left = (int*)calloc(2, sizeof(int));
	int* right = (int*)calloc(2, sizeof(int));
	memcpy(left, dp, 2*sizeof(int));
	memcpy(right, dp, 2*sizeof(int));
	left = postTrasval(node->left);
	right = postTrasval(node->right);
	*dp = max(*left + *right, *(left+1) + *(right+1));
	*(dp+1) = max(*left + *right + node->val, *(left+1) + *(right+1));
	return dp;
}

int rob(struct TreeNode* root){
	int *result = postTrasval(root);
	return max(*result, *(result+1));
}


int main(void){
	TreeNode *root = NULL;
	int a[] = {3,2,3,-1,3,-1,1};
	int size = sizeof(a) / sizeof(a[0]);
	int i;
	Stack *stack = NULL;
	for(i=0;i<size;i++){
		stackPush(&stack, a[i]);
	}
	while(stack != NULL) {
		StackNode* top = stackTop(stack);
		printf("%d,", top->val);
		stackPop(stack);
	}
	printf("\n");	
	//free(stack);
	stack = NULL;
	
	return 0;
}
