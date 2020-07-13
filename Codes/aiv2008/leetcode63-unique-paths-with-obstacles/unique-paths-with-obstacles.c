#include<stdio.h>
#include<stdlib.h>

int uniquePaths(int m, int n){
	int i;
	int j;
	int dp[n];
	for(i=0;i<n;i++) dp[i] = 1;
	for(i=1;i<m;i++){
		for(j=1;j<n;j++){
			dp[j] = dp[j] + dp[j-1];
		}
	}
	return dp[n-1];			
}

int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize){
	if(obstacleGridSize == 0 || *obstacleGridColSize == 0) return 0;
	int i;
	int j;
	int dp[*obstacleGridColSize];
	//dp[0] = 1;
	for(i=0;i<*obstacleGridColSize;i++) {
		if(*(*obstacleGrid+i) == 1) dp[i] = 0;
		else {
			if(i==0) dp[i] = 1;
			else dp[i] = dp[i-1];
		}
	}

	for(i=0;i<*obstacleGridColSize;i++) {
		printf("dp=%d,", dp[i]);
	}
	printf("\n");
	

	for(i=1;i<obstacleGridSize;i++) {
		if(*(*(obstacleGrid+i)) == 1) dp[0] = 0;
		for(j=0;j<*obstacleGridColSize;j++){
			if(*(*(obstacleGrid+i)+j) == 1) dp[j] = 0;
			else {
				if(j==0){
					printf("dp=%d,", dp[j]);
					continue;
				}
				else dp[j] = dp[j] + dp[j-1];
			}
			printf("dp=%d,", dp[j]);
		}
		printf("\n");
	}
	return dp[*obstacleGridColSize-1];
	
}

int main(void){
	int m = 1;
	int n = 2;
	int a[][2] = {{1,0}};
	int** b = (int**)calloc(m, sizeof(int*));
	//int rowSize = sizeof(a)/sizeof(a[0]);
	printf("m=%d\n", m);
	int colSize[m];
	int i;
	for(i=0;i<m;i++){
		colSize[i] = sizeof(a[i]) / sizeof(a[i][0]);	
		*(b+i) = (int*)calloc(colSize[i], sizeof(int));
		int j;
		for(j =0;j<n;j++) *(*(b+i)+j) = a[i][j];
	}
	int result = uniquePathsWithObstacles(b, m, colSize);
	printf("result is %d\n", result);
	return 0;
}
