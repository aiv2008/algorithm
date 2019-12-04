#include<stdio.h>
#include<stdlib.h>

#define bool int
#define true 1
#define false 0

bool isMatch(char *s, char *p)
{
	char *pSMove = s;
	char *pPMove = p;
	return dp(s, p, pSMove, pPMove, 1);
}

//用动态规划解决
bool dp(char *s, char *p, char *pSMove, char *pPMove, bool status)
{
	printf("%c, %c\n", *pSMove, *pPMove);
	if(*pSMove == '\0') 
	{
		printf("111\n");
		char *pPMoveMove = pPMove;
		while(*pPMoveMove != '\0')
		{
			if(*pPMoveMove != '*') return false;
			pPMoveMove++;
		}
		return true;
	}
	else
	{
		if((int)(*pSMove) < 97 || (int)(*pSMove)>122 || !(((int)(*pPMove) >= 97 && (int)(*pPMove) <= 122) 
			|| (*pPMove) == '*' || (*pPMove) == '.'))
		{
			printf("222\n");
			return false;
		}
		if(status)
		{
			if(*pPMove == '.' || *pPMove == *pSMove) 
			{
				printf("333\n");
				return dp(s, p, ++pSMove, ++pPMove, 1);
			}
			else if(*pPMove == '*')
			{
				char *pp = pSMove;
				bool b = false;
				while(*pp != '\0' && *pp == *(pp-1) && b == false)
				{
					b = dp(s, p, ++pSMove, pPMove, 1);
					pp++;
				}			
				//if(*pp != '\0')

				/**		
				if(*(pPMove - 1) == '.' || (*pSMove == *(pSMove-1) && *pSMove  == *(pPMove - 1))) 
				{
					printf("444\n");
					//bool r = dp(s, p, ++pSMove, ++pPMove, 1);
					return dp(s, p, ++pSMove, ++pPMove, 1);
				}
				else  
				{
					printf("555\n");
					return dp(s, p, pSMove, ++pPMove, 1);
				}
				**/
			}
			else 
			{
				printf("666\n");
				return dp(s, p, pSMove, ++pPMove, 0);
			}
		}
		else
		{
			if( *pPMove == '*' ) 
			{
				printf("777\n");
				return dp(s, p, pSMove, ++pPMove, 1);
			}
			else 
			{
				printf("888\n");
				return false;
			}
		}
	}
}


int main(void)
{
	char s[30], p[30];
	printf("enter s:\n");
	gets(s);
	printf("enter p:\n");
	gets(p);
	printf("%d\n", isMatch(s, p));
	return 0;
}
