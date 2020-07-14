#include<iostream>
#include<vector>

using namespace std;

class Solution {
private:
	int max(int a, int b);
public:
    int rob(vector<int>& nums) {
        if( nums.size() == 0) return 0;
	else if(nums.size() == 1) return nums.at(0);
	int size = nums.size();
	int s1_0 = 0, s1_1 = nums.at(0), s2_0 = 0, s2_1 = 0;
	int i;
	for(i=2;i<size+1;i++){
		if(i < size ) {
			s1_0 = max(s1_0 + nums.at(i-1), s1_1);
			s1_0 = s1_0 + s1_1;
			s1_1 = s1_0 - s1_1;
			s1_0 = s1_0 - s1_1;
		}
		if(i==2) s2_1 = nums.at(1);
		else{
			s2_0 = max(s2_0 + nums.at(i-1), s2_1);
			s2_0 = s2_0 + s2_1;
			s2_1 = s2_0 - s2_1;
			s2_0 = s2_0 - s2_1;
		}
	}
	return max(s1_1, s2_1);
    }
};

int Solution::max(int a, int b){
	return a > b ? a : b;
}

int main(){
	Solution solution;
	vector<int> v;
	v.push_back(1);	
	v.push_back(2);	
	v.push_back(3);
	v.push_back(1);	
	cout << solution.rob(v) <<endl;
	return 0;

}
