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

bool dp(char *s, char *p, char *ps, char *pp, bool status)
{
	printf("%c, %c\n", *ps, *pp);
	if(*ps == '\0' && *pp == '\0') 
	{
		printf("1111\n");
		return true;
	}
	else if(*pp == '\0') return false;
	if(*ps == *pp || *pp == '.') 
	{
		printf("2222\n");
		return dp(s, p, ps + 1, pp + 1, 1);
	}
	else
	{
		if(*pp == '*')
		{
			//* matchs 0 char
			bool r = dp(s, p, ps, pp + 1, 1);
			printf("status=%d\n", status);
			if(status)
			{
				if(!r && *ps != '\0')
				{
					printf("5555\n");
					printf("5555: %c, %c\n", *ps, *pp);
					if(pp == p) return false;
					char c = *(pp - 1);
					if( *ps == c || c == '.')
					{
						printf("3333\n");
						r = dp(s, p, ps + 1, pp + 1, 1);
						if(!r) 
						{
							printf("4444\n");
							r = dp(s, p, ps + 1, pp, 1);
						}
						return r;
					}
					else return false;
				}
			}
			else return r;
		}
		else
		{//current character not equals each other
			printf("6666\n");
			return dp(s, p, ps, pp + 1, 0);
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

	char *s = "ab";
	char *p = ".*c";
	printf("%d\n", isMatch(s, p));
	return 0;
}
