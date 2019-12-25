#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//calculate the max length of intersection the suffix of a and the prefix of b
int computePrefixFunction(char *p) {
	if(!p || !strlen(p) || strlen(p) == 1) return 0;
	int i;
	int result = 0;
	char *p1 = p+1;
	while(*p1 != '\0') {
		char *p11 = p1;
		char *p2 = p;
		while(*p11 != '\0' && *(p2+1) != '\0') {
			printf("*p11=%c, *p2=%c\n", *p11, *p2);
			if(*p11 == *p2) {
				p11++;
				p2++;
			} else {
				break;
			}
		}
		if(*p11 == '\0') {
			printf("enter here\n");
			result = p2 - p;
			break;
		}
		p1++;
		printf("\n");
	}
	return result;
}

//return first displacement of the matching
//-1 means no matches
int kmpMatching(char *t, char *p) {
	if(!t || !p || !*t || !*p || !strlen(t) || !strlen(p) || strlen(p) > strlen(t)) return -1;
	char *pt = t;
	char *pp = p;
	int result = -1;
	while(*pt != '\0' && *pp != '\0') {
		if(*pt == *pp) {
			pt++;
			pp++;
		} else {
			int i = pp - p - 1;
			if(i < 0) {
				pt = pt + 1;
			} else {
				char* cCopy = (char*)calloc(i+2, sizeof(char));
				memcpy(cCopy, pp, i+1);
				printf("%d, %s\n", i, cCopy);
				int s = computePrefixFunction(cCopy);
				if(i+s > strlen(t)) break;
				else {
					pp = p;
					pt = pt + s;
				}
			}
		}
	} 
	if(*pp == '\0') {
		result = pt - t;
	}
	return result;
}

int main(void) {
	char t[30], p[30];
	printf("please input t: \n");
	fgets(t, sizeof(t), stdin);
	printf("please input p: \n");
	fgets(p, sizeof(p), stdin);
	char *tt = (char*)calloc(strlen(t)+1, sizeof(char));
	char *pp = (char*)calloc(strlen(p)+1, sizeof(char));
	strcpy(tt, t);
	strcpy(pp, p);
	char *tEnd = strchr(tt, '\n');
	if(tEnd) {
		*tEnd = '\0';
	}
	char *pEnd = strchr(pp, '\n');
	if(pEnd) {
		*pEnd = '\0';
	}
	printf("tt=%s, pp=%s\n", tt, pp);
	printf("s=%d\n", kmpMatching(tt, pp));

/**
	char a[30];
	printf("please input the pattern: \n");
	fgets(a, sizeof(a), stdin);
	char *aa = (char*)calloc(strlen(a)+1, sizeof(char));
	strcpy(aa, a);
	printf("a==%s\n", a);
	printf("aa==%s\n", aa);
	char *end = strchr(aa, '\n');
	if(end) {
		*end = '\0';
	}
	printf("%d\n", computePrefixFunction(aa));
**/
	return 0;
}

