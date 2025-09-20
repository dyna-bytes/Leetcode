class Solution {
    #define MAXN 1005
    int dp[MAXN];
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int N = cost.size();
        dp[0] = cost[0];
        dp[1] = cost[1];

        for (int x = 2; x < N; x++)
            dp[x] = min(dp[x-1], dp[x-2]) + cost[x];

        return min(dp[N-1], dp[N-2]);
    }
};