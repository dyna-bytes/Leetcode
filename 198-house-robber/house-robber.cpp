class Solution {
    #define MAXN 105
    int dp[MAXN];
    // dp[n] = max(nums[n] + dp[n-2], dp[n-1])
public:
    int rob(vector<int>& nums) {
        int N = nums.size();
        if (N == 1) return nums[0]; 

        memset(dp, 0, MAXN * sizeof(int));

        dp[0] = nums[0];
        dp[1] = max(dp[0], nums[1]);
        for (int n = 2; n < N; n++)
            dp[n] = max(nums[n] + dp[n-2], dp[n-1]);
        return dp[N-1];
    }
};