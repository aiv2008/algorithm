#include<stdio.h>
#include<stdlib.h>
#include"../common/vector.h"
#include"../common/tree.h"


void recoverTree(struct TreeNode* root){
	//dfs(root);
}

void swap(int *a, int *b) {
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b){
	return a < b  ? a : b;
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
		if(endIndex - startIndex + 1 == 2) {
			struct TreeNode* startNode = (struct TreeNode*)vectorGet(vector, startIndex);
			struct TreeNode* endNode = (struct TreeNode*)vectorGet(vector, endIndex);
			if(startNode->val > endNode->val) {
				startNode->val = startNode->val + endNode->val;
				endNode->val = startNode->val - endNode->val;
				startNode->val = startNode->val - endNode->val;
			}
			return;
		}  
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
	for(j=startIndex;j<endIndex-1;j++){
		jNode = (struct TreeNode*)vectorGet(vector, j);
		if(jNode->val <= node->val) {
			iNode = (struct TreeNode*)vectorGet(vector, ++i);
			//这里增加a，b两个变量， 是防止iNode==jNodeD的情况
			a = iNode->val, b = jNode->val;
			a = a + b;
			b = a - b;
			a = a - b;
			iNode->val = a;
			jNode->val = b;
			
		}
	}
	printf("i=%d, r=%d\n", i, endIndex);
	iNode = (struct TreeNode*)vectorGet(vector, ++i);
	printf("--begin print vector---\n");
	printVector(vector);	
	printf("---end print vector---\n");

	a = iNode->val, b = node->val;
	a = a + b;
	b = a - b;
	a = a - b;
	iNode->val = a;
	node->val = b;
	printf("--begin print vector---\n");
	printVector(vector);	
	printf("---end print vector---\n");
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

/**
void dfs(struct TreeNode* root){	
	if(root == NULL ||(root->left == NULL && root->right == NULL)) return;
	struct TreeNode* node = NULL;
	if(root->left != NULL) {
		node = root->left;
		dfs(node);
		//root->val = max(root->val, node->val);
		//node->val = min(root->val, node->val);
		if(root->val < node->val) swap(&root->val, &node->val);
	}
	if(root->right != NULL) {
		node = root->right;
		dfs(node);
		//node->val = max(root->val, node->val);
		//root->val = min(root->val, node->val);
		if(root->val > node->val) swap(&root->val, &node->val);
	}
}
**/

int main(void) {
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
		if(a[i] > 0 ) {
			node = initTreeNode(a[i]);
                	//vectorAdd(&vector, node);
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

	//printf("---begin print tree---\n");
	//treeIterator(root);	
	//printf("---end print tree---\n");

	//printf("---befor quicksort---\n");
	Vector *vct = NULL;
	inorderTraversal(root, &vct);
	//printVector(vct);
	quicksort(vct, 0, vectorSize(vct)-1);
	
	//printf("---after quicksort---\n");
	//printVector(vct);	

//	recoverTree(root);

	//printf("---begin print tree2222---\n");
	//treeIterator(root);	
	//printf("---end print tree222---\n");


	return 0;

}
