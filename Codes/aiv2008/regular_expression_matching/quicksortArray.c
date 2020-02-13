#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<malloc.h>

void swap(char *a, char *b, int len) {
	char *temp = malloc(len);
	memcpy(temp, a, len);
	memcpy(a, b, len);
	memcpy(b, temp, len);
	free(temp);
	temp = NULL;
}

int myPartition(char* array, int start, int end, int len)
{
	if(array == NULL)
	{
		printf("array cannot be null\n");
		return -1;
	}
	if(start < 0)
	{
		printf("index must begin with 1\n");
		return -1;
	}
	int i = start - 1;
	int j = start;
	if(j < end)
	{
		while(j < end)
		{
			if(*(array+len*j) <= *(array+len*end))
			{
				i++;
				if(i != j)
				{
					swap(array+len*j, array+len*i, sizeof(int));
				}
			}
			j++;
		}
		if(i+1 != end)
		{
			swap(array+len*(i+1), array+len*end, sizeof(int));
			return i+1;
		}
		else
		{
			return end;
		}

	}
	return -1;
}

void myQuicksort(char* array, int start, int end, int len)
{
	if(array == NULL)
	{
		printf("array cannot be null\n");
		return ;
	}
	if(start < end)
	{
		int partitionIndex = myPartition(array, start, end, len);
		if(partitionIndex < 0)
		{
		    printf("partitionIndex must larger than 0\n");
		    return ;
		}
		myQuicksort(array, start, partitionIndex-1, len);
		myQuicksort(array, partitionIndex+1, end, len);
	}
}

int myRandomizedPartition(char* array, int start, int end, int len)
{
	if(start < 0)
	{
		printf("quicksort myRandomizedPartition: index must begin with 1\n");
		return -1;
	}
	if(start > end)
	{
		printf("quicksort myRandomizedPartition: start must smaller than end\n");
		return -1;
	}
	srand(time(0));
    int randIndex = start + rand()%(end - start);
	if(randIndex != end)
			swap(array+len*randIndex, array+len*end, sizeof(int));
	return myPartition(array, start, end, len);
}

void myRandomizedQuicksort(char* array, int start, int end, int len)
{
	if(array == NULL)
	{
		printf("quicksort myRandomizedQuicksort: array cannot be null\n");
		return ;
	}
	if(start < end)
	{
		int partitionIndex = myRandomizedPartition(array, start, end, len);
		if(partitionIndex < 0)
		{
		    printf("quicksort myRandomizedQuicksort: partitionIndex must larger than 0\n");
		    return ;
		}
		myRandomizedQuicksort(array, start, partitionIndex-1, len);
		myRandomizedQuicksort(array, partitionIndex+1, end, len);
	}
}

int main() {
	int a[] = {4,5,6,7,4,21,3,4,1,3,4,6,7,8,109,34,54,32,11};
	int size = sizeof(a)/sizeof(a[0]);
	myRandomizedQuicksort(a, 0, size-1, sizeof(int));
	int i;
	for(i=0;i<size;i++) {
		printf("%d,", a[i]);
	}
	printf("\n");
	return;
}
