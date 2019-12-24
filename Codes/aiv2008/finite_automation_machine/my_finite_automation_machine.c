#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//calculate the max length of intersection the suffix of a and the prefix of b
int sigma(char *a, int aLen, char *b, int bLen) {
	if(!a || !b || !strlen(a) || !strlen(b)) return 0;
	//int aLen = strlen(a);
	//int bLen = strlen(b);
	int i;
	int result = 0;
	for(i=bLen-1;i>=0;i--) {
		int j = aLen-1;
		int k = i;
		while(1) {
			if(j < 0 || k < 0 || *(a+j) != *(b+k)) break;
			else {
				j--;
				k--;	
			}
		}
		if(k < 0) {
			result = i+1;
			break;
		}
	}
	return result;
}


void test() {
	int rowSize = 2;
	int colSize = 5;
	int a[2][5] = {{1,2,3,4,5},{6,7,8,9,10}};
	printTwoDimension(a,rowSize, colSize) ;
	printf("---end---");
}

void printTwoDimension(int (*p)[3], int rowLen, int colLen) {
	int i;
	for(i=0;i<rowLen;i++) {
		int j;
		for(j=0;j<colLen;j++) {
			//printf("%d, ", *(*(p+i)+j));
			printf("%d,", p[i][j]);
		}
		printf("\n");
	}
}

void printTwoDimension2(int **p, int rowLen, int colLen) {
	int i;
	for(i=0;i<rowLen;i++) {
		int j;
		for(j=0;j<colLen;j++) {
			printf("%d, ", *(*(p+i)+j));
			//printf("%d,", p[i][j]);
		}
		printf("\n");
	}
}

int main(void) {
//	test();
	
	char a[30], b[30];
	printf("please input a: \n");
	gets(a);
	printf("please input b: \n");
	gets(b);
	char *aa = (char*)calloc(strlen(a)+1, sizeof(char));
	char *bb = (char*)calloc(strlen(b)+1, sizeof(char));
	char *pa = a;
	char *pb = b;
	char *paa = aa;
	char *pbb = bb;
	while(*pa != '\0') {
		strcpy(paa, pa);
		pa++;
		paa++;
	}	
	*paa = '\0';
	while(*pb != '\0') {
		strcpy(pbb, pb);
		pb++;
		pbb++;
	}
	*pbb = '\0';
	int **status = NULL;
	initFA(aa, bb, &status);
	int m = strlen(aa);
	int n = strlen(bb);
	printTwoDimension2(status, m+1, n);
	return 0;
}

//initial my finite automation
//p: parameter of pattern
//c: parameter of letters
void initFA(char *p, char *c, int ***status) {
	int m = strlen(p);
	int n = strlen(c);
	if(!status) return;
	if(!*status ) {
		*status = (int**)calloc(m+1, sizeof(int*));
		int i;
		for(i=0;i<m+1;i++){
			*(*status + i) = (int*)calloc(n, sizeof(int));
		}
	}
	int i;
	for(i=0;i<m+1;i++) {
		int j;
		for(j=0;j<n;j++) {
			char *cCopy = (char*)calloc(i+2, sizeof(char));
			if(i > 0) memcpy(cCopy, p, i);
			*(cCopy+i) = *(c+j);
			*(cCopy+i+1) = '\0';
			printf("cCopy=%s, strlen(cCopy)=%d, p=%s, i+1=%d\n", cCopy, strlen(cCopy), p, i+1);	
			int maxLen = sigma(cCopy, strlen(cCopy), p, i+1);
		//	printf("maxLen=%d\n", maxLen);
			*(*(*status+i)+j) = maxLen;
		}
	}
}
