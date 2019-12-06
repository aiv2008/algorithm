#include<stdio.h>
#include<stdlib.h>

#define bool int
#define true 1
#define false 0

bool isMatch(char *s, char *p)
{
	char *pSMove = s;
	char *pPMove = p;
	return dp(s, p, pSMove, pPMove);
}

bool dp(char *s, char *p, char *ps, char *pp)
{
	printf("%c, %d ,%c, %d\n", *ps, ps - s, *pp, pp - p);
	if(*ps == '\0' && *pp == '\0') {
		return true;
	}
	else if(*pp == '\0') return false;
	else if(*pp == '*') return false;
	if(*(pp + 1) != '*') {
		if( *pp == '.' || *pp == *ps ) return dp(s, p, ps, pp+1);
		else return false;
	} else {
		if(*pp == '*')
		{
			//if(pp == p) return false;
			//匹配0个字符, 包含了当两字符不相等时, 后面一个也是*的情况
			bool r = dp(s, p, ps, pp + 1);
			//printf("status=%d\n", status);
			//printf("5555\n");
			//printf("5555: %c, %c\n", *ps, *pp);
			char c = *(pp - 1);
			if( *ps == c || c == '.' )
			{
				//匹配1个字符
				if(*ps == '\0') r = dp(s, p, ps, pp + 1);
				else r = dp(s, p, ps + 1, pp + 1);
				//匹配2个字符
				if(!r && *ps != '\0') r = dp(s, p, ps + 1, pp);
			}
			return r;
		}
		else
		{//current character not equals each other
			//printf("6666\n");
			if(*ps == '\0') return false;
			else return dp(s, p, ps, pp + 1);
		}
	}
}

int main(void)
{
/**
	char s[30], p[30];
	printf("enter s:\n");
	gets(s);
	printf("enter p:\n");
	gets(p);
**/

	char *s = "bbbba";
	char *p = ".*a*a";

	printf("%d\n", isMatch(s, p));
	return 0;
}
