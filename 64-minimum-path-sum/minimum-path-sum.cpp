class Solution {
    typedef long long ll;
public:
    int minPathSum(vector<vector<int>>& grid) {
        int Y = grid.size();
        int X = grid[0].size();

        vector<vector<ll>> dp(Y, vector<ll>(X, INT_MAX));
        dp[0][0] = grid[0][0];

        for (int y = 1; y < Y; y++)
            dp[y][0] = dp[y-1][0] + grid[y][0];

        for (int x = 1; x < X; x++)
            dp[0][x] = dp[0][x-1] + grid[0][x];

        for (int y = 1; y < Y; y++)
            for (int x = 1; x < X; x++)
                dp[y][x] = min(dp[y-1][x], dp[y][x-1]) + grid[y][x];

        return dp[Y-1][X-1]; 
    }
};