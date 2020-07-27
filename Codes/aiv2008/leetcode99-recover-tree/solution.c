#include<stdio.h>
#include<stdlib.h>
#include"../common/tree.h"
#include"../common/vector.h"

void recoverTree(struct TreeNode* root) {
        struct TreeNode* cur = root;  // 游标
	// s1 存小索引那个结点，s2存大索引那个结点，pre存前驱结点
    	struct TreeNode *s1 = NULL, *s2 = NULL, *pre = NULL;
        while(cur != NULL){           
            if(cur->left != NULL){  // 进入左子树
                // 找到cur的前驱结点，分两种情况
                // 1、cur的左子结点没有右子结点，那cur的左子结点就是前驱
                // 2、cur的左子结点有右子结点，就一路向右下，走到底就是cur的前驱
                struct TreeNode* predecessor = cur->left;
                while(predecessor->right != NULL && predecessor->right != cur){
                    predecessor = predecessor->right;
                }

                // 前驱还没有指向自己，说明左边还没有遍历，将前驱的右指针指向自己，后进入前驱
                if(predecessor->right == NULL){
                    predecessor->right = cur;
                    cur = cur->left;
                }else{
                    // 前驱已经指向自己了，直接比较是否有逆序对，然后进入右子树
                    if(pre != NULL && cur->val < pre->val){
                        if(s1 == NULL) s1 = pre;
                        s2 = cur;
                    }
                    pre = cur;
                    predecessor->right = NULL;
                    cur = cur->right;
                }
            }else{  // 左子树为空时，检查是否有逆序对，然后进入右子树
                if(pre != NULL && cur->val < pre->val){
                    if(s1 == NULL) s1 = pre;
                    s2 = cur;
                }
                pre = cur;
                cur = cur->right;
            }
        }
        // 进行交换
        int t = s1->val;
        s1->val = s2->val;
        s2->val = t;
        return;
}



int main(void) {
	//int a[] = {10,5,15,0,8,13,20,2,-5,6,9,12,14,18,25};
	int a[] = {7,10,4,11,9,5,-1};
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

	return 0;
}

