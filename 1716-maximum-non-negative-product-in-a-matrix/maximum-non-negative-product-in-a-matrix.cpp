class Solution {
    typedef long long ll;
    typedef pair<ll, ll> pll;
    int Y, X;
    const ll mod = 1e9 + 7;

public:
    int maxProductPath(vector<vector<int>>& grid) {
        Y = grid.size(), X = grid[0].size();
        
        vector<vector<ll>> max_dp(Y + 1, 
            vector<ll>(X + 1, -1));
        vector<vector<ll>> min_dp(Y + 1, 
            vector<ll>(X + 1, 1));

        max_dp[0][0] = grid[0][0];
        min_dp[0][0] = grid[0][0];

        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                if (y > 0) {
                    max_dp[y][x] = max({ max_dp[y][x], 
                        grid[y][x] * max_dp[y-1][x], grid[y][x] * min_dp[y-1][x] });
                    min_dp[y][x] = min({ min_dp[y][x], 
                        grid[y][x] * max_dp[y-1][x], grid[y][x] * min_dp[y-1][x] });
                }

                if (x > 0) {
                    max_dp[y][x] = max({ max_dp[y][x], 
                        grid[y][x] * max_dp[y][x-1], grid[y][x] * min_dp[y][x-1] });
                    min_dp[y][x] = min({ min_dp[y][x], 
                        grid[y][x] * max_dp[y][x-1], grid[y][x] * min_dp[y][x-1] });
                }
            }
        } 

        if (max_dp[Y-1][X-1] < 0) return -1;
        return max_dp[Y-1][X-1] % mod;
    }
};