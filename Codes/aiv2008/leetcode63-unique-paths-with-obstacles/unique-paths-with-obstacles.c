#include<stdio.h>
#include<stdlib.h>

int uniquePathsWithObstacles(int m, int n){
	int i;
	int j;
	if(m==1) return 1;
	int dp[n];
	for(i=0;i<n;i++) dp[i] = 1;
	for(i=1;i<m;i++){
		for(j=1;j<n;j++){
			if(j==)
			dp[j] = dp[j] + dp[j-1];
		}
	}
	return dp[n-1];			
}

int main(void){
	int m,n;
	printf("input m:\n");
	scanf("%d", &m);
	printf("input n:\n");
	scanf("%d", &n);
	//int m = 50, n = 50;
	printf("result is %d\n", uniquePaths(m,n));
	printf("result is %d\n", uniquePathsEx(m,n));
	printf("result is %d\n", uniquePathsEx1(m,n));
}
