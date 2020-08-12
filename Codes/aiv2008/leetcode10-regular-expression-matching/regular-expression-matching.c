#include<stdio.h>
#include<stdlib.h>
#define bool int;
#define true 1;
#define false 0;


bool isMatch(char * s, char * p){
	if(*p == '*') return false;
	char *ps = s;
	char *pp = p;
	while(*ps != '\0' && *pp != '\0') {
		if(*(pp+1) == '*') {
			if(*pp != *ps){
				pp += 2;
			} else {
				
			}
		}	
	}
}
