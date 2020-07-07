#include<stdio.h>
#include<stdlib.h>

int max(int a, int b)
{
	return a > b ? a : b;
}

int rob(int* nums, int numsSize)
{
	if( nums == NULL || numsSize == 0) 
	{
		printf("# of rooms is 0");
		return 0;
	} else if(numsSize == 1)
	{
		return *nums;
	} else if(numsSize == 2)
	{
		return max(*(nums+1), *nums);
	} else
	{
		int dp[numsSize];
		int i;
		dp[0] = *nums;
		dp[1] = *(nums+1);
		for(i=2;i<numsSize;i++)
		{
			dp[i] = max(dp[i-2]+*(nums+i), dp[i-1]);	
			printf("dp is %d\n", dp[i]);
		}
		return dp[numsSize-1];
	}
}	

int main()
{
	int a[] = {1,2,3,1};
	int size = sizeof(a) / sizeof(a[0]);
	printf("size is %d\n", size);
	int result = rob(a, size);
	printf("result is %d\n", result);
	return 0;
}
