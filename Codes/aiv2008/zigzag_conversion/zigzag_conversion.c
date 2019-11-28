#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *convert(char *s, int rowNums)
{
	int len = strlen(s);
	int colNums = len / (rowNums+rowNums-2)*(rowNums-1);
	int modNums = len % (rowNums+rowNums-2);
	modNums = modNums <= rowNums ? 1 : modNums - rowNums + 1;
	colNums = colNums + modNums;
	char *pMove = s;
	while(*pMove != '\0')
	{
		
	}
}
