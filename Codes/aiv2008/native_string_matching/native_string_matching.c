#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void nativeStringMatching(char *s, char*p) {
	int sLen = strlen(s);
	int pLen = strlen(p);
	int i=0;
	while(i < sLen - pLen + 1) {
		int j=0;
		int k=i;
		while(j < pLen) {
			if(*(s+k) == *(p+j)) {
				if(k == sLen) {
					break;
				}
				k++;
				j++;
			} else {
				break;
			}
		}
		if( j == pLen ) {
			printf("matching successfully in the %d index of s!\n", i);
		}
		i++;
	}
}

int main(void) {
	char p[30], s[30];
	printf("input s:\n");
	gets(s);
	printf("input p:\n");
	gets(p);
	char *ss = (char*)calloc(strlen(s)+1, sizeof(char));
	char *pp = (char*)calloc(strlen(p)+1, sizeof(char));
	strcpy(ss, s);
	strcpy(pp, p);
	nativeStringMatching(ss, pp);
	return 0;
}
