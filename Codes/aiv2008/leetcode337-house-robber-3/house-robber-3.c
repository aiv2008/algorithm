#include<stdio.h>
#include<stdlib.h>
#include "../common/vector.h"
#include "../common/tree.h"

/**
typedef struct {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode; 
**/

typedef struct{
	char* val;
	struct StackNode* next;
} StackNode;

typedef struct{
	struct StackNode* top;
	struct StackNode* bottom;
} Stack;

/**
typedef struct{
	int size;
	int capacity;
	char** element;
} Vector;
**/


int max(int a, int b){
	return a > b ? a : b;
}

/**
void vectorAdd(Vector** vector, char* element){
	if(vector == NULL) return;
	if(*vector == NULL) {
		*vector = (Vector*)malloc(sizeof(Vector));
		(*vector)->element = (char**)calloc(8, sizeof(char*));
		(*vector)->capacity = 8;
	}
	if((*vector)->size == (*vector)->capacity) {
		int capacity = (*vector)->capacity;
		(*vector)->capacity = capacity + capacity >> 1;
		char** newElement = (char**)calloc((*vector)->capacity, sizeof(char*));
		memcpy(newElement, (*vector)->element, (*vector)->size*sizeof(char*));
		free((*vector)->element);
		(*vector)->element = newElement;
	}
	*((*vector)->element + (*vector)->size) = element;
	(*vector)->size++;
}

char* vectorGet(Vector* vector, int index){
	if(vector == NULL||index<0) return NULL;
	return *(vector->element+index);
}

int vectorSize(Vector* vector) {
	return vector == NULL ? 0 : vector->size;
}
**/

int *postTrasval(TreeNode* node) {
	int *dp = (int*)calloc(2, sizeof(int));
	*dp = 0;
	*(dp+1) = 0;
	if(node == NULL) return dp;
	if(node->left == NULL && node->right == NULL) {
		*dp = 0;
		*(dp+1) = node->val < 0 ? 0 : node->val;
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

/**
TreeNode* initTreeNode( int val){
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->val = val;
	return node;
}
**/


int main(void){
	int a[] = {3,4,5,1,3,-1,1};
	int size = sizeof(a) / sizeof(a[0]);
	int i=0;
	int j=0;
	Vector* vector = NULL;	
	TreeNode* root = initTreeNode(a[0]);
	TreeNode* thisNode = root;
	vectorAdd(&vector, thisNode);
	for(i=1;i<size;i++){
		TreeNode* node = initTreeNode(a[i]);
		vectorAdd(&vector, node);
		thisNode = (TreeNode*)vectorGet(vector, j);
		if(thisNode == NULL) break;
		if(thisNode->left == NULL) {
			thisNode->left = node;
		} else{
			thisNode->right = node;
			thisNode = vectorGet(vector, ++j);
		}
	}	

	size = vectorSize(vector);
	for(i=0;i<size;i++){
		TreeNode* node = (TreeNode*)vectorGet(vector, i);
		printf("root=%d, left=%d, right=%d\n", node->val, node->left == NULL ? -1 : ((TreeNode*)(node->left))->val, node->right == NULL ? -1 : ((TreeNode*)(node->right))->val);
	}

	printf("result is %d", rob(root));

	return 0;
}


/** 
void stackPush(Stack** stack, char* val) {
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
		free(top);
		stack->top = NULL;
		//free(bottom);
		stack->bottom = NULL;
	} else {
		StackNode* tmpNode = top;
		stack->top = top->next;
		tmpNode->next = NULL;
		free(tmpNode);
		tmpNode = NULL;
	}
}
**/
