#include<stdio.h>
#include<stdlib.h>

int max(int a, int b){
	return a > b ? a : b;
}

int rob(int* nums, int numsSize){
	if(numsSize <= 0) return 0;
	else if(numsSize == 1) return *nums;
	int s1_0 = 0, s1_1 = *nums, s2_0 = 0, s2_1 = 0;
	int i;
	for(i=2;i<numsSize+1;i++){
		if(i < numsSize){
			s1_0 = max(s1_0 + *(nums + i - 1), s1_1);
			s1_0 = s1_0 + s1_1;
			s1_1 = s1_0 - s1_1;
			s1_0 = s1_0 - s1_1;
		}
		if(i==2) s2_1 = *(nums+1);
		else{
			s2_0 = max(s2_0 + *(nums + i - 1), s2_1);
			s2_0 = s2_0 + s2_1;
			s2_1 = s2_0 - s2_1;
			s2_0 = s2_0 - s2_1;
		}
	}
	printf("s1=%d, s2=%d\n", s1_1, s2_1);
	return max(s1_1, s2_1);
}

int main(void){
	int a[] = {1,2,3,1};
	int size = sizeof(a) / sizeof(a[0]);
	printf("result is %d\n", rob(a, size));
	return 0;
}
