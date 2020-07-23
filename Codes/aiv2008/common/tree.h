#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};


struct TreeNode* initTreeNode( int val);

//前序遍历二叉树
void treeIterator(struct TreeNode* root);

//中序遍历二叉树
void treeInorderIterator(struct TreeNode* root);

//后序遍历二叉树
void treePostOrderIterator(struct TreeNode* root);

#endif
