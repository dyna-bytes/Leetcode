class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int Y = matrix.size();
        int X = matrix[0].size();
        vector<vector<int>> dp(Y, vector<int>(X, 0));

        int cnt = 0;
        for (int y = 0; y < Y; y++) {
            dp[y][0] = matrix[y][0];
            cnt += dp[y][0];
        }
        for (int x = 1; x < X; x++) {
            dp[0][x] = matrix[0][x];
            cnt += dp[0][x];
        }

        for (int y = 1; y < Y; y++)
            for (int x = 1; x < X; x++) {
                if (matrix[y][x])
                    dp[y][x] = min({dp[y - 1][x - 1], dp[y][x - 1], dp[y - 1][x]}) + 1;
                cnt += dp[y][x];
            }
        return cnt;
    }
};