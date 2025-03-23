class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int Y = matrix.size(), X = matrix[0].size();
        vector<vector<int>> dp(Y, vector<int>(X, 0));

        int max_len = 0;

        dp[0][0] = (matrix[0][0] == '1');
        max_len = max(max_len, dp[0][0]);

        for (int y = 1; y < Y; y++) {
            dp[y][0] = (matrix[y][0] == '1');
            max_len = max(max_len, dp[y][0]);
        }
        for (int x = 1; x < X; x++) {
            dp[0][x] = (matrix[0][x] == '1');
            max_len = max(max_len, dp[0][x]);
        }

        for (int y = 1; y < Y; y++) {
            for (int x = 1; x < X; x++) {
                dp[y][x] = matrix[y][x] == '1' ? 
                    1 + min({dp[y - 1][x], dp[y][x - 1], dp[y - 1][x - 1]})
                    : 0;
                max_len = max(max_len, dp[y][x]);
            }
        }

        return max_len * max_len;
    }
};