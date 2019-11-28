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
	int i = 0;
	int j = 0;
	char result[rowNums][colNums];
	char *pMove = s;
	int colIndex = 0;
	while(*pMove != '\0')
	{
		
		result[i][j] = *pMove;
		if(i == 0 || j == colIndex )
		{
			if(i == 0) colIndex == j;
			i++;
		}
		else if(i == rowNums || j != colIndex)
		{
			i--;
			j++;
		}
		pMove++;
	}
	char *header = (char*)calloc(len+1, sizeof(char));
	pMove = header;
	for(i=0;i<rowNums;i++)
		for(j=0;j<colNums;j++)
		{
			if(result[i][j] != '\0')
			{
				*pMove = result[i][j];
				pMove++;
			}
		}
	*pMove = '\0';
	return header;
}


int main(void)
{
	//char *s = "";
	char a[2][2];
	int i,j;
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
		{
			printf("%c,", a[i][j]);
			printf("%d\n", a[i][j]=='\0'? 1 : 0);
		}

	char **b = (char**)calloc(2, sizeof(char*));
	
	return 0;
}
