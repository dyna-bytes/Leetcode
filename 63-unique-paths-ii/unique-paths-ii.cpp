class Solution {
    int Y, X;
    vector<vector<int>> grid;
    vector<vector<int>> dp;
    const int dy[2] = {0, 1}, dx[2] = {1, 0};
    bool inRange(int y, int x) {
        return 0 <= y && y < Y && 0 <= x && x < X;
    }

    int f(int y, int x) {
        if (grid[y][x]) return false;
        if (y == Y-1 && x == X-1) return true;

        int& ret = dp[y][x];
        if (ret != -1) return ret;

        ret = 0;
        for (int d = 0; d < 2; d++) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            if (grid[ny][nx]) continue;
            ret += f(ny, nx);
        }
        return ret;
    }
public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        Y = grid.size(), X = grid[0].size();
        this->grid = grid;
        dp.resize(Y+1, vector<int>(X+1, -1));
        return f(0, 0);
    }
};