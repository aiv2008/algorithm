#include<stdio.h>
#include<stdlib.h>
#include"tree.h"


struct TreeNode* initTreeNode( int val){
        struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        node->val = val;
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

