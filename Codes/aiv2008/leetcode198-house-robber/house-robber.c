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
		int dp[numsSize+1];
		int i;
		dp[0] = 0;
		dp[1] = *nums;
		for(i=2;i<numsSize+1;i++)
		{
			dp[i] = max(dp[i-2]+*(nums+i-1), dp[i-1]);	
			printf("dp is %d\n", dp[i]);
		}
		return dp[numsSize];
	}
}	

int rob_ex(int* nums, int numsSize)
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
		int i;
		int dp_0 = 0;
		int dp_1 = *nums;
		//int tmp = 0;
		for(i=2;i<numsSize+1;i++)
		{
		//	tmp = dp_1;
			dp_0 = max(dp_0+*(nums+i-1), dp_1);
			//dp_0 = tmp;
			//dp[i] = max(dp[i-2]+*(nums+i-1), dp[i-1]);	
			dp_0 = dp_0 + dp_1;  
			dp_1 = dp_0 - dp_1;  
			dp_0 = dp_0 - dp_1;  			
			printf("dp is %d\n", dp_1);
		}
		return dp_1;
	}
}

int main()
{
	int a[] = {2,1,1,3};
	int size = sizeof(a) / sizeof(a[0]);
	printf("size is %d\n", size);
	int result = rob_ex(a, size);
	printf("result is %d\n", result);
	return 0;
}
