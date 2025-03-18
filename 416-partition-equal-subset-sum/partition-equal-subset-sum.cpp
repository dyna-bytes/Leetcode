class Solution {
    vector<vector<int>> dp;
public:
    bool canPartition(vector<int>& nums) {
        int K = 0;
        for (int num: nums) K += num;
        if (K & 1) return false;
        K /= 2;
        dp.resize(nums.size(), vector<int>(K+1, -1));

        return canPartition(nums.size()-1, K, nums);
    }

    bool canPartition(int curr, int sum, const vector<int>& nums) {
        int& ret = dp[curr][sum];
        if (ret != -1) return ret;

        if (curr == 0) {
            ret = (nums[curr] == sum);
            return ret;
        }

        if (canPartition(curr-1, sum, nums)) 
            return ret = true;

        if (sum >= nums[curr])
            return ret = canPartition(curr-1, sum - nums[curr], nums);

        return ret = false;
    }
};