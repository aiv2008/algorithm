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
	void* k;
	void* v;
	struct Entry* next;
} Entry;


typedef struct {
	int capacity;
	int size;
	Entry *entry;
} HashMap;

typedef struct {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode; 


int hashCode( char* key,int len, int size){
	unsigned long h = 0;
	int i;
	for(i=0;i<len;i++) {
        	h = (h << 4) + *(key+i);
        	unsigned long g = h & 0xF0000000L;
        	if (g) {
            	h ^= g >> 24;
        	}
        	h &= ~g;
    	}
    	return h % size;
}

int rob(struct TreeNode* root){
	
}

int main(void){
}
