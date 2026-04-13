class Solution {
    const int dy[4] = {-1, 0, 1, 0}, dx[4] = {0, 1, 0, -1};
    int Y, X;
    bool inRange(int y, int x) {
        return 0 <= y && y < Y && 0 <= x && x < X;
    }
    vector<vector<int>> grid, visited;
    int dfs(int y, int x) {
        int ret = 0;
        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) {
                ret += true;
                continue;
            }
            if (visited[ny][nx]) continue;
            if (grid[ny][nx]) continue;
            visited[ny][nx] = true;
            ret += dfs(ny, nx);
        }
        return ret;
    }
public:
    int closedIsland(vector<vector<int>>& grid) {
        this->grid = grid;
        Y = grid.size(), X = grid[0].size();
        visited.assign(Y, vector<int>(X, 0));
        int ret = 0;
        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                if (grid[y][x]) continue;
                if (visited[y][x]) continue;
                visited[y][x] = true;
                if (dfs(y, x) == 0) ret++;
            }
        }
        return ret;
    }
};