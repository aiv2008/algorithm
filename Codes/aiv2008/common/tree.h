#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};


struct TreeNode* initTreeNode( int val);


void treeIterator(struct TreeNode* root);

#endif
