class Solution {
    int Y, X;
    const int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
    vector<vector<int>> dp;
    bool inRange(int y, int x) { return 0 <= y && y < Y && 0 <= x && x < X; };
    int dfs(int y, int x, vector<vector<int>>& matrix) {
        int& ret = dp[y][x];
        if (ret != -1)
            return ret;
        int curr = matrix[y][x];

        ret = 0;
        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx))       continue;
            if (matrix[ny][nx] <= curr) continue;
            ret = max(ret, dfs(ny, nx, matrix));
        }
        return ++ret;
    }

public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        Y = matrix.size(), X = matrix[0].size();
        dp.resize(Y, vector<int>(X, -1));

        int ret = 0;
        for (int y = 0; y < Y; y++)
            for (int x = 0; x < X; x++) 
                ret = max(ret, dfs(y, x, matrix));
            
        return ret;
    }
};