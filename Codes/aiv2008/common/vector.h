#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

typedef struct {
	int size;
	int capacity;
	char** element;
} Vector;

/**
**add the element whose type is char pointer to the vector
**/
void vectorAdd(Vector** vector, char* element);

/**
**get the element whose type is char pointer from the vector
**/
char* vectorGet(Vector* vector, int index);

/**
**get the size of the vector
**/
int vectorSize(Vector* vector) ;


#endif
