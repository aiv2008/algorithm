#include<stdio.h>
#include<stdlib.h>

#define bool int
#define true 1
#define false 0

bool isMatch(char *s, char *p) {
	char *pSMove = s;
	char *pPMove = p;
	return dp(s, p, pSMove, pPMove);
}

bool dp(char *s, char *p, char *ps, char *pp) {
	printf("%c, %d ,%c, %d\n", *ps, ps - s, *pp, pp - p);
	if(*ps == '\0' && *pp == '\0') return true;
	//判断当前字符是否匹配, 包括以下几种情况
	//1. 当前字符相等或者p为'.', 则划分以下两种情况: 
	//(1) 后面一个字符不为'*', 即只匹配一个, 则s和p指针都向后移动一位
	//(2) 后面一个字符为'*', 则又需要划分两种情况:
	//A. s+1和s不相同, 则只可匹配0个或者匹配一个, 即只可匹配当前字符或者匹配0个
	//B. s+1和s相同, 则可匹配0个, 1个或者多个
	//2. 当前字符不相等, 但p后面为'*', 则匹配0个
	//3. 当前字符不相等, 且p后面不为'*', 返回false

	//匹配之后, 操作如下(针对'*'号):
	//1. 匹配0个,s不变, p+2
	//2. 匹配1个, s+1, p+2
	//3. 匹配多个, s+1 , p不变
	if(*ps == '\0' || *pp == '\0') return false;
	if(*ps == *pp || *pp == '.') {//当前字符相等或者p为'.'
		if( *(pp + 1) != '*' ) {//后面一个字符不为'*', 即只匹配一个, 则s和p指针都向后移动一位
			return dp(s, p, ps + 1, pp + 1);
		}else {//后面一个字符为'*'
			if(*ps != *(ps + 1)) {//s+1和s不相同, 则只可匹配0个或者匹配一个
				//匹配0个
				bool r = dp(s, p, ps, pp + 2);
				if(!r) {
					//匹配1个
					r = dp(s, p, ps + 1, pp + 2);
				}
				return r;
			}else {//s+1和s相同, 则可匹配0个, 1个或者多个
				//匹配0个
				bool r = dp(s, p, ps, pp + 2);
				if(!r) {
					//匹配1个
					r = dp(s, p, ps + 1, pp + 2);
					if(!r) {
						//匹配多个
						r = dp(s, p, ps + 1, pp);
					}
				}
				return r;
			}
		}
	} else {//当前字符不相等
		if(*(p+1) == '*') return dp(s, p, ps, pp + 2);
		else return false;
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
