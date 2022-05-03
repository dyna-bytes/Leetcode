class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];
        const int IMPOSSIBLE = -1;
        int ret;
        
        vector<vector<int>> dp;
        dp.resize(n+2, vector<int>(2, 0));
        
        // 0번 집을 털고, n-1번 집을 털지 않음
        dp[0][true] = nums[0], dp[0][false] = IMPOSSIBLE;
        for(int here = 1; here < n; here++){
            int prev = here - 1;
            dp[here][true] = dp[prev][false] + nums[here];
            dp[here][false] = max(dp[prev][false], dp[prev][true]);
        }
        ret = dp[n-1][false];
        
        dp.clear();
        dp.resize(n+2, vector<int>(2, 0));
        
        // 0번 집 털지 않고, n-1번 집 털음
        dp[0][true] = IMPOSSIBLE, dp[0][false] = 0;
        for(int here = 1; here < n; here++){
            int prev = here - 1;
            dp[here][true] = dp[prev][false] + nums[here];
            dp[here][false] = max(dp[prev][false], dp[prev][true]);
        }
        ret = max(ret, dp[n-1][true]);
        
        dp.clear();
        dp.resize(n+2, vector<int>(2, 0));
        
        // 0번 집, n-1번 집 둘 다 털지 않음
        dp[0][true] = IMPOSSIBLE, dp[0][false] = 0;
        for(int here = 1; here < n; here++){
            int prev = here - 1;
            dp[here][true] = dp[prev][false] + nums[here];
            dp[here][false] = max(dp[prev][false], dp[prev][true]);
        }
        ret = max(ret, dp[n-1][false]);
        
        return ret;
    }
};