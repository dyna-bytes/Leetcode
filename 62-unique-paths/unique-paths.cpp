class Solution {
    typedef long long ll;

public:
    int uniquePaths(int m, int n) {
        int Y = m, X = n;
        vector<vector<ll>> dp(Y, vector<ll>(X, 0));

        dp[0][0] = 1;
        for (int y = 1; y < Y; y++)
            dp[y][0] = dp[y - 1][0];
        for (int x = 1; x < X; x++)
            dp[0][x] = dp[0][x - 1];
        for (int y = 1; y < Y; y++)
            for (int x = 1; x < X; x++)
                dp[y][x] = dp[y - 1][x] + dp[y][x - 1];

        return dp[Y - 1][X - 1];
    }
};