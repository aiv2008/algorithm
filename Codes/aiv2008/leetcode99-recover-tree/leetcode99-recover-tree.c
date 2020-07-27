#include<stdio.h>
#include<stdlib.h>
#include"../common/vector.h"
#include"../common/tree.h"

/**
typedef struct {
        int size;
        int capacity;
        char** element;
} Vector;


void vectorAdd(Vector** vector, char* element){
        if(vector == NULL) return;
        if(*vector == NULL) {
                *vector = (Vector*)malloc(sizeof(Vector));
                (*vector)->element = (char**)calloc(8, sizeof(char*));
                (*vector)->capacity = 8;
		(*vector)->size = 0;
        }
        if((*vector)->size == (*vector)->capacity) {
                int capacity = (*vector)->capacity;
                (*vector)->capacity = capacity + capacity << 1;
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

void swap(int *a, int *b){
	*a = *a ^ *b; 
	*b = *a ^ *b; 
	*a = *a ^ *b; 
}


void recoverTree(struct TreeNode* root){
	//Vector *vct = NULL;
	//inorderTraversal(root, &vct);
	//quicksort(vct, 0, vectorSize(vct)-1);
	morrisPre(root);
}


//中序遍历二叉树
void inorderTraversal(struct TreeNode* root, Vector** vector){
	if(root == NULL || vector == NULL) return;
	inorderTraversal(root->left, vector);
	vectorAdd(vector, root);
	inorderTraversal(root->right, vector);
}

void quicksort(Vector *vector, int startIndex, int endIndex) {
	if(vector == NULL || endIndex - startIndex + 1 <= 1 ) return;
	if(startIndex < endIndex) {
		int midIndex = partition(vector, startIndex, endIndex);
		printf("midIndex=%d\n", midIndex);
		quicksort(vector, startIndex, midIndex-1);
		quicksort(vector, midIndex+1, endIndex);
	}
}

int partition(Vector *vector, int startIndex, int endIndex) {
	if(vector == NULL) return -1;
	struct TreeNode* node = (struct TreeNode*)vectorGet(vector, endIndex);
	struct TreeNode* jNode = NULL;
	struct TreeNode* iNode = NULL;
	//int val = node->val;
	int i = startIndex - 1;
	int j;
	int a = 0;
	int b = 0;
	for(j=startIndex;j<endIndex;j++){
		jNode = (struct TreeNode*)vectorGet(vector, j);
		if(jNode->val <= node->val) {
			iNode = (struct TreeNode*)vectorGet(vector, ++i);
			//这里增加a，b两个变量， 是防止iNode==jNodeD的情况
			a = iNode->val, b = jNode->val;
			swap(&a, &b);
			//a = a + b;
			//b = a - b;
			//a = a - b;
			iNode->val = a;
			jNode->val = b;
			
		}
	}
	iNode = (struct TreeNode*)vectorGet(vector, ++i);
	a = iNode->val, b = node->val;
	swap(&a, &b);
	//a = a + b;
	//b = a - b;
	//a = a - b;
	iNode->val = a;
	node->val = b;
	return i;
}

void printVector(Vector *vct){
	if(vct == NULL) return;
	int i;
	for(i=0;i<vectorSize(vct);i++) {
		struct TreeNode* node = (struct TreeNode*)vectorGet(vct, i);
		printf("       %d       \n", node->val);
		printf("     /    \\       \n");
		if(node->left == NULL) 
	                printf("    null  ");
	        else printf("    %d  ", ((struct TreeNode*)(node->left))->val);
        	if(node->right == NULL) 
                	printf("  null  \n");
        	else printf("  %d  \n", ((struct TreeNode*)(node->right))->val);
	}
}



void morrisPre(struct TreeNode* root) {
	if(root == NULL) return;
	struct TreeNode* cur = root;
	struct TreeNode* mr = NULL;
	while(cur != NULL) {
		if(cur->left == NULL) cur = cur->right;
		else{
			mr = cur->left;
//			if(cur->val < mr->val){
//				swap(&cur->val, &mr->val);
//			}
			while(mr->right != NULL && mr->right != cur) {
				struct TreeNode* right = (struct TreeNode*)(mr->right);
//				if(mr->val > right->val) swap(&mr->val, &right->val);
				mr = mr->right;
			}
			if(mr->right == cur) {
				struct TreeNode* right = mr->right;
				if(mr->val > right->val) swap(&mr->val, &right->val);
				mr->right = NULL;
				cur = cur->right;
			} else {
				mr->right = cur;
				struct TreeNode* right = (struct TreeNode*)(mr->right);
				if(right->val > cur->val) swap(&right->val, &cur->val);
				struct TreeNode* left = cur->left;
//				if(cur->left != NULL) 
//					if(cur->val < left->val) swap(&cur->val, &left->val);
				cur = cur->left;
			}
		}
	}
}

int main(void) {
	//int a[] = {10,5,15,0,8,13,20,2,-5,6,9,12,14,18,25};
	int a[] = {3,1,4,-1,-1,2};
	int size = sizeof(a) / sizeof(a[0]);
        int i=0;
        int j=0;
        Vector* vector = NULL;
        struct TreeNode* root = initTreeNode(a[0]);
        struct TreeNode* thisNode = root;
        vectorAdd(&vector, thisNode);
	char flag = 'l';
        for(i=1;i<size;i++){
                struct TreeNode* node = NULL;
		if(a[i] != -1 ) {
			node = initTreeNode(a[i]);
		}
		if(node == NULL) printf("null,");
		else printf("%d,", node->val);
                vectorAdd(&vector, node);
                if(thisNode == NULL) continue;
		if(flag == 'l'){
                        thisNode->left = node;
			flag = 'r';
                } else{
                        thisNode->right = node;
                        thisNode = (struct TreeNode*)vectorGet(vector, ++j);
			flag = 'l';
                }
        }
	printf("\n");

	recoverTree(root);

	printf("---begin print tree2222---\n");
	treeIterator(root);	
	printf("---end print tree222---\n");

/**
	int a = -2147483648;
	int b = 1;
	printf("a=%d, b=%d\n", a, b);
	swap(&a, &b);
	printf("a=%d, b=%d\n", a, b);
**/

	return 0;

}
