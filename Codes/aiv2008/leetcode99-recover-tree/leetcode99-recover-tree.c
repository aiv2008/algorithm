#include<stdio.h>
#include<stdlib.h>
#include"../common/vector.h"
#include"../common/tree.h"


// * Definition for a binary tree node.
/**
struct TreeNode {
 	int val;
 	struct TreeNode *left;
 	struct TreeNode *right;
};
**/


void recoverTree(struct TreeNode* root){
	dfs(root);
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
                //thisNode = (struct TreeNode*)vectorGet(vector, j);
		//if(thisNode == NULL) printf("null,");
		//else printf("%d,", thisNode->val);
                if(thisNode == NULL) continue;
                //if(thisNode->left == NULL) {
		if(flag == 'l'){
                        thisNode->left = node;
			flag = 'r';
                } else{
                        thisNode->right = node;
			//j++;
                        thisNode = (struct TreeNode*)vectorGet(vector, ++j);
			flag = 'l';
                }
        }
	printf("\n");

	printf("---begin print tree---\n");
	treeIterator(root);	
	printf("---end print tree---\n");

	recoverTree(root);
	printf("---begin print tree---\n");
	treeIterator(root);	
	printf("---end print tree---\n");
	return 0;

}
