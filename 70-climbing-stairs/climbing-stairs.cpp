class Solution {
    #define MAXN 50
    int dp[MAXN];
public:
    int climbStairs(int n) {
        memset(dp, 0, MAXN * sizeof(int));

        dp[0] = 0;
        dp[1] = 1;
        dp[2] = dp[1] + 1;
        
        for (int i = 3; i <= n; i++)
            dp[i] = dp[i-1] + dp[i-2];
        return dp[n];
    }
};