#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
大致思路: 先归纳出规律
1. 当行数为第一行或者最后一行时, 输出的字符的间隔为: per = rowNums+rowNums-2, 例如: LEETCODEISHIRING, rowNums=4, 
	则per=4+4-2=6, 亦即第一行的位置为0, 6, 12, 即L, D, R
2. 当行数不符合1条件时, 亦即头行和尾行夹着的行, 输出的字符除了符合条件1外, 
	中间的字符在原字符串的位置是第一行的每个字符减去行数(要满足该字符的索引就要大于0)
**/
char *convert(char *s, int rowNums)
{
	if(!s || !*s) return "";
	if(!rowNums || rowNums == 1) return s;
	int len = strlen(s);
	if(rowNums >= len) return s;
	int per = rowNums+rowNums-2;
	//int colNums = len / per*(rowNums-1);
	//int modNums = len % per;
	//modNums = modNums == 0 ? 0 : (modNums <= rowNums ? 1 : modNums - rowNums + 1);
	//colNums = colNums + modNums;
	char *result = (char*)calloc(len+1, sizeof(char));
	char *pMove = result;
	int i,j=0;
	for(i=0;i<rowNums;i++)
	{
		
		while(i + j * per < len)
		{
			//printf("i=%d, j=%d, i + j * per=%d\n", i, j, i + j * per);
			int index = i + j * per;
			memcpy(pMove, s + index, sizeof(char));
			//printf("aaa\n");
			//printf("%c\n", *pMove);
			pMove++;			
			//if(i==0 || i==rowNums - 1)
			//{
			//}
			if(i!=0 && i!=rowNums - 1)
			//else
			{
				int index2 = (j + 1) * per - i;	
				//printf("index2=%d\n", index2);
				if(index2 > 0 && index2 < len)
				{
					memcpy(pMove, s + index2, sizeof(char));
					//printf("bbb\n");
					//printf("%c\n", *pMove);
					pMove++;
				}
			}
			j++;
		}
		j = 0;
	}
	*pMove = '\0';
	return result;
}

int main(void)
{
	char *s = "LEETCODEISHIRING";
	int rowNums = 4;
	char *result = convert(s, rowNums);
	char *pMove = result;
	while(*pMove != '\0')
		printf("%c", *pMove++);
	printf("\n");
	return 0;
}
