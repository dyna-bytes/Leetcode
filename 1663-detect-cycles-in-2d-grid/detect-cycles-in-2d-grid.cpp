class Solution {
    const int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
    enum {
        NOT_VISITED,
        VISITING,
        VISITED,
    };
    int Y, X;
    vector<vector<char>> grid;
    vector<vector<int>> visited;

    bool inRange(int y, int x) {
        return 0 <= y && y < Y && 0 <= x && x < X;
    }

    int dfs(int y, int x, char val) {
        if (visited[y][x] == VISITED) return true;
        visited[y][x] = VISITING;

        int ret = false;
        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            if (grid[ny][nx] != val) continue;
            if (visited[ny][nx] == VISITING) continue;
            ret += dfs(ny, nx, val);
        }

        visited[y][x] = VISITED;
        return ret;
    }
public:
    bool containsCycle(vector<vector<char>>& grid) {
        Y = grid.size();
        X = grid[0].size();
        this->grid = grid;
        visited.assign(Y, vector<int>(X, 0));

        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                if (visited[y][x]) continue;

                if (dfs(y, x, grid[y][x])) return true;
            }
        }
        return false;
    }
};