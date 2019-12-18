#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void nativeStringMatching(char *s, char*p) {
	int sLen = strlen(s);
	int pLen = strlen(p);
	int i=0;
	while(i < sLen) {
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
			printf("matching successfully!\n");
		}
		i++;
	}
}

int main(void) {
	nativeStringMatching("aaab","aaa");
	return 0;
}
