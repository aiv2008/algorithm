#include<stdio.h>
#include<stdlib.h>

int uniquePaths(int m, int n){
	int i;
	int j;
	int dp[m][n];
	dp[0][0] = 1;
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			if(i-1<0&&j-1<0)continue;
			else if(i-1<0) dp[i][j] = dp[i][j-1];
			else if(j-1<0) dp[i][j] = dp[i-1][j];
			else dp[i][j] = dp[i-1][j] + dp[i][j-1];
		}
	}
	return dp[m-1][n-1];			
}

unsigned long uniquePathsEx(int m,int n){
	int i;
	int j;
	unsigned long dp[m][n];
	dp[0][0] = 1;
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			if(i-1<0&&j-1<0)continue;
			else if(i-1<0) dp[i][j] = dp[i][j-1];
			else if(j-1<0) dp[i][j] = dp[i-1][j];
			else dp[i][j] = dp[i-1][j] + dp[i][j-1];
		}
	}
	return dp[m-1][n-1];			
}



int uniquePathsEx1(int m, int n){
	int i;
	int j;
	if(m==1) return 1;
	//int dp[2][n];
	int dp[n];
	//dp[0][0] = 1;
	for(i=0;i<n;i++) dp[i] = 1;
	for(i=1;i<m;i++){
		for(j=1;j<n;j++){
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
