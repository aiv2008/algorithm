class Solution(object):
    def rob_o(self, nums):
        # 依照上面的思路，其实我们用到的数据永远都是dp的dp[i-1]和dp[i-2]两个变量
        # 因此，我们可以使用两个变量来存放前两个状态值
        # 空间使用由O(N) -> O(1)

        size = len(nums)
        if size == 0:
            return 0

        dp1 = 0
        dp2 = nums[0]
        for i in range(2, size+1):
            dp1 = max(dp2, nums[i-1]+dp1)
            dp1, dp2 = dp2, dp1
        return dp2

    def rob(self, nums):
      # 1.dp[i] 代表当前最大子序和
      # 2.动态方程: dp[i] = max(dp[i-1], nums[i-1]+dp[i-2])
      # 3.初始化: 给没有房子时，dp一个位置，即：dp[0]
      #   3.1 当size=0时，没有房子，dp[0]=0；
      #   3.2 当size=1时，有一间房子，偷即可：dp[1]=nums[0]
        size = len(nums)
        if size == 0:
            return 0

        dp = [0 for _ in range(size+1)]

        dp[0] = 0
        dp[1] = nums[0]
        for i in range(2, size+1):
            dp[i] = max(dp[i-1], nums[i-1]+dp[i-2])
            print("i = {}, dp={}".format(i, dp[i]))
        return dp[size]

if __name__ == "__main__":
    solution = Solution()
    nums = [2,1,1,2]
    #result = solution.rob_o(nums)
    #print(result)
    result = solution.rob(nums)
    print(result)

