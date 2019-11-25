#include<stdio.h>
#include<stdlib.h>

double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
	if((!nums1 && !nums2) || (nums1Size<=0 && nums2Size <= 0))return 0.0;
	if(!nums1)
		return nums2Size%2 == 0 ? (*(nums2 + nums2Size/2 ) + *(nums2 + nums2Size/2 - 1)) / 2 : *(nums2 + nums2Size / 2);
	else if(!nums2)
		return nums1Size%2 == 0 ? (*(nums1 + nums1Size/2) + *(nums1 + nums1Size/2 - 1)) / 2 : *(nums1 + nums1Size / 2);
	int *minArrays = nums1Size <= nums2Size ? nums1 : nums2;
	int *maxArrays = minArrays == nums1 ? nums2 : nums1;
	int minSize = nums1Size <= nums2Size ? nums1Size : nums2Size;
	int maxSize = minSize == nums1Size ? nums2Size : nums1Size;
	int i = minSize / 2;
	int j = (minSize + maxSize + 1) / 2 - i;
	while(i < minSize && i > 0)
	{
		if( *(minArrays + i - 1) <= *(maxArrays + j ) &&  *(minArrays + i ) >= *(maxArrays + j - 1 ))
			return (maxSize + minSize) % 2 == 0 ? ((*(minArrays + i - 1) >= *(maxArrays + j - 1) ? *(minArrays + i - 1) : *(maxArrays + j - 1)) + (*(minArrays + i) <= *(maxArrays + j) ? *(minArrays + i) : *(maxArrays + j ))) * 1.0 / 2 : *(minArrays + i - 1) >= *(maxArrays + j- 1) ? *(minArrays + i - 1 ) : *(maxArrays + j -1) ; 
		
		
		if(*(minArrays + i - 1) > *(maxArrays + j ))
			i = i / 2;
		else
			i = i + ((minSize - i) / 2 < 1 ? 1 : (minSize - i) / 2);
		j = (minSize + maxSize + 1) / 2 - i;
	}

	

	if(i == minSize )
	{
		if((maxSize + minSize) % 2 == 0)
		{		
			int index1 = (maxSize + minSize) / 2 - 1;
			int index2 = (maxSize + minSize) / 2;
			return ((*maxArrays+index2-i) + (index1<i ? *minArrays+index1 : *maxArrays+index1-i)) * 1.0 / 2;
		}
		else
			return *maxArrays + (maxSize + minSize) / 2 - i;
	}
	else
	{
		if((maxSize + minSize) % 2 == 0)
		{
			int index1 = (maxSize + minSize) / 2 - 1;
			int index2 = (maxSize + minSize) / 2;
			return ((*maxArrays+index1) + (index2 >= j ? *minArrays : (*maxArrays+index2))) * 1.0 / 2;
		}
		else
			return *maxArrays + (maxSize + minSize) / 2;
	}
}

int main(void)
{
	int a[] = {1};
	int b[] = {2,3};
	printf("%f\n", findMedianSortedArrays(a, sizeof(a)/sizeof(a[0]), b, sizeof(b)/sizeof(b[0])));
	return 0;
}
