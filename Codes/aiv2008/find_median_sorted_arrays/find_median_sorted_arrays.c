#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define POS_INFINITY INT_MAX
#define NAG_INFINITY -128

double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
	double result = 0.0;
	if((!nums1 && !nums1Size && !nums2 && !nums2Size) || nums1Size < 0 || nums2Size < 0) return result;

	int moreSize = nums1Size < nums2Size ? nums2Size : nums1Size;
	int lessSize = moreSize == nums1Size ? nums2Size : nums1Size;
	int totalSize = moreSize + lessSize;
	//avoid assessing the illegal memory
	if(!lessSize)
	{
		printf("enter here\n");
		int *nums = (!nums1 || !nums1Size) ? nums2 : nums1;
		printf("nums=%d\n", *nums);
		return moreSize % 2 == 0 ? (*(nums + totalSize / 2 - 1) + *(nums + totalSize / 2)) * 1.0 / 2 : *(nums + totalSize / 2);
	}

	int *pMore = nums1Size < nums2Size ? nums2 : nums1;
	int *pLess = pMore == nums1 ? nums2 : nums1;
	
	int i = lessSize < 2 ? lessSize : lessSize / 2;
	//int i = lessSize;
	int j = (totalSize + 1) / 2 - i;
	while(i > 0 && i <= lessSize)
	{
		int leftIIndex = i - 1;
		int leftJIndex = j - 1;
		int rightIIndex = i;
		int rightJIndex = j;
		int leftIMax = leftIIndex < 0 ? NAG_INFINITY : *(pLess+leftIIndex);
		int leftJMax = leftJIndex < 0 ? NAG_INFINITY : *(pMore +leftJIndex);
		int rightIMin = rightIIndex >= lessSize ? POS_INFINITY : *(pLess + rightIIndex);
		int rightJMin = rightJIndex >= moreSize ? POS_INFINITY : *(pMore + rightJIndex) ;
		if( leftIMax <= rightJMin && leftJMax <= rightIMin )
		{
			result = totalSize % 2 == 0 ? (max(leftIMax, leftJMax) + min(rightIMin, rightJMin)) * 1.0 / 2 : max(leftIMax, leftJMax);
			break;
		}
		if( leftIMax > rightJMin )
		{
			i = i < 2 ? i - 1 : i / 2;
		}
		else if(leftJMax > rightIMin)
		{
			i = i < 2 ? i + 1 : i + (lessSize - i) / 2;
		}
		j = j = (totalSize + 1) / 2 - i;
	}
	
	if(i == 0)
	{
		if(totalSize % 2 == 0)
		{
			int leftIndex = totalSize / 2 - 1;
			int rightIndex = totalSize / 2 ;
			int leftVal = *(pMore + leftIndex);
			int rightVal = 0;
			if( rightIndex >=  moreSize) rightVal = *pLess;
			else rightVal = *(pMore + rightIndex);
			result = (leftVal + rightVal) * 1.0 / 2;
		}
		else
		{
			int index = totalSize / 2;
			result = *(pMore + index );
		}
	}
	else if( i == lessSize + 1)
	{//i==lessSize+1
		if(totalSize % 2 == 0)
		{
			int leftIndex = totalSize / 2 - 1;
			int rightIndex = totalSize / 2 ;
			int leftVal = 0;
			int rightVal = *(pMore + rightIndex - lessSize);
			if(leftIndex < 0) leftVal = *(pLess + lessSize - 1);
			else leftVal = *(pMore + leftIndex);
			result = (leftVal + rightVal) * 1.0 / 2;
		}
		else
		{
			int index = totalSize / 2;
			result = *(pMore + index - lessSize - 1);
		}
	}

	return result;
}

int min(int i, int j)
{
	return i <= j ? i : j;
}

int max(int i, int j)
{
	return i >= j ? i : j;
}

int main(void)
{
	int a[] = {3};
	int b[] = {1,2,4};
	printf("%f\n", findMedianSortedArrays(a, sizeof(a)/sizeof(a[0]), b, sizeof(b)/sizeof(b[0])));
	return 0;
}
