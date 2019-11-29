#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *convert(char *s, int rowNums)
{
	if(!s || !*s) return "";
	if(!rowNums || rowNums == 1) return s;
	int len = strlen(s);
	if(rowNums >= len) return s;
	int colNums = len / (rowNums+rowNums-2)*(rowNums-1);
	int modNums = len % (rowNums+rowNums-2);
	modNums = modNums == 0 ? 0 : (modNums <= rowNums ? 1 : modNums - rowNums + 1);
	colNums = colNums + modNums;
	int i = 0;
	int j = 0;
	//char result[rowNums][colNums];
	char **result = (char**)calloc(rowNums, sizeof(char*));
	char *pMove = s;
	int colIndex = 0;
	while(*pMove != '\0')
	{
		if( !*(result+i) ) *(result + i) = (char*)calloc(colNums, sizeof(char));
		*(*(result+i)+j) = *pMove;
		if(i == 0 )
		{
			colIndex = j;
			i++;
		}
		else if(i == rowNums - 1 )
		{
			i--;
			j++;
		}
		else if(j != colIndex)
		{
			i--;
			j++;
		}
		else if(j == colIndex )
		{
			i++;
		}
		pMove++;
	}
	char *header = (char*)calloc(len+1, sizeof(char));
	pMove = header;
	for(i=0;i<rowNums;i++)
		for(j=0;j<colNums;j++)
		{
			if(*(*(result+i)+j) != '\0')
			{
				*pMove = *(*(result+i)+j);
				pMove++;
			}
		}
	*pMove = '\0';
	return header;
}

int main(void)
{
	char *s = "AB";
	int rowNums = 1;
	char *result = convert(s, rowNums);
	char *pMove = result;
	while(*pMove != '\0')
		printf("%c", *pMove++);
	printf("\n");
	return 0;
}
