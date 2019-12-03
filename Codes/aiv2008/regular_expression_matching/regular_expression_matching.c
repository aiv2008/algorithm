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
	if(*pSMove == '\0') 
	{
		char *pPMoveMove = pPMove;
		while(*pPMoveMove != '\0')
		{
			if(*pPMoveMove != '*') return false;
			pPMoveMove++;
		}
		return true;
	}
	if(status)
	{
		if(*pPMove == '.' || *pPMove == *pSMove) return dp(s, p, ++pSMove, ++pPMove, 1);
		else if(*pPMove == '*')
		{
			if(*pSMove == *(pSMove-1)) return dp(s, p, ++pSMove, pPMove, 1);
			else 
			{
				if(*(pPMove - 1) == '.') return dp(s, p, ++pSMove, ++pPMove, 1);
				else dp(s, p, pSMove, ++pPMove, 1);
			}
		}
		else return false;
	}
	else
	{
		if( *pPMove == '*' ) return dp(s, p, pSMove, ++pPMove, 1);
		else return false;
	}
}


int main(void)
{
	printf("%d\n", isMatch("aa", "a*"));
	return 0;
}
