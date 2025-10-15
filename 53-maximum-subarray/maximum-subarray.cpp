/*
    dp[i] : largest sum of a subarray, that contains nums[i] and ends at i.
    dp[0] = nums[0]
    dp[i+1] = max(dp[i] + nums[i+1], nums[i+1])
*/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxSum = nums[0];
        int sum = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            sum = max(sum + nums[i], nums[i]);
            maxSum = max(maxSum, sum);
        }
        return maxSum;
    }
};

