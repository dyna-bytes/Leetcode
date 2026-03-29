class Solution {
    const int dy[8] = {0, 1, 1, 1};
    const int dx[8] = {1, 1, 0, -1};
    int Y, X;
    vector<vector<int>> mat;
    bool inRange(int y, int x) {
        return 0 <= y && y < Y && 0 <= x && x < X;
    }
    int dfs(int y, int x, int dir) {
        if (!inRange(y, x)) return 0;
        if (mat[y][x] == 0) return 0;

        int ny = y + dy[dir], nx = x + dx[dir];
        return 1 + dfs(ny, nx, dir);
    }
public:
    int longestLine(vector<vector<int>>& mat) {
        Y = mat.size(), X = mat[0].size();
        this->mat = mat;
        int ret = 0;
        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                if (!mat[y][x]) continue;
                
                for (int d = 0; d < 4; d++) 
                    ret = max(ret, dfs(y, x, d));
            }
        }
        return ret;
    }
};