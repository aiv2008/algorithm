#include<stdio.h>
#include<stdlib.h>
#include"tree.h"


struct TreeNode* initTreeNode( int val){
        struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        node->val = val;
	node->left = NULL;
	node->right = NULL;
        return node;
}

void treeIterator(struct TreeNode* root){
	if(root != NULL) {
		printf("       %d       \n", root->val);
		printf("     /    \\       \n");
		if(root->left == NULL) 
			printf("    null  ");
		else printf("    %d  ", ((struct TreeNode*)(root->left))->val);
		if(root->right == NULL) 
			printf("  null  \n");
		else printf("  %d  \n", ((struct TreeNode*)(root->right))->val);
		treeIterator(root->left);
		treeIterator(root->right);
	}
}

void treeInorderIterator(struct TreeNode* root){
	if(root == NULL) return;
	treeInorderIterator(root->left);
	printf("       %d       \n", root->val);
	printf("     /    \\       \n");
	if(root->left == NULL) 
		printf("    null  ");
	else printf("    %d  ", ((struct TreeNode*)(root->left))->val);
	if(root->right == NULL) 
		printf("  null  \n");
	else printf("  %d  \n", ((struct TreeNode*)(root->right))->val);
	treeInorderIterator(root->right);
}

void treePostOrderIterator(struct TreeNode* root) {
	if(root == NULL) return;
	treePostOrderIterator(root->left);
	printf("       %d       \n", root->val);
	printf("     /    \\       \n");
	if(root->left == NULL) 
		printf("    null  ");
	else printf("    %d  ", ((struct TreeNode*)(root->left))->val);
	if(root->right == NULL) 
		printf("  null  \n");
	else printf("  %d  \n", ((struct TreeNode*)(root->right))->val);
	treePostOrderIterator(root->right);
}
