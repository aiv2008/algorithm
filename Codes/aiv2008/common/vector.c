#include<stdio.h>
#include<stdlib.h>
#include"vector.h"

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

void vectorDelete(Vector* vector, int index){
	if(vector == NULL || index >= vectorSize(vector) || index < 0) return;
	int i;
	char* element = NULL;
	for(i=index+1;i<vectorSize(vector);i++){
		//element = vectorGet(vector, i-1);
//		free(*(vector->element+i-1));
		*(vector->element+i-1) = *(vector->element+i);
	}
//	free(*(vector->element+i-1));
	*(vector->element+i-1) = NULL;
	vector->size--;
}
