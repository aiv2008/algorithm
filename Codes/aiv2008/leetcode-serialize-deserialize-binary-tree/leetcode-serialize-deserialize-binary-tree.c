#include<stdio.h>
#include<stdlib.h>
#include"../common/tree.h"
#include"../common/vector.h"


typedef struct {
	int capacity;
	int size;
	char *element;
} CVector;

void cVectorAdd(CVector** vector, char element){
        if(vector == NULL) return;
        if(*vector == NULL) {
                *vector = (Vector*)malloc(sizeof(Vector));
                (*vector)->element = (char*)calloc(8, sizeof(char));
                (*vector)->capacity = 8;
               (*vector)->size = 0;
        }
        if((*vector)->size == (*vector)->capacity) {
                int capacity = (*vector)->capacity;
                (*vector)->capacity = capacity + capacity << 1;
                char* newElement = (char*)calloc((*vector)->capacity, sizeof(char));
                memcpy(newElement, (*vector)->element, (*vector)->size*sizeof(char));
                free((*vector)->element);
                (*vector)->element = newElement;
        }
        *((*vector)->element + (*vector)->size) = element;
        (*vector)->size++;
}

int cVectorSize(CVector* vector){
	return vector == NULL ? 0 : vector->size;
}

char* cVectorAll(CVector* vector) {
	return vector == NULL ? NULL : vector->element;
}

char* serialize(struct TreeNode* root) {
	CVector *cVct = NULL;
	cVectorAdd(&cVct , '[');	
	
	if(root != NULL){
		Vector* vector = NULL;
		vectorAdd(&vector, root);
		while(vectorSize(vector)) {
			struct TreeNode* node = (struct TreeNode*)vectorGet(vector, 0);
			cVectorAdd(&cVct, ',');
			if(node == NULL) {
				cVectorAdd(&cVct , 'n');	
				cVectorAdd(&cVct , 'u');	
				cVectorAdd(&cVct , 'l');	
				cVectorAdd(&cVct , 'l');	
			} else {
				int r = node->val;
				while(r) {
					cVectorAdd(&cVct, r/10);
					r = r - r/10;
				}
				cVectorAdd(&cVct, (char)r);
			}
			if(node->left != NULL && node->right != NULL) {
				vectorAdd(&vector, node->left);
				vectorAdd(&vector, node->right);
			}
			vectorDelete(vector, 0);
		}
	}

	cVectorAdd(&cVct , ']');	
	return cVct == NULL ? NULL : cVct->element;
}

struct TreeNode* deserialize(char* data) {

}


int main(void){
//	int a[] = {2,34,5,6,7,3,2,4,56,7,8,39,4};
//	int a[] = {2,3,54,56,6,67,8};
	int a[] = {1,2,3,-1,-1,4,5};
	Vector* vector = NULL;
	int i;
	int size = sizeof(a) / sizeof(a[0]);
	for(i=0;i<size;i++){
		struct TreeNode* node = NULL;
		if(a[i] != -1)
			node = initTreeNode(a[i]);
		vectorAdd(&vector, node);
	}
	
	size = vectorSize(vector);
	int j = 0;
	i = j + 1;
	while(i < size) {
		struct TreeNode* jNode = (struct TreeNode*)vectorGet(vector, j);
		struct TreeNode* iNode = (struct TreeNode*)vectorGet(vector, i++);
		jNode->left = iNode;
		if(i >= size) break;
		iNode = (struct TreeNode*)vectorGet(vector, i++);
		jNode->right = iNode;
		j++;
	}

	treeIterator((struct TreeNode*)vectorGet(vector, 0));

	return 0;
}
