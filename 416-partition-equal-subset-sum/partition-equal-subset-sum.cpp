class Solution {
    
public:
    bool canPartition(vector<int>& nums) {
        int K = 0;
        for (int num: nums) K += num;
        if (K & 1) return false;
        K /= 2;

        vector<vector<int>> dp(nums.size(), vector<int>(2*K, 0));

        for (int i = 0; i < nums.size(); i++) {
            dp[i][0] = true;
            if (nums[i] <= K) dp[i][nums[i]] = true;
        }

        for (int i = 1; i < nums.size(); i++) {
            for (int s = 0; s <= K; s++) {
                dp[i][s] = (dp[i-1][s]) ||
                (s >= nums[i] && dp[i-1][s-nums[i]]);
            }
            if (dp[i][K]) return true;
        }

        return false;
    }
};